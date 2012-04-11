#pragma once
#include "AbstractOperator.h"

class ScharrOperator :	public AbstractOperator {

public:
	void createHorizontalKernelMatrix() {
		float matrix[9] = { 3, 0, -3,
						   10, 0, -10,
						    3, 0, -3 };
		horizontalMatrix = cvCreateMat(3, 3, CV_32FC1);
		horizontalMatrix = setupKernelMatrixFromArray(horizontalMatrix, matrix);
	}

	void createVerticalKernelMatrix() {
		float matrix[9] = { 3, 10, 3,
						    0,  0, 0,
						   -3,-10,-3 };
		verticalMatrix = cvCreateMat(3, 3, CV_32FC1);
		verticalMatrix = setupKernelMatrixFromArray(verticalMatrix, matrix);
	}
};