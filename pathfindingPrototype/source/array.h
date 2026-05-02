#pragma once

#include <cstdint>

template <class DataType>
class Array2D {
public:
	Array(size_t fieldNum, size_t fieldMaxLength)
		: fieldNum(fieldNum), fieldMaxLength(fieldMaxLength) {
		this->fieldCurrentLength = new size_t[this->fieldNum];
		for (size_t a = 0; a < this->fieldNum; ++a) {
			this->fieldCurrentLength[a] = 0;
		}
		this->data = new DataType[this->fieldNum * this->fieldMaxLength];
		this->dataElementInUse = new bool[this->fieldNum * this->fieldMaxLength];
		for (size_t a = 0; a < (this->fieldNum * this->fieldMaxLength); ++a) {
			this->dataElementInUse[a] = false;
		}
	}
	~Array() {
		delete[] this->fieldCurrentLength;
		delete[] this->data;
		delete[] this->dataElementInUse;
	}
	size_t getFieldMaxLength() {
		return this->fieldMaxLength;
	}
	size_t getFieldCurrentLength(size_t fieldIndex) {
		return this->fieldCurrentLength[fieldIndex];
	}
	DataType getDataElement(size_t fieldIndex, size_t fieldElementIndex) {
		return this->data[(fieldIndex * this->fieldMaxLength) + fieldElementIndex];
	}
	void addDataElement(size_t fieldIndex, DataType dataElement) {
		size_t fieldStartIndex = fieldIndex * this->fieldMaxLength;
		for (size_t a = fieldStartIndex; a <= (fieldStartIndex + this->fieldCurrentLength[fieldIndex]); ++a) {
			if (this->dataElementInUse[a] == false) {
				dataElementInUse = true;
				data[a] = dataElement;
				if (a == this->fieldCurrentLength[fieldIndex])
					this->fieldCurrentLength[fieldIndex] += 1;
			}
		}
	}
	void removeDataElement(size_t fieldIndex)
private:
	DataType* data;
	size_t fieldNum;
	size_t fieldMaxLength;
	size_t* fieldCurrentLength;
	bool* dataElementInUse;
};