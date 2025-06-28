#pragma once

//ʵ��mysql���ݿ���ɾ�Ĳ�
#include <mysql.h>
#include <string>
#include <ctime>
using namespace std;
class Connection {
public:
	//��ʼ�����ݿ�����
	Connection();

	//�ͷ����ݿ�����
	~Connection();

	//�������ݿ�
	bool connect(string ip, unsigned short port, string user, string password, string dbname);

	//ִ�и��²���
	bool update(string sql);

	//��ѯ����select
	MYSQL_RES* query(string sql);

	//ˢ�����ӿ��д��ʱ��
	void refreshAliveTime(clock_t time) {
		_alivetime = clock(); //����������ʼ���д��ʱ��
	}

	//��ȡ���ӿ��д��ʱ��
	clock_t getAliveTime() const {
		return clock() - _alivetime; 
	}
private:
	MYSQL * _conn; //��MySQL Server��һ������
	clock_t _alivetime; //��ʼ���д��ʱ�䣬�����ж������Ƿ�ʱ
};
