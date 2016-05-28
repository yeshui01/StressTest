#ifndef __HTTP_CASE_H__
#define __HTTP_CASE_H__
#include <string>
using namespace std;
#include "../../src/test_case.h"

class HttpCase : public TestCase{
public:
	HttpCase(std::string name, int id = 0) 
		:TestCase(name, id){
		port_ = 0;
	}
	virtual ~HttpCase(){}
	virtual bool Init();
	virtual bool Connect();
	virtual bool DoStep();
	virtual void Close();

protected:
	bool ConnectWebServer();
	std::string host_;
	int port_;
};


#endif