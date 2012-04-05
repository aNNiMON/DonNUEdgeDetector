#pragma once

#include <cv.h>

/**
 * Абстрактный класс оператора поиска граней.
 */
class AbstractOperator {
public:
	IplImage* applyOperator(IplImage* sourceImage);

protected:
	virtual CvMat* getHorizontalKernelMatrix() = 0;
	virtual CvMat* getVerticalKernelMatrix() = 0;
	CvMat* setupKernelMatrixFromArray(CvMat* sourceMatrix, float* matrix);

private:
	IplImage* applyGradient(IplImage* horizontalEdges, IplImage* verticalEdges);
	uchar calculateGradient(uchar pix1, uchar pix2);

	int numberOfChannels;
};

