#pragma once

#define GLDEV_WRAPPED_API __declspec(dllexport)

GLDEV_WRAPPED_API int wrappedFunction0();

class GLDEV_WRAPPED_API WrappedClass {
public:
	WrappedClass();
	~WrappedClass();
	int classWrappedFunction();

	int value;
};