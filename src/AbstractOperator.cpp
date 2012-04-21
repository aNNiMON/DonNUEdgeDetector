#include "AbstractOperator.h"

/**
 * Применить оператор поиска граней.
 */
IplImage* AbstractOperator::applyOperator(IplImage* sourceImage) {
	// Применение горизонтального фильтра выделения граней
	IplImage* horizontalEdges = cvCloneImage(sourceImage);
	cvFilter2D(sourceImage, horizontalEdges, horizontalMatrix, cvPoint(-1,-1));

	// Применение вертикального фильтра выделения граней
	IplImage* verticalEdges = cvCloneImage(sourceImage);
	cvFilter2D(sourceImage, verticalEdges, verticalMatrix, cvPoint(-1,-1));

	// Объединение двух изображений в одно (G = sqrt(Gx^2 + Gy^2))
	horizontalEdges = applyGradient(horizontalEdges, verticalEdges);
	cvReleaseImage(&sourceImage);
	cvReleaseImage(&verticalEdges);
	return horizontalEdges;
}

/**
 * Создать матрицы свертки.
 */
void AbstractOperator::createMatrix() {
	createHorizontalKernelMatrix();
	createVerticalKernelMatrix();
}

/**
 * Заполнить матрицу свёртки значениями из массива.
 */
CvMat* AbstractOperator::setupKernelMatrixFromArray(CvMat* kernel, float* matrix) {
	int w = kernel->width;
	for (int y = 0; y < kernel->height; y++) {
		for (int x = 0; x < w; x++) {
			cvSet2D(kernel, y, x, cvRealScalar(matrix[y*w+x]));
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
				if (pHor[ch*x+i] > 255) pHor[ch*x+i] = 255;
			}
		}
	}
	return horiz;
}

uchar AbstractOperator::calculateGradient(uchar pix1, uchar pix2) {
	return (uchar) sqrt(double(pix1*pix1 + pix2*pix2));
}