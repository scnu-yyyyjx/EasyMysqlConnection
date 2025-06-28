// ConnectionPool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Connection.h"
#include "ConnectionPool.h"
using namespace std;


int main()
{

	Connection conn; // 创建数据库连接对象
	conn.connect("127.0.0.1", 3306, "root", "123456", "chat");

	//Connection conn; // 创建数据库连接对象
	//char sql[1024] = { 0 }; // 用于存储SQL语句
	//sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
	//conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//conn.update(sql); // 执行插入操作


	clock_t start = clock(); // 记录开始时间
	//ConnectionPool* pool = ConnectionPool::getConnectionPool(); // 获取连接池实例


	thread t1([]() {
		//ConnectionPool* pool = ConnectionPool::getConnectionPool(); // 获取连接池实例
		for (int i = 0; i < 2500; ++i) {
			Connection conn; // 创建数据库连接对象
			char sql[1024] = { 0 }; // 用于存储SQL语句
			sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql); // 执行插入操作

			//shared_ptr<Connection> conn = pool->getConnection(); // 从连接池获取连接对象
			//char sql[1024] = { 0 }; // 用于存储SQL语句
			//sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			//conn->update(sql); // 执行插入操作
		}
		});

	thread t2([]() {
		//ConnectionPool* pool = ConnectionPool::getConnectionPool(); // 获取连接池实例
		for (int i = 0; i < 2500; ++i) {
			Connection conn; // 创建数据库连接对象
			char sql[1024] = { 0 }; // 用于存储SQL语句
			sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql); // 执行插入操作

			//shared_ptr<Connection> conn = pool->getConnection(); // 从连接池获取连接对象
			//char sql[1024] = { 0 }; // 用于存储SQL语句
			//sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			//conn->update(sql); // 执行插入操作
		}
		});

	thread t3([]() {
		//ConnectionPool* pool = ConnectionPool::getConnectionPool(); // 获取连接池实例
		for (int i = 0; i < 2500; ++i) {
			Connection conn; // 创建数据库连接对象
			char sql[1024] = { 0 }; // 用于存储SQL语句
			sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql); // 执行插入操作

			//shared_ptr<Connection> conn = pool->getConnection(); // 从连接池获取连接对象
			//char sql[1024] = { 0 }; // 用于存储SQL语句
			//sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			//conn->update(sql); // 执行插入操作
		}
		});

	thread t4([]() {
		//ConnectionPool* pool = ConnectionPool::getConnectionPool(); // 获取连接池实例
		for (int i = 0; i < 2500; ++i) {
			Connection conn; // 创建数据库连接对象
			char sql[1024] = { 0 }; // 用于存储SQL语句
			sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql); // 执行插入操作

			//shared_ptr<Connection> conn = pool->getConnection(); // 从连接池获取连接对象
			//char sql[1024] = { 0 }; // 用于存储SQL语句
			//sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			//conn->update(sql); // 执行插入操作
		}
		});

	t1.join(); // 等待线程1结束
	t2.join(); // 等待线程2结束
	t3.join(); // 等待线程3结束
	t4.join(); // 等待线程4结束

	clock_t end = clock(); // 记录结束时间

	double duration = double(end - start) / CLOCKS_PER_SEC; // 计算耗时
	cout << "插入1000条数据耗时: " << duration << "秒" << endl;

    return 0;
}

