#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__
#include "http_common.h"
#include <map>
using namespace std;

namespace http_case{
	class HttpRequest{
	public:
		HttpRequest(RequestMethod method);
		~HttpRequest(){}
		void set_url(std::string url);
		void set_proto_vertion(std::string ver);
		void AddHeadParam(std::string field, std::string value);
		void AddRequestData(char *data_ptr, size_t data_len);
		std::string Serialize();
	protected:
		std::string method_name_;
		std::string url_;
		std::string proto_vertion_;
		std::string request_header_;
		std::string request_data_;
		std::map<std::string, std::string> head_param_map_;
	};
}
#endif