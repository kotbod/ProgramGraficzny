#pragma once

#include <exception>

using namespace std;

class WrongFilterSize : public exception {
public:
	virtual const char* what() noexcept {
		return "A filter can't have an even number as size\n";
	}
};

class Filter {
public:
	float sum;
	int size;
	bool include_edges;
	bool absolute;
	// Two dimensional array size * size
	float *kernel;
	Filter(int size, float *kernel, bool include_edges);
	~Filter();
};
