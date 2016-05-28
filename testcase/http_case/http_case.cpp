#include "http_case.h"
#include "../../src/comm_inc.h"
#include "http_request.h"
#include "http_response.h"

#include<sstream>
using namespace std;

//用于测试的url和web
#define WWW_HOST					"www.boost.org"
//#define URL							"/LICENSE_1_0.txt"

//内网测试服务器
#define NORTHSEA_HOST_IP			"192.168.1.4"
#define URL							"/cgi-bin/northsea/prsim/news/1/get_news.fcgi?user_id=5&token=12_&news_type=5&count=5&callback=jsonp"

#define PORT						80						//http default port

#define BUFFER_SIZE					 (1024*5)

bool HttpCase::Init(){
	port_ = PORT;		
	//host_ = WWW_HOST;
	host_ = NORTHSEA_HOST_IP;
	return true;
}

bool HttpCase::Connect(){
	
	return true;
}

bool HttpCase::DoStep(){
	if (!ConnectWebServer()){
		cout << "Error! Failed to connect web server ";
		cout << "case_name:" << name_ << endl;
		return false;
	}
	// 发送 http请求
	stringstream os;
	std::string request = os.str();
	http_case::HttpRequest http_request(http_case::METHOD_GET);
	http_request.set_url(URL);
	http_request.set_proto_vertion("1.1");
	http_request.AddHeadParam("Accept", "*.*");
	http_request.AddHeadParam("Host", NORTHSEA_HOST_IP);
	http_request.AddHeadParam("Connection", " Keep-Alive");
	http_request.AddHeadParam("Alive", "300");
	http_request.AddHeadParam("Keep-Alive", "timeout=20");
	http_request.AddHeadParam("Content-Type", "text/html;charset=GB2312");
	request = http_request.Serialize();

	int len = request.length();
	int send_ret = ::send(socket_, request.c_str(), len, 0);
	if (SOCKET_ERROR == send_ret){
		cout << "error! failed to send request!" << endl;
		return false;
	}
	// recieve response
	char *buffer_ptr = new char[BUFFER_SIZE];
	memset(buffer_ptr, 0, BUFFER_SIZE);
	if (nullptr == buffer_ptr){
		cout << "nullptr == buffer_ptr" << endl;
	}
	assert(nullptr != buffer_ptr);
	int read_ret = ::recv(socket_, buffer_ptr, BUFFER_SIZE, 0);
	if (SOCKET_ERROR == read_ret){
		cout << "error! failed to recv response!" << endl;
		return false;
	}
	if (0 == read_ret){
		cout << "[error]! recv 0 byte response, the connection may be closed!" << endl;
		return false;
	}
	// analyze response ...	
	(*this) << "============================[response]============================" << case_endl;

	http_case::HttpResponse http_respons(buffer_ptr);	
	(*this) << http_respons.response_line() << case_endl;
	(*this) << http_respons.ResponsHeadContent() << case_endl;
	(*this) << http_respons.response_data() << case_endl;

	delete [] buffer_ptr;
	buffer_ptr = nullptr;
	return true;
}

void HttpCase::Close(){
	::closesocket(socket_);
}

bool HttpCase::ConnectWebServer(){
	// 连接
	std::string ip_addr = GetIpFromHost(host_);
	if (ip_addr.length() < 1){
		cout << "Error! Failed to get ip from host:" << host_ << ", check network init" << endl;
		return false;
	}
	socket_ = ::socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == socket_){
		return false;
	}
	SOCKADDR_IN sock_svr_addr;
	sock_svr_addr.sin_port = htons(port_);
	sock_svr_addr.sin_family = AF_INET;
	sock_svr_addr.sin_addr.s_addr = ::inet_addr(ip_addr.c_str());

	int conn_ret = ::connect(socket_, (SOCKADDR*)&sock_svr_addr, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == conn_ret){
		cout << "Error!HttpCase failed to connect host:" << host_ << endl;
		return false;
	}
	return true;
}