#include "ConnectionPool.h"
#include "public.h"

//连接池构造函数实现
ConnectionPool::ConnectionPool() {
	//加载配置文件
	if (!loadConfigFile()) {
		return; // 如果加载配置文件失败，直接返回
	}

	//初始化连接池，创建初始数量的连接
	for (int i = 0; i < _initSize; ++i) {
		Connection* conn = new Connection(); // 创建新的连接对象
		conn->connect(_ip, _port, _username, _password, _dbname); // 连接数据库
		conn->refreshAliveTime(clock()); // 刷新连接的起始空闲存活时间
		_connectionQue.push(conn); // 将连接对象放入连接池队列
		_connectionCount++; // 增加连接池当前连接数
	}

	//启动一个线程，作为连接的生产者
	thread produce(std::bind(&ConnectionPool::produceConnectionTask, this));
	produce.detach(); // 分离线程，使其在后台运行

	//启动一个定时线程，扫描多余的连接，释放空闲时间超过最大空闲时间的连接
	thread scan(std::bind(&ConnectionPool::scanConnectionTask, this));
	scan.detach(); // 分离线程，使其在后台运行
}

//线程安全的懒汉单例模式实现
ConnectionPool * ConnectionPool::getConnectionPool() {
	static ConnectionPool pool; // 静态局部变量，保证只创建一次，编译器会自动进行lock和unlock操作
	return &pool; // 返回指向单例的指针
}

//加载配置项实现
bool ConnectionPool::loadConfigFile() {
	FILE* fp = fopen("mysql.ini", "r"); // 打开配置文件

	if (fp == nullptr) {
		LOG("配置文件为空，打开失败");
		return false;
	}

	while (!feof(fp)) {
		char line[1024] = { 0 }; // 用于存储每一行内容
		fgets(line, sizeof(line), fp); // 读取一行内容
		if (line[0] == '#' || line[0] == '\n') continue; // 跳过注释和空行
		char key[64] = { 0 }, value[64] = { 0 }; // 用于存储键和值
		sscanf(line, "%[^=]=%s", key, value); // 按照格式解析键值对
		if (strcmp(key, "ip") == 0) {
			_ip = value; // 设置IP地址
		}
		else if (strcmp(key, "port") == 0) {
			_port = atoi(value); // 设置端口号
		}
		else if (strcmp(key, "username") == 0) {
			_username = value; // 设置用户名
		}
		else if (strcmp(key, "password") == 0) {
			_password = value; // 设置密码
		}
		else if (strcmp(key, "initSize") == 0) {
			_initSize = atoi(value); // 设置初始连接池大小
		}
		else if (strcmp(key, "maxSize") == 0) {
			_maxSize = atoi(value); // 设置最大连接池大小
		}
		else if (strcmp(key, "maxIdleTime") == 0) {
			_maxIdleTime = atoi(value); // 设置最大空闲时间
		}
		else if (strcmp(key, "connectionTimeout") == 0) {
			_connectionTimeout = atoi(value); // 设置获取连接超时时间
		}
		else if (strcmp(key, "dbname") == 0) {
			_dbname = value; // 设置数据库名称
		}
	}
	return true; // 返回true表示加载成功
}


void ConnectionPool::produceConnectionTask() {
	for (;;) {
		unique_lock<mutex> lock(_queueMutex); // 获取互斥锁，保护连接池队列的线程安全
		while (!_connectionQue.empty()) {
			cv.wait(lock); // 等待可用连接变空
		}

		// 如果连接池队列为空且当前连接数小于最大连接数，则创建新的连接
		if (_connectionCount < _maxSize) {
			Connection* conn = new Connection(); // 创建新的连接对象
			conn->connect(_ip, _port, _username, _password, _dbname); // 连接数据库
			conn->refreshAliveTime(clock()); // 刷新连接的起始空闲存活时间
			_connectionQue.push(conn); // 将连接对象放入连接池队列
			_connectionCount++; // 增加连接池当前连接数
		}
		cv.notify_all(); // 通知消费者线程有新的连接可用
	}
}

void ConnectionPool::scanConnectionTask() {
	for (;;) {
		//模拟定时效果
		this_thread::sleep_for(chrono::seconds(_maxIdleTime)); // 每隔最大空闲时间扫描一次

		//扫描整个连接池，释放空闲时间超过最大空闲时间的连接

		unique_lock<mutex> lock(_queueMutex); // 获取互斥锁，保护连接池队列的线程安全
		while (_connectionCount > _initSize) {
			Connection* conn = _connectionQue.front(); // 获取队列头部的连接对象
			if(conn->getAliveTime() >= _maxIdleTime * CLOCKS_PER_SEC) { // 如果连接的空闲存活时间超过最大空闲时间
				_connectionQue.pop(); // 从连接池队列中移除该连接对象
				delete conn; // 释放连接对象的内存
				_connectionCount--; // 减少连接池当前连接数
			} else {
				break; // 如果没有超过最大空闲时间，跳出循环
			}
		}
	}

}

shared_ptr<Connection> ConnectionPool::getConnection() {
	unique_lock<mutex> lock(_queueMutex); // 获取互斥锁，保护连接池队列的线程安全
	while (_connectionQue.empty()) {
		if (cv_status::timeout == cv.wait_for(lock, chrono::milliseconds(_connectionTimeout))) {
			if (_connectionQue.empty()) {
				LOG("获取空闲连接超时");
				return nullptr; // 如果等待超时仍然没有可用连接，返回nullptr
			}
		}
	}

	// share_ptr指针析构时，默认会delete指针指向的connection对象，相当于调用Connection的析构函数。这里需要自定义share_ptr的析构函数，来将连接对象归还到连接池队列中，而不是直接删除连接对象。shared_ptr的自定义删除器可以通过lambda表达式来实现。删除器是shared_ptr的第二个参数。
	shared_ptr<Connection> sp(_connectionQue.front(), 
		[&](Connection* pcon) {
			unique_lock<mutex> lock(_queueMutex); // 获取互斥锁，保护连接池队列的线程安全
			pcon->refreshAliveTime(clock()); // 刷新连接的起始空闲存活时间
			_connectionQue.push(pcon); // 将连接对象归还到连接池队列中
		});
	_connectionQue.pop(); // 从连接池队列中取出一个连接对象
	if (_connectionQue.empty()) {
		cv.notify_all(); // 谁消费了最后一个连接，就通知生产者线程可以继续生产连接
	}
	return sp;
}