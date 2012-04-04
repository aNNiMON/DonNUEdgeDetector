#include "EdgeDetector.h"

EdgeDetector::EdgeDetector() {}

/**
 * Деструктор.
 * Закрытие окон созданных при помощи OpenCV и освобождение ресурсов.
 */
EdgeDetector::~EdgeDetector() {
	cvReleaseCapture(&camera);
	cvDestroyAllWindows();
}

/**
 * Инициализация камеры, окон и первоначальных параметров.
 */
void EdgeDetector::init(int deviceNumber) {
	camera = initCamera(deviceNumber);
	imageSize = getCameraImageSize(camera);
	cvNamedWindow(getWindowName(), CV_WINDOW_AUTOSIZE);
}

/**
 * Обновление выводимой информации.
 */
void EdgeDetector::update() {
	if (camera == NULL) return;
	IplImage *tempFrame;
	cameraFrame = cvQueryFrame(camera);
	resultFrame = cvCloneImage(cameraFrame);
	if (isGrayScaleEffect) {
		resultFrame = cvCreateImage(imageSize, cameraFrame->depth, CV_LOAD_IMAGE_GRAYSCALE);
		cvCvtColor(cameraFrame, resultFrame, CV_BGR2GRAY);
	}
	if (isInverseEffect) {
		tempFrame = cvCloneImage(resultFrame);
		cvNot(tempFrame, resultFrame);
	}

	cvShowImage(getWindowName(), resultFrame);
}

/**
 * Сохранить скриншот результирующего фрейма.
 */
void EdgeDetector::snapshot() {
	if (resultFrame == NULL) return;
	cvSaveImage("Capture.jpg", resultFrame);
}

/**
 * Выставить состояние эффекта.
 */
void EdgeDetector::setEffects(UINT effect, bool enabled) {
	switch(LOWORD(effect)) {
		case ID_EF_ORIGINAL:
			isOriginalEffect = enabled;
			break;
		case ID_EF_GRAYSCALE:
			isGrayScaleEffect = enabled;
			break;
		case ID_EF_INVERSE:
			isInverseEffect = enabled;
			break;
	}
}


CvCapture* EdgeDetector::initCamera(int deviceNumber) {
	//return cvCreateCameraCapture(deviceNumber);
	return cvCaptureFromCAM(deviceNumber);
}

CvSize EdgeDetector::getCameraImageSize(CvCapture* camera) {
	double width = cvGetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH);
	double height = cvGetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT);
	return cvSize(width, height);
}

const char* EdgeDetector::getWindowName() {
	return "Окно просмотра";
}
