#ifndef __REQUET_HEADER_H__
#define __REQUET_HEADER_H__
#include "http_common.h"
namespace HttpCase{
	class HttpHeader{
	public:
		HttpHeader(RequestMethod method_type, std::string url);
	};
}

#endif