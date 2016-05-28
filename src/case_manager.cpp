#include "case_manager.h"
#include "comm_inc.h"

CaseManager* CaseManager::instance_ = nullptr;
std::mutex CaseManager::mtx_;

int CaseManager::s_case_index_ = 1;

CaseManager* CaseManager::GetInstance(){
	if (nullptr == instance_){
		std::lock_guard<std::mutex> lock_mu(mtx_);
		if (nullptr == instance_){
			instance_ = new CaseManager();
			assert(nullptr != instance_);
		}
	}
	return instance_;
}

void CaseManager::FreeInstance(){
	if (nullptr != instance_){
		std::lock_guard<std::mutex> lock_mu(mtx_);
		if (nullptr != instance_){
			delete instance_;
			instance_ = nullptr;
		}
	}
}

bool CaseManager::PushCase(TestCase* case_ptr){
	if (nullptr == case_ptr)
		return false;
	std::lock_guard<std::mutex> lock_mu(mtx_);
	case_queue_.push(case_ptr);
	return true;
}

TestCase* CaseManager::PopCase(){
	TestCase *case_ptr = nullptr;
	std::lock_guard<std::mutex> lock_mu(mtx_);
	if (!case_queue_.empty()){
		case_ptr = case_queue_.front();
		case_queue_.pop();
	}
	return case_ptr;
}