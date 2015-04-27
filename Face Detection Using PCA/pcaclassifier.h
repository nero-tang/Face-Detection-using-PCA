#ifndef PCACLASSIFIER_H
#define PCACLASSIFIER_H

#include <QThread>
#include <QTime>
#include "opencv2/opencv.hpp"

#define DEFAULT_RETAINED_VARIANCE 50.0
#define DEFAULT_TEMPLATE_WIDTH  20
#define DEFAULT_TEMPLATE_HEIGHT 20

class PCAClassifier : public QThread
{
	Q_OBJECT
	Q_ENUMS(SVMType)
	Q_ENUMS(KernelType)

public:
	explicit PCAClassifier(QObject *parent = 0);
	~PCAClassifier();

	enum SVMType
	{
		C_SVC = CvSVM::C_SVC,
		NU_SVC = CvSVM::NU_SVC,
		ONE_CLASS = CvSVM::ONE_CLASS,
		EPS_SVR = CvSVM::EPS_SVR,
		NU_SVR = CvSVM::NU_SVR
	};
	enum KernelType
	{
		LINEAR = CvSVM::LINEAR,
		POLY = CvSVM::POLY,
		RBF = CvSVM::RBF,
		SIGMOID = CvSVM::SIGMOID
	};

	enum TemplateType
	{
		FaceTemplate = 0,
		Nonface
	};
	
	bool isAvailable() const;
	cv::Size templateSize() const;
	cv::Mat meanface() const;
	cv::Mat templateImage(int index, TemplateType type) const;
	std::vector<cv::Mat> eigenfaces() const;
	std::vector<float> eigenvalues() const;
	void setTemplates(const std::vector<cv::Mat>& vector, TemplateType type);
	void setTemplateSize(cv::Size tempSize);
	bool predict(const cv::Mat& img) const;
	void setRetainedVariance(double rv);
	void setSVMParameters(const CvSVMParams& params);

	friend class PCAClassifierDialog;

protected:
	void run();
	
private:
	cv::Mat templates[2];
	cv::Size tempSize;
	double retainedVariance;
	CvSVM svm;
	CvSVMParams svmParams;
	cv::PCA pca;

signals:
	void postMessage(const QString& msg);
	void processStarted();
	void processFinished();
};


#endif // PCACLASSIFIER_H
