#pragma once

//实现mysql数据库增删改查
#include <mysql.h>
#include <string>
#include <ctime>
using namespace std;
class Connection {
public:
	//初始化数据库连接
	Connection();

	//释放数据库连接
	~Connection();

	//连接数据库
	bool connect(string ip, unsigned short port, string user, string password, string dbname);

	//执行更新操作
	bool update(string sql);

	//查询操作select
	MYSQL_RES* query(string sql);

	//刷新连接空闲存活时间
	void refreshAliveTime(clock_t time) {
		_alivetime = clock(); //设置连接起始空闲存活时间
	}

	//获取连接空闲存活时间
	clock_t getAliveTime() const {
		return clock() - _alivetime; 
	}
private:
	MYSQL * _conn; //与MySQL Server的一条连接
	clock_t _alivetime; //起始空闲存活时间，用于判断连接是否超时
};
