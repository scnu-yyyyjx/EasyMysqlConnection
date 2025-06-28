#pragma once
#include<string>
#include<queue>
#include "Connection.h"
#include<mutex>
#include<atomic>
#include<thread>
#include<memory>
#include<functional>
#include<condition_variable>
//实现连接池功能模块
using namespace std;

class ConnectionPool {

public:
	//用于外部获取连接池对象实例
	static ConnectionPool* getConnectionPool(); 

	//用于外部获取连接池中的连接对象，这里使用智能指针自动管理连接对象的生命周期（通过重定义智能指针的销毁方式来归还资源）。
	shared_ptr<Connection> getConnection(); 

private:
	//实现线程安全的单例模式
	ConnectionPool(); //单例#1 构造函数私有化，禁止外部创建对象
	
	//加载配置文件，初始化连接池参数
	bool loadConfigFile();

	//运行在独立的线程中，负责生产连接对象
	void produceConnectionTask(); 

	//扫描多余的连接，释放空闲时间超过最大空闲时间的连接
	void scanConnectionTask();

	//连接池成员变量
	string _ip; //数据库IP地址
	unsigned short _port; //数据库端口号，默认3306
	string _username; //数据库用户名
	string _password; //数据库密码
	string _dbname; //数据库名称，默认chat
	int _initSize; //连接池初始大小
	int _maxSize; //连接池最大大小
	int _maxIdleTime; //连接池最大空闲时间
	int _connectionTimeout; //获取连接超时时间

	queue<Connection*> _connectionQue; //连接池队列，存储可用的连接对象
	mutex _queueMutex; //互斥锁，保护连接池队列的线程安全
	atomic_int _connectionCount; //连接池当前连接数，使用atomic类型保证线程安全
	condition_variable cv; //条件变量，用于生产者和消费者的通信
};