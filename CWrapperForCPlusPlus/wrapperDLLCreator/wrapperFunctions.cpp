#include "pch.h"
#include "wrapperFunctions.h"
#include "wrappedFunctions.h"
#pragma comment(lib, "wrappedProgramWindows.lib")
#include <new>

extern "C" int wrapperFunction0() {
	return wrappedFunction0();
}

extern "C" struct WrapperClass* WrapperClass_constructor(struct WrapperClass* self) {
	return reinterpret_cast<struct WrapperClass*>(new (self) WrappedClass());
}

extern "C" void WrapperClass_destructor(struct WrapperClass* self) {
	reinterpret_cast<WrappedClass*>(self)->~WrappedClass();
}

extern "C" int WrapperClass_classWrappedFunction(struct WrapperClass* self) {
	return reinterpret_cast<WrappedClass*>(self)->classWrappedFunction();
}