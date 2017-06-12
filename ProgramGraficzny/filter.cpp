#include "filter.h"



Filter::Filter(int size, float *kernel, bool include_edges): size(size), kernel(kernel), include_edges(include_edges) {
	if (size % 2 == 0) {
		throw WrongFilterSize();
	}
	sum = 0;
	for (int i = 0; i < size*size; ++i) {
		sum += kernel[i];
	}
}

Filter::~Filter() {
	delete[] kernel;
}

