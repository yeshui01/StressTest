#include <iostream>
using namespace std;
#include "./src/case_interfase.h"
#include "testcase/http_case/http_case.h"

/*
 @ MICRO: REGISTER_TEST_CASE(CLASS_NAME, CASE_NAME, RUN_NUM, CASE_NUM)
 @ CLASS_NAME: 类名
 @ CASE_NAME:  测试用例名
 @ RUN_NUM:	   执行次数
 @ CASE_NUM:   测试用例的个数
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
	stress_test.RunTest(5);		//开启5个线程来执行测试用例
	stress_test.WaitEnd();
	cout << "\n[all test finished! press any key to exit!]" << endl;
	
	getchar();
	WSACleanup();
	return 0;
}