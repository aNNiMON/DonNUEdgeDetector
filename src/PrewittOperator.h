#pragma once
#include "AbstractOperator.h"

class PrewittOperator :	public AbstractOperator {

public:
	CvMat* getHorizontalKernelMatrix() {
		float matrix[9] = {-1, 0, 1,
						   -1, 0, 1,
						   -1, 0, 1 };
		CvMat* kernel = cvCreateMat(3, 3, CV_32FC1);
		return setupKernelMatrixFromArray(kernel, matrix);
	}

	CvMat* getVerticalKernelMatrix() {
		float matrix[9] = {-1,-1,-1,
							0, 0, 0,
							1, 1, 1 };
		CvMat* kernel = cvCreateMat(3, 3, CV_32FC1);
		return setupKernelMatrixFromArray(kernel, matrix);
	}
};

