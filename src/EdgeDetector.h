#pragma once

#include <cv.h>
#include <highgui.h>
#include "resource.h"

/**
 * Класс выделения границ.
 * @author aNNiMON
 */
class EdgeDetector {
public:
	EdgeDetector();
	~EdgeDetector();

	void init(int deviceNumber);
	void update();
	void snapshot();

	void setEffects(UINT effect, bool enabled);

private:
	// инициализация
	CvCapture* initCamera(int deviceNumber);
	CvSize getCameraImageSize(CvCapture* camera);

	const char* getWindowName();

	bool isOriginalEffect, isGrayScaleEffect, isInverseEffect;
	CvCapture* camera;
	CvSize imageSize;
	IplImage *cameraFrame, *resultFrame;
};
