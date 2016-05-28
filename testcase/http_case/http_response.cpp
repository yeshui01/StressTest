#include "http_response.h"
#include <sstream>
using namespace std;

namespace http_case{

	HttpResponse::HttpResponse(std::string response_str){
		// analyze response_str
		size_t pos = response_str.find("\r\n");
		response_line_ = response_str.substr(0, pos + 2);
		response_str.erase(0, pos + 2);
		
		std::string response_head;
		pos = response_str.find("\r\n\r\n");
		response_head = response_str.substr(0, pos + 4);
		response_str.erase(0, pos + 4);

		pos = response_head.find("\r\n\r\n");
		response_head.erase(pos, string::npos);

		//temp
		response_head.append("\r\n");
		while (1){
			pos = response_head.find("\r\n");
			if (pos == string::npos){
				break;
			}
			string key_value = response_head.substr(0, pos);
			size_t tem_pos = key_value.find(":");
			if (string::npos != tem_pos){
				string key = key_value.substr(0, tem_pos);
				string val = key_value.substr(tem_pos + 1, string::npos);
				response_head_map_.insert(make_pair(key, val));
			}

			response_head.erase(0, pos + 2);
		}


		response_data_ = response_str;
	}

	std::string HttpResponse::ResponsHeadContent(){
		std::stringstream content;
		for (std::map<std::string, std::string>::iterator it = response_head_map_.begin();
			it != response_head_map_.end();
			++it){
			content << it->first << ":" << it->second << "\r\n";
		}
		return content.str();
	}
}