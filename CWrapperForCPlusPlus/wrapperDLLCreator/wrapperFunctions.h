#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define GLDEV_WRAPPER_API __declspec(dllexport)

	GLDEV_WRAPPER_API int wrapperFunction0();

	GLDEV_WRAPPER_API struct WrapperClass {
		int value;
	};

	GLDEV_WRAPPER_API struct WrapperClass* WrapperClass_constructor(struct WrapperClass* self);
	GLDEV_WRAPPER_API void WrapperClass_destructor(struct WrapperClass* self);
	GLDEV_WRAPPER_API int WrapperClass_classWrappedFunction(struct WrapperClass* self);

#ifdef __cplusplus
}
#endif