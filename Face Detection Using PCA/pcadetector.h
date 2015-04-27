#ifndef PCADETECTOR_H
#define PCADETECTOR_H

#include <QThread>
#include <QTime>
#include "pcaclassifier.h"

#define DEFAULT_SCAN_STEP 1
#define DEFAULT_SCALE_RATE 1.2
#define DEFAULT_GROUP_THRESHOLD 1
#define DEFAULT_GROUP_EPS 0.8

class PCADetector : public QThread
{
	Q_OBJECT

public:
	PCADetector(QObject *parent = 0, PCAClassifier *_classifier = 0);
	~PCADetector();
	
	enum ImageType
	{
		Origianl = 0,
		SkinSegmented,
		FaceMarked,
		ImageTypeCount
	};

	const std::vector<cv::Rect>& results() const;
	cv::Mat faceDetectedAtIndex(int index) const;
	const cv::Mat& image(ImageType type) const;
	void setClassifier(PCAClassifier *_classifier);
	void setImage(const cv::Mat& image);
	void setEnableSkinSgmt(bool enableSkinSgmt);
	void setScanStep(int scanStep);
	void setScaleRate(double scaleRate);
	void setGroupThreshold(int threshold);
	void setGroupEps(double eps);

	friend class PCADetectorDialog;

protected:
	void run();

private:
	PCAClassifier *m_classifier;
	bool m_enableSkinSgmt;
	int m_scanStep;
	double m_scaleRate;
	int m_groupThreshold;
	double m_groupEps;
	cv::Mat m_images[ImageTypeCount];
	std::vector<cv::Rect> m_resultRects;

	void performSkinSegmentation();

signals :
	void postMessage(const QString& msg);
	void processStarted();
	void processFinished();
};

#endif // PCADETECTOR_H
