#ifndef __HTTP_COMMON_H__
#define __HTTP_COMMON_H__
#include <string>
using namespace std;

namespace http_case{
	enum RequestMethod{
		METHOD_MIN = 0,
		METHOD_GET = 1,
		METHOD_POS = 2,
		METHOD_MAX
	};
	struct HttpRequestMethod{
		RequestMethod method_type;
		char *name;
	};

	
}
#endif