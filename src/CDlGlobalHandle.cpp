#include"include/CDlGlobalHandle.hpp"

#include<dlfcn.h>

	CDlGlobalHandle::CDlGlobalHandle() : dlHandle(nullptr){}
	CDlGlobalHandle::~CDlGlobalHandle(){
		if (nullptr == dlHandle)
		{
			return;
		}

		       	dlclose(dlHandle);
	}
	void CDlGlobalHandle::set(void* handle) {dlHandle = handle;}


