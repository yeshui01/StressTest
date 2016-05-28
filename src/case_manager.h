#ifndef __CASE_MANAGER_H__
#define __CASE_MANAGER_H__
#include <mutex>
#include <queue>
using namespace std;

class TestCase;
class CaseManager;

class CaseManager{
protected:
	CaseManager(){}
	~CaseManager(){}
public:
	static CaseManager* GetInstance();
	static void FreeInstance();
public:
	bool PushCase(TestCase* case_ptr);
	TestCase* PopCase();
private:
	queue<TestCase*> case_queue_;
private:
	static CaseManager* instance_;
	static std::mutex mtx_;
public:
	static int s_case_index_;
};


#endif