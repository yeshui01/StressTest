#include "test_case.h"


ofstream& case_endl(ofstream& of){
	of << "\n";
	of.flush();
	return of;
}

bool TestCase::Init(){
	cout << "TestCase::Init()\n";
	return true;
}
bool TestCase::Connect(){
	cout << "TestCase::Connect()\n";
	return true;
}

bool TestCase::DoStep(){
	cout << "TestCase::DoStep()\n";
	return true;
}

void TestCase::Close(){
	cout << "TestCase::Close()\n";
}

std::string TestCase::GetIpFromHost(std::string host_name){
	std::string ip_addr = "";
	struct hostent *hostent_ptr = ::gethostbyname(host_name.c_str());
	if (hostent_ptr == nullptr){
		return false;
	}
	in_addr svr_addr;
	memcpy(&svr_addr.S_un.S_addr, hostent_ptr->h_addr_list[0], hostent_ptr->h_length);
	ip_addr = ::inet_ntoa(svr_addr);
	return ip_addr;
}

TestCase& TestCase::operator<<(std::string str){
	log_file_ << str;
	return *this;
}

TestCase& TestCase::operator<<(double val){
	log_file_ << val;
	return *this;
}

TestCase& TestCase::operator << (ofstream& (*pFun)(ofstream &)){
	(*pFun)(log_file_);
	return *this;
}