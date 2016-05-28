#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__
#include "http_common.h"
#include <map>
using namespace std;

namespace http_case{
	class HttpResponse{
	public:
		HttpResponse(std::string response_str);
		~HttpResponse(){};
		std::string response_line() { return response_line_; };
		std::string ResponsHeadContent();
		std::string response_data(){ return response_data_; };

	protected:
		std::string response_line_;
		std::map<std::string, std::string> response_head_map_;
		std::string response_data_;
	};
}
#endif