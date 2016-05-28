#include "http_request.h"
#include <sstream>
using namespace std;

namespace http_case{

	static HttpRequestMethod s_method_name[] = {
		{ METHOD_MIN, "INVALID_METHOD" },
		{ METHOD_GET, "GET" },
		{ METHOD_POS, "POST" },
		{ METHOD_MAX, "INVALID_METHOD" },
	};

	HttpRequest::HttpRequest(RequestMethod method){
		method_name_ = s_method_name[method].name;
	}
	void HttpRequest::set_url(std::string url){
		url_ = url;
	}
	void HttpRequest::set_proto_vertion(std::string ver){
		proto_vertion_ = "HTTP/";
		proto_vertion_.append(ver);
	}
	void HttpRequest::AddHeadParam(std::string field, std::string value){
		head_param_map_.insert(make_pair(field, value));
	}
	void HttpRequest::AddRequestData(char *data_ptr, size_t data_len){
		request_data_.append(data_ptr, data_len);
	}
	std::string HttpRequest::Serialize(){
		std::stringstream os;
		// request line
		os << method_name_ << " " << url_ << " " << proto_vertion_ << "\r\n";
		//request head
		for (std::map<std::string, std::string>::iterator it = head_param_map_.begin();
			it != head_param_map_.end();
			++it){
			os << it->first << ":" << it->second << "\r\n";
		}
		os << "\r\n";
		os << request_data_;

		return os.str();
	}
}

