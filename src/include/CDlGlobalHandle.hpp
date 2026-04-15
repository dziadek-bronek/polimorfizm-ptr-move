#ifndef CDLGLOBALHANDLE
#define CDLGLOBALHANDLE

struct CDlGlobalHandle {
	CDlGlobalHandle();
	~CDlGlobalHandle();
	void set(void* handle);
	void* dlHandle;
};

#endif


