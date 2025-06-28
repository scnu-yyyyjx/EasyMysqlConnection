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
//ʵ�����ӳع���ģ��
using namespace std;

class ConnectionPool {

public:
	//�����ⲿ��ȡ���ӳض���ʵ��
	static ConnectionPool* getConnectionPool(); 

	//�����ⲿ��ȡ���ӳ��е����Ӷ�������ʹ������ָ���Զ��������Ӷ�����������ڣ�ͨ���ض�������ָ������ٷ�ʽ���黹��Դ����
	shared_ptr<Connection> getConnection(); 

private:
	//ʵ���̰߳�ȫ�ĵ���ģʽ
	ConnectionPool(); //����#1 ���캯��˽�л�����ֹ�ⲿ��������
	
	//���������ļ�����ʼ�����ӳز���
	bool loadConfigFile();

	//�����ڶ������߳��У������������Ӷ���
	void produceConnectionTask(); 

	//ɨ���������ӣ��ͷſ���ʱ�䳬��������ʱ�������
	void scanConnectionTask();

	//���ӳس�Ա����
	string _ip; //���ݿ�IP��ַ
	unsigned short _port; //���ݿ�˿ںţ�Ĭ��3306
	string _username; //���ݿ��û���
	string _password; //���ݿ�����
	string _dbname; //���ݿ����ƣ�Ĭ��chat
	int _initSize; //���ӳس�ʼ��С
	int _maxSize; //���ӳ�����С
	int _maxIdleTime; //���ӳ�������ʱ��
	int _connectionTimeout; //��ȡ���ӳ�ʱʱ��

	queue<Connection*> _connectionQue; //���ӳض��У��洢���õ����Ӷ���
	mutex _queueMutex; //���������������ӳض��е��̰߳�ȫ
	atomic_int _connectionCount; //���ӳص�ǰ��������ʹ��atomic���ͱ�֤�̰߳�ȫ
	condition_variable cv; //�������������������ߺ������ߵ�ͨ��
};