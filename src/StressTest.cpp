#include "StressTest.h"
#include "test_case.h"
#include "case_manager.h"
#include "case_interfase.h"
#include <time.h>

StressTest::StressTest(){
	end_ = false;
}

StressTest::~StressTest(){

}

void StressTest::Init(){
	cout.sync_with_stdio(true);
}

void StressTest::RunTest(int thread_num){
	if (0 == thread_num){
		return;
	}
	for (int i = 0; i < thread_num; ++i){
		thread_vec.push_back(std::thread(&StressTest::WorkFunc, std::ref(*this), (i+1), CaseManager::GetInstance()));
	}
}

void StressTest::WaitEnd(){
	for (std::thread& rh : thread_vec){
		rh.join();
	}
}

bool StressTest::WorkFunc(int thread_idx, CaseManager* case_mgr_ptr){
	if (nullptr == case_mgr_ptr){
		return false;
	}
	int sleep_count = 0;
	cout << "[thread start], id_index = " << thread_idx << endl;
	TestCase *case_ptr = nullptr;
	while (!end_){
		// TODO:
		case_ptr = CaseManager::GetInstance()->PopCase();
		if (nullptr == case_ptr){
			if (sleep_count >= 2){
				end_ = true;
				break;
			}
			std::this_thread::sleep_for(std::chrono::seconds(1));
			sleep_count++;
			continue;
		}
		else
		{
			sleep_count = 0;
			TestCase::CaseStatus e_status = case_ptr->status();
			switch (e_status){
				case (TestCase::ECASE_INIT):{
					case_ptr->Init();
					case_ptr->set_status(TestCase::ECASE_CONNECT);
					break;
				}
				case (TestCase::ECASE_CONNECT):{
					case_ptr->Connect();
					case_ptr->set_status(TestCase::ECASE_DOSTEP);
					break;
				}
				case (TestCase::ECASE_DOSTEP):{				
					if (case_ptr->run_count() <= 0){
						case_ptr->set_status(TestCase::ECASE_CLOSE);
					}else{
						case_ptr->set_run_count(case_ptr->run_count() - 1);
						clock_t start, finish;
						start = clock();
						// do case stetp
						case_ptr->DoStep();				
						finish = clock();
						double duration = (double)(finish - start) / CLOCKS_PER_SEC/* * 1000*/;
						(*case_ptr) << "[DoStopTime]:" << duration << " ms"<<case_endl;

						cout << "[case DoStep]thread_idex = " << thread_idx \
							<< " case_id =" \
							<< case_ptr->case_id() \
							<< " case name = " \
							<< case_ptr->name() \
							<< "time(ms):"<<duration \
							<< endl;
					}
					break;
				}
				case (TestCase::ECASE_CLOSE):{
					case_ptr->Close();
					case_ptr->set_status(TestCase::ECASE_END);
					break;
				}
				case (TestCase::ECASE_END) : {
					 cout << "[case end]thread_idex = " << thread_idx \
					 << " case_id =" \
					 << case_ptr->case_id() \
					 << " case name = " \
					 << case_ptr->name() << endl;

					delete case_ptr;
					case_ptr = nullptr;
					break;
				}
				default:{
					cout << "[error]unknown status of this test case,case_id =" \
						<< case_ptr->case_id() << "case name = " << case_ptr->name() <<endl;
					break;
				}
			}
			if (TestCase::ECASE_END != e_status && nullptr != case_ptr){	
				CaseManager::GetInstance()->PushCase(case_ptr);
			}
			case_ptr = nullptr;
		}
	}
	cout << ">>>>>>>>>>>>[thread end], id_index = " << thread_idx << endl;
	return true;
}