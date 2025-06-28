#include "public.h"
#include "Connection.h"

//��ʼ�����ݿ�����-ʵ��
Connection::Connection() {
	_conn = mysql_init(nullptr); //ʹ��MySQL C API��ʼ��һ��MYSQL����
}

//�ͷ����ݿ�����-ʵ��
Connection::~Connection() {
	if (_conn != nullptr) {
		mysql_close(_conn); //�ر���MySQL Server������
		_conn = nullptr; //��ָ����Ϊnullptr������Ұָ��
	}
}

//�������ݿ�-ʵ��
bool Connection::connect(string ip, unsigned short port, string user, string password, string dbname) {
	MYSQL* p = mysql_real_connect(_conn, ip.c_str(), user.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0);
	return p != nullptr; //������ӳɹ������طǿ�ָ��
}

//ִ�и��²���-ʵ��
bool Connection::update(string sql) {
	if (mysql_query(_conn, sql.c_str())) { //ִ��SQL���
		LOG("����ʧ�ܣ�" + sql); //���ִ��ʧ�ܣ���ӡ������Ϣ
		return false; //���ִ��ʧ�ܣ�����false
	}
	return true; //���ִ�гɹ�������true
}

//��ѯ����select-ʵ��
MYSQL_RES* Connection::query(string sql) {
	if (mysql_query(_conn, sql.c_str())) { //ִ��SQL���
		LOG("��ѯʧ�ܣ�" + sql); //���ִ��ʧ�ܣ���ӡ������Ϣ
		return nullptr; //���ִ��ʧ�ܣ�����nullptr
	}
	return mysql_store_result(_conn); //���ִ�гɹ������ؽ����
}