#include "EdgeDetector.h"

int EdgeDetector::captureIndex = 0;

EdgeDetector::EdgeDetector() {}

/**
 * Деструктор.
 * Закрытие окон созданных при помощи OpenCV и освобождение ресурсов.
 */
EdgeDetector::~EdgeDetector() {
	cvReleaseCapture(&camera);
	cvReleaseImage(&resultFrame);
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

	cvWaitKey(33);

	cameraFrame = cvQueryFrame(camera);
	cvReleaseImage(&resultFrame);
	
	if (isGrayScaleEffect) {
		IplImage* tempFrame = cvCloneImage(cameraFrame);
		resultFrame = cvCreateImage(imageSize, cameraFrame->depth, CV_LOAD_IMAGE_GRAYSCALE);
		cvCvtColor(tempFrame, resultFrame, CV_BGR2GRAY);
		cvReleaseImage(&tempFrame);
	} else resultFrame = cvCloneImage(cameraFrame);

	if (!isOriginalEffect) {
		if (isStrokeEffect) {
			IplImage* tempFrame = cvCloneImage(resultFrame);
			tempFrame = edgeDetectOperator->applyOperator(tempFrame);
			cvSub(resultFrame, tempFrame, resultFrame);
			cvReleaseImage(&tempFrame);
		} else resultFrame = edgeDetectOperator->applyOperator(resultFrame);
	}

	if (isInverseEffect) {
		IplImage* tempFrame = cvCloneImage(resultFrame);
		cvNot(tempFrame, resultFrame);
		cvReleaseImage(&tempFrame);
	}

	cvShowImage(getWindowName(), resultFrame);
}

/**
 * Сохранить скриншот результирующего фрейма.
 */
void EdgeDetector::snapshot() {
	if (resultFrame == NULL) return;
	char filename[20];
	sprintf(filename, "Capture%d.jpg", captureIndex);
	captureIndex++;
	cvSaveImage(filename, resultFrame);
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
		case ID_EF_STROKE:
			isStrokeEffect = enabled;
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
		case ID_OP_SCHARR:
			edgeDetectOperator = new ScharrOperator();
			break;
	}
	edgeDetectOperator->createMatrix();
}


CvCapture* EdgeDetector::initCamera(int deviceNumber) {
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
