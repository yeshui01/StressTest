#ifndef __TEST_CASE_H__
#define __TEST_CASE_H__

#include "comm_inc.h"
#include <ostream>
#include <fstream>
#include <sstream>
using namespace std;

ofstream& case_endl(ofstream& of);

class TestCase{
public:
	enum CaseStatus{
		ECASE_START = 0,
		ECASE_INIT = 1,
		ECASE_CONNECT = 2,
		ECASE_DOSTEP = 3,
		ECASE_CLOSE = 4,
		ECASE_END = 5
	};

public:
	TestCase(std::string name, int id = 0)
		:case_id_(id),
		name_(name),
		status_(ECASE_INIT),
		socket_(INVALID_SOCKET),
		run_count_(1){
		std::stringstream os;
		os << "./log/" << name << id << ".log";
		log_file_.open(os.str().c_str(), ios::out | ios::trunc);
		if (!log_file_.is_open()){
			cout << "Error! Failed to open log file,case_name:" << name << "case_id:" << id << endl;
		}
	};

	virtual ~TestCase(){ log_file_.close(); };

	int run_count(){ return run_count_; }
	void set_run_count(int count){ 
		count >= 0 ? (run_count_ = count) : (run_count_ = 0);
	}

	std::string name() { return name_; }
	CaseStatus status(){ return status_; }
	void set_status(CaseStatus status){ status_ = status; };
	int case_id(){ return case_id_; };
	virtual bool Init();
	virtual bool Connect();
	virtual bool DoStep() = 0;
	virtual void Close();
	TestCase& operator<<(std::string str);
	TestCase& operator<<(double val);
	TestCase& operator << (ofstream& (*pFun)(ofstream &));
protected:
	std::string GetIpFromHost(std::string host_name);
	std::string name_;
	SOCKET socket_;
	int run_count_;
	int case_id_;
	CaseStatus status_;
	std::ofstream log_file_;
};


#endif