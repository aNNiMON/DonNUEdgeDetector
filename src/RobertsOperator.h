#pragma once
#include "AbstractOperator.h"

class RobertsOperator :	public AbstractOperator {

public:
	void createHorizontalKernelMatrix() {
		float matrix[9] = {0, 0, 0,
						   0, 1, 0,
						   0, 0,-1 };
		horizontalMatrix = cvCreateMat(3, 3, CV_32FC1);
		horizontalMatrix = setupKernelMatrixFromArray(horizontalMatrix, matrix);
	}

	void createVerticalKernelMatrix() {
		float matrix[9] = {0, 0, 0,
						   0, 0, 1,
						   0,-1, 0 };
		verticalMatrix = cvCreateMat(3, 3, CV_32FC1);
		verticalMatrix = setupKernelMatrixFromArray(verticalMatrix, matrix);
	}
};