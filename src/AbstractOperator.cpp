#include "AbstractOperator.h"

/**
 * Применить оператор поиска граней.
 */
IplImage* AbstractOperator::applyOperator(IplImage* sourceImage) {
	IplImage* horizontalEdges = cvCloneImage(sourceImage);
	CvMat* horizontalMatrix = getHorizontalKernelMatrix();
	cvFilter2D(sourceImage, horizontalEdges, horizontalMatrix, cvPoint(-1,-1));
	cvReleaseMat(&horizontalMatrix);

	IplImage* verticalEdges = cvCloneImage(sourceImage);
	CvMat* verticalMatrix = getVerticalKernelMatrix();
	cvFilter2D(sourceImage, verticalEdges, verticalMatrix, cvPoint(-1,-1));
	cvReleaseMat(&verticalMatrix);

	sourceImage = applyGradient(horizontalEdges, verticalEdges);
	return sourceImage;
}

/**
 * Заполнить матрицу свёртки значениями из массива.
 */
CvMat* AbstractOperator::setupKernelMatrixFromArray(CvMat* kernel, float* matrix) {
	int w = kernel->width;
	for (int y = 0; y < kernel->height; y++) {
		for (int x = 0; x < w; x++) {
			cvSet2D(kernel, 0, 0, cvRealScalar(matrix[y*w+x]));
		}
	}
	return kernel;
}

IplImage* AbstractOperator::applyGradient(IplImage* horiz, IplImage* vert) {
	int ch = horiz->nChannels;
	for(int y = 0; y < horiz->height; y++) {
		uchar* pHor = (uchar*) (horiz->imageData + y * horiz->widthStep);
		uchar* pVert = (uchar*) (vert->imageData + y * vert->widthStep);
		for(int x = 0; x < horiz->width; x++) {
			// Вычисляем значения для каждого канала
			for (int i = 0; i < ch; i++) {
				pHor[ch*x+i] = calculateGradient(pHor[ch*x+i],  pVert[ch*x+i]);
			}
		}
	}
	return horiz;
}

uchar AbstractOperator::calculateGradient(uchar pix1, uchar pix2) {
	return (uchar) sqrt(double(pix1*pix1 + pix2*pix2));
}