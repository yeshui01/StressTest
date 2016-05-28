#ifndef __STRESS_TEST_H__
#define __STRESS_TEST_H__
#include "comm_inc.h"
#include <thread>
#include <chrono>
using namespace std;

class CaseManager;

class StressTest{
public:
	StressTest();
	~StressTest();
	void Init();
	void RunTest(int thread_num = 1);
	void WaitEnd();
protected:
	bool WorkFunc(int thread_idx, CaseManager* case_mgr_ptr = nullptr);
private:
	vector<thread> thread_vec;
	bool end_;
};
#endif