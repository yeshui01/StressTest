#ifndef __CASE_INTERFACE_H__
#define __CASE_INTERFACE_H__
#include "StressTest.h"
#include "test_case.h"
#include "case_manager.h"
// ×¢²átest case

#define REGISTER_TEST_CASE(CLASSNAME, CASENAME, RUNNUM, CASENUM) { \
for (int i = 0; i < CASENUM; ++i){\
	TestCase *case_ptr = new CLASSNAME(""#CASENAME, CaseManager::s_case_index_++); \
	assert(nullptr != case_ptr); \
	case_ptr->set_run_count(RUNNUM); \
	CaseManager::GetInstance()->PushCase(case_ptr); \
	cout << "register test case " << case_ptr->name() << " case_id = " << case_ptr->case_id() << endl; \
}\
};



#endif