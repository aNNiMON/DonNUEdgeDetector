#include "EdgeDetector.h"

EdgeDetector::EdgeDetector() {}

/**
 * Деструктор.
 * Закрытие окон созданных при помощи OpenCV и освобождение ресурсов.
 */
EdgeDetector::~EdgeDetector() {
	cvReleaseCapture(&camera);
	cvDestroyAllWindows();
	delete edgeDetectOperator;
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

	cameraFrame = cvQueryFrame(camera);
	resultFrame = cvCloneImage(cameraFrame);
	
	if (isGrayScaleEffect) {
		IplImage* tempFrame = cvCloneImage(resultFrame);
		resultFrame = cvCreateImage(imageSize, cameraFrame->depth, CV_LOAD_IMAGE_GRAYSCALE);
		cvCvtColor(tempFrame, resultFrame, CV_BGR2GRAY);
	}
	if (!isOriginalEffect) {
		resultFrame = edgeDetectOperator->applyOperator(resultFrame);
	}
	if (isInverseEffect) {
		IplImage* tempFrame = cvCloneImage(resultFrame);
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

/**
 * Переключение оператора поиска граней.
 */
void EdgeDetector::setOperator(UINT typeOperator) {
	switch(LOWORD(typeOperator)) {
		case ID_OP_ROBERTS:
			edgeDetectOperator = new RobertsOperator();
			break;
		case ID_OP_PREWITT:
			edgeDetectOperator = new PrewittOperator();
			break;
		case ID_OP_SOBEL:
			edgeDetectOperator = new SobelOperator();
			break;
	}
}


CvCapture* EdgeDetector::initCamera(int deviceNumber) {
	//return cvCreateCameraCapture(deviceNumber);
	return cvCaptureFromCAM(deviceNumber);
}

CvSize EdgeDetector::getCameraImageSize(CvCapture* camera) {
	int width = (int) cvGetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH);
	int height = (int) cvGetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT);
	return cvSize(width, height);
}

const char* EdgeDetector::getWindowName() {
	return "Окно просмотра";
}
