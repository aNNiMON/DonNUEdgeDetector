#pragma once

#include <cv.h>
#include <highgui.h>
#include "resource.h"
#include "RobertsOperator.h"
#include "PrewittOperator.h"
#include "SobelOperator.h"
#include "ScharrOperator.h"


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
	void setOperator(UINT typeOperator);

private:
	// инициализация
	CvCapture* initCamera(int deviceNumber);
	CvSize getCameraImageSize(CvCapture* camera);

	const char* getWindowName();

	bool isOriginalEffect, isGrayScaleEffect, isInverseEffect;
	bool isStrokeEffect;
	static int captureIndex;
	AbstractOperator* edgeDetectOperator;
	CvCapture* camera;
	CvSize imageSize;
	IplImage *cameraFrame, *resultFrame;
};
