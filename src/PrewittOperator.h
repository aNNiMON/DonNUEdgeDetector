#pragma once
#include "AbstractOperator.h"

class PrewittOperator :	public AbstractOperator {

public:
	void createHorizontalKernelMatrix() {
		float matrix[9] = {-1, 0, 1,
						   -1, 0, 1,
						   -1, 0, 1 };
		horizontalMatrix = cvCreateMat(3, 3, CV_32FC1);
		horizontalMatrix = setupKernelMatrixFromArray(horizontalMatrix, matrix);
	}

	void createVerticalKernelMatrix() {
		float matrix[9] = {-1,-1,-1,
							0, 0, 0,
							1, 1, 1 };
		verticalMatrix = cvCreateMat(3, 3, CV_32FC1);
		verticalMatrix = setupKernelMatrixFromArray(verticalMatrix, matrix);
	}
};

