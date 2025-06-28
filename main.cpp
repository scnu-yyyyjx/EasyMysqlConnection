// ConnectionPool.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include "Connection.h"
#include "ConnectionPool.h"
using namespace std;


int main()
{

	Connection conn; // �������ݿ����Ӷ���
	conn.connect("127.0.0.1", 3306, "root", "123456", "chat");

	//Connection conn; // �������ݿ����Ӷ���
	//char sql[1024] = { 0 }; // ���ڴ洢SQL���
	//sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
	//conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//conn.update(sql); // ִ�в������


	clock_t start = clock(); // ��¼��ʼʱ��
	//ConnectionPool* pool = ConnectionPool::getConnectionPool(); // ��ȡ���ӳ�ʵ��


	thread t1([]() {
		//ConnectionPool* pool = ConnectionPool::getConnectionPool(); // ��ȡ���ӳ�ʵ��
		for (int i = 0; i < 2500; ++i) {
			Connection conn; // �������ݿ����Ӷ���
			char sql[1024] = { 0 }; // ���ڴ洢SQL���
			sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql); // ִ�в������

			//shared_ptr<Connection> conn = pool->getConnection(); // �����ӳػ�ȡ���Ӷ���
			//char sql[1024] = { 0 }; // ���ڴ洢SQL���
			//sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			//conn->update(sql); // ִ�в������
		}
		});

	thread t2([]() {
		//ConnectionPool* pool = ConnectionPool::getConnectionPool(); // ��ȡ���ӳ�ʵ��
		for (int i = 0; i < 2500; ++i) {
			Connection conn; // �������ݿ����Ӷ���
			char sql[1024] = { 0 }; // ���ڴ洢SQL���
			sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql); // ִ�в������

			//shared_ptr<Connection> conn = pool->getConnection(); // �����ӳػ�ȡ���Ӷ���
			//char sql[1024] = { 0 }; // ���ڴ洢SQL���
			//sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			//conn->update(sql); // ִ�в������
		}
		});

	thread t3([]() {
		//ConnectionPool* pool = ConnectionPool::getConnectionPool(); // ��ȡ���ӳ�ʵ��
		for (int i = 0; i < 2500; ++i) {
			Connection conn; // �������ݿ����Ӷ���
			char sql[1024] = { 0 }; // ���ڴ洢SQL���
			sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql); // ִ�в������

			//shared_ptr<Connection> conn = pool->getConnection(); // �����ӳػ�ȡ���Ӷ���
			//char sql[1024] = { 0 }; // ���ڴ洢SQL���
			//sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			//conn->update(sql); // ִ�в������
		}
		});

	thread t4([]() {
		//ConnectionPool* pool = ConnectionPool::getConnectionPool(); // ��ȡ���ӳ�ʵ��
		for (int i = 0; i < 2500; ++i) {
			Connection conn; // �������ݿ����Ӷ���
			char sql[1024] = { 0 }; // ���ڴ洢SQL���
			sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
			conn.update(sql); // ִ�в������

			//shared_ptr<Connection> conn = pool->getConnection(); // �����ӳػ�ȡ���Ӷ���
			//char sql[1024] = { 0 }; // ���ڴ洢SQL���
			//sprintf_s(sql, sizeof(sql), "insert into user(name,age,sex) values('%s','%d','%s')", "zhang san", 18, "male");
			//conn->update(sql); // ִ�в������
		}
		});

	t1.join(); // �ȴ��߳�1����
	t2.join(); // �ȴ��߳�2����
	t3.join(); // �ȴ��߳�3����
	t4.join(); // �ȴ��߳�4����

	clock_t end = clock(); // ��¼����ʱ��

	double duration = double(end - start) / CLOCKS_PER_SEC; // �����ʱ
	cout << "����1000�����ݺ�ʱ: " << duration << "��" << endl;

    return 0;
}

