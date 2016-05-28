#include <iostream>
using namespace std;
#include "./src/case_interfase.h"
#include "testcase/http_case/http_case.h"

/*
 @ MICRO: REGISTER_TEST_CASE(CLASS_NAME, CASE_NAME, RUN_NUM, CASE_NUM)
 @ CLASS_NAME: ����
 @ CASE_NAME:  ����������
 @ RUN_NUM:	   ִ�д���
 @ CASE_NUM:   ���������ĸ���
*/

class CBase{
public:
	CBase(){}
	virtual ~CBase(){};
	virtual int fun() = 0;

};

int main(int argn, char* argv[]){
	WSADATA ws_data;
	WSAStartup(MAKEWORD(2,2), &ws_data);
	StressTest stress_test;
	stress_test.Init();
	REGISTER_TEST_CASE(HttpCase, http_test, 2, 20);
	stress_test.RunTest(5);		//����5���߳���ִ�в�������
	stress_test.WaitEnd();
	cout << "\n[all test finished! press any key to exit!]" << endl;
	
	getchar();
	WSACleanup();
	return 0;
}