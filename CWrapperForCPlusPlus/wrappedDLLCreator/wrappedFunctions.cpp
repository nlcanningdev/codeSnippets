#include "pch.h"
#include "wrappedFunctions.h"

int wrappedFunction0() {
	return 12;
}

WrappedClass::WrappedClass() {
	this->value = 20;
}

WrappedClass::~WrappedClass() {

}

int WrappedClass::classWrappedFunction() {
	return this->value;
}