#include "pcaclassifier.h"


PCAClassifier::PCAClassifier(QObject *parent)
	: QThread(parent),
	retainedVariance(DEFAULT_RETAINED_VARIANCE),
	tempSize(DEFAULT_TEMPLATE_WIDTH, DEFAULT_TEMPLATE_HEIGHT)
{
	// Register Meta type
	qRegisterMetaType<PCAClassifier::TemplateType>("PCAClassifier::TemplateType");
}

PCAClassifier::~PCAClassifier()
{

}

bool PCAClassifier::isAvailable() const
{
	return !pca.eigenvalues.empty() && svm.get_support_vector_count();
}

cv::Size PCAClassifier::templateSize() const
{
	return tempSize;
}

cv::Mat PCAClassifier::templateImage(int index, TemplateType type) const
{
	if (templates[type].empty())
	{
		return cv::Mat::zeros(tempSize, CV_8UC1);
	}
	cv::Mat templateImage;
	templates[type].col(index).convertTo(templateImage, CV_8UC1, 255.0);
	return templateImage.reshape(1, tempSize.height);
}

void PCAClassifier::setTemplates(const std::vector<cv::Mat>& vector, TemplateType type)
{
	if (vector.empty())
	{
		return;
	}

	templates[type].create(tempSize.area(), vector.size(), CV_32FC1);

	for (int i = 0; i != vector.size(); ++i)
	{
		cv::Mat col_temp = templates[type].col(i);
		vector[i].reshape(1, tempSize.area()).convertTo(col_temp, CV_32FC1, 1 / 255.0f);
	}
}

void PCAClassifier::setTemplateSize(cv::Size _tempSize)
{
	tempSize = _tempSize;
}

cv::Mat PCAClassifier::meanface() const
{
	cv::Mat meanface(tempSize.height, tempSize.width, CV_8UC1, cv::Scalar(0));
	if (pca.mean.empty())
	{
		return meanface;
	}

	cv::normalize(pca.mean.reshape(1, tempSize.height), meanface, 0, 255, cv::NORM_MINMAX, CV_8UC1);
	return meanface;
}

std::vector<cv::Mat> PCAClassifier::eigenfaces() const
{
	std::vector<cv::Mat> eigenfaces;
	if (pca.eigenvectors.empty())
	{
		return eigenfaces;
	}

	int princomps = pca.eigenvalues.rows;
	for (int i = 0; i < princomps; ++i)
	{
		cv::Mat eigenface(tempSize.height, tempSize.width, CV_8UC1);
		cv::normalize(pca.eigenvectors.row(i).reshape(1, tempSize.height), eigenface, 0, 255, cv::NORM_MINMAX, CV_8UC1);
		eigenfaces.push_back(eigenface);
	}
	return eigenfaces;
}

std::vector<float> PCAClassifier::eigenvalues() const
{
	std::vector<float> eigenvalues;
	if (pca.eigenvalues.empty())
	{
		return eigenvalues;
	}

	int princomps = pca.eigenvalues.rows;
	const float *ptr = pca.eigenvalues.reshape(1, 1).ptr<float>(0);
	eigenvalues = std::vector<float>(ptr, ptr + princomps);

	return eigenvalues;
}

void PCAClassifier::setRetainedVariance(double rv)
{
	retainedVariance = rv;
}

void PCAClassifier::setSVMParameters(const CvSVMParams& params)
{
	svmParams = params;
}

bool PCAClassifier::predict(const cv::Mat& img) const
{
	return svm.predict(pca.project(img)) > 0;
}

void PCAClassifier::run()
{
	// Status check
	if (templates[FaceTemplate].empty() && templates[Nonface].empty())
	{
		emit postMessage(tr("<strong>WARNING:</strong> Please import both face and non-face templates."));
		return;
	}
	else if (templates[FaceTemplate].empty())
	{
		emit postMessage(tr("<strong>WARNING:</strong> Please import face templates."));
		return;
	}
	else if (templates[Nonface].empty())
	{
		emit postMessage(tr("<strong>WARNING:</strong> Please import non-face templates."));
		return;
	}

	// Perform classification
	emit processStarted();
	emit postMessage("PCA training started.");
	QTime time;
	time.start();

	pca.computeVar(templates[FaceTemplate], cv::Mat(), CV_PCA_DATA_AS_COL, retainedVariance);
	emit postMessage(tr("PCA model generated, <strong>%1</strong> principal components retained.").arg(pca.eigenvalues.rows));
	
	int faceTempSize = templates[FaceTemplate].cols;
	int nonfaceTempSize = templates[Nonface].cols;

	cv::Mat labelMat(faceTempSize + nonfaceTempSize, 1, CV_32FC1);
	for (int i = 0; i < (faceTempSize + nonfaceTempSize); ++i)
	{
		labelMat.at<float>(i) = (i < faceTempSize) ? 1.0f : -1.0f;
	}
	
	cv::Mat trainingDataMat;
	for (int i = 0; i < (faceTempSize + nonfaceTempSize); ++i)
	{
		cv::Mat projection;
		if (i < faceTempSize)
		{
			projection = pca.project(templates[FaceTemplate].col(i));
		}
		else
		{
			projection = pca.project(templates[Nonface].col(i - faceTempSize));
		}
		trainingDataMat.push_back(projection.reshape(1, 1));
	}

	svm.train(trainingDataMat, labelMat, cv::Mat(), cv::Mat(), svmParams);

	emit postMessage(tr("SVM training completed, <strong>%1<strong> support vectors generated.").arg(svm.get_support_vector_count()));
	emit postMessage(tr("Classifier training completed in <strong>%1s</strong>.").arg(time.elapsed() / 1000.0));
	emit processFinished();
}