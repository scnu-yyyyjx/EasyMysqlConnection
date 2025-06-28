#include "public.h"
#include "Connection.h"

//初始化数据库连接-实现
Connection::Connection() {
	_conn = mysql_init(nullptr); //使用MySQL C API初始化一个MYSQL对象
}

//释放数据库连接-实现
Connection::~Connection() {
	if (_conn != nullptr) {
		mysql_close(_conn); //关闭与MySQL Server的连接
		_conn = nullptr; //将指针置为nullptr，避免野指针
	}
}

//连接数据库-实现
bool Connection::connect(string ip, unsigned short port, string user, string password, string dbname) {
	MYSQL* p = mysql_real_connect(_conn, ip.c_str(), user.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0);
	return p != nullptr; //如果连接成功，返回非空指针
}

//执行更新操作-实现
bool Connection::update(string sql) {
	if (mysql_query(_conn, sql.c_str())) { //执行SQL语句
		LOG("更新失败：" + sql); //如果执行失败，打印错误信息
		return false; //如果执行失败，返回false
	}
	return true; //如果执行成功，返回true
}

//查询操作select-实现
MYSQL_RES* Connection::query(string sql) {
	if (mysql_query(_conn, sql.c_str())) { //执行SQL语句
		LOG("查询失败：" + sql); //如果执行失败，打印错误信息
		return nullptr; //如果执行失败，返回nullptr
	}
	return mysql_store_result(_conn); //如果执行成功，返回结果集
}