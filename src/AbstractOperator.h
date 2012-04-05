#pragma once

#include <cv.h>

/**
 * Абстрактный класс оператора поиска граней.
 */
class AbstractOperator {
public:
	IplImage* applyOperator(IplImage* sourceImage);
	void createMatrix();

protected:
	virtual void createHorizontalKernelMatrix() = 0;
	virtual void createVerticalKernelMatrix() = 0;
	CvMat* setupKernelMatrixFromArray(CvMat* sourceMatrix, float* matrix);

protected:
	CvMat* horizontalMatrix;
	CvMat* verticalMatrix;

private:
	IplImage* applyGradient(IplImage* horizontalEdges, IplImage* verticalEdges);
	uchar calculateGradient(uchar pix1, uchar pix2);
};

