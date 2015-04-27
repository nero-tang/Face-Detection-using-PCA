#include "pcadetector.h"

PCADetector::PCADetector(QObject *parent, PCAClassifier *_classifier)
	: QThread(parent),
	m_classifier(_classifier),
	m_enableSkinSgmt(true),
	m_scanStep(DEFAULT_SCAN_STEP), 
	m_scaleRate(DEFAULT_SCALE_RATE),
	m_groupThreshold(DEFAULT_GROUP_THRESHOLD),
	m_groupEps(DEFAULT_GROUP_EPS)
{

}

PCADetector::~PCADetector()
{

}

const std::vector<cv::Rect>& PCADetector::results() const
{
	return m_resultRects;
}

cv::Mat PCADetector::faceDetectedAtIndex(int index) const
{
	if (!m_resultRects.size())
	{
		return cv::Mat::zeros(m_classifier->templateSize(), CV_8UC1);
	}

	return m_images[SkinSegmented](m_resultRects[index]);
}

const cv::Mat& PCADetector::image(ImageType type) const
{
	return m_images[type];
}

void PCADetector::setClassifier(PCAClassifier *_classifier)
{
	m_classifier = _classifier;
}

void PCADetector::setImage(const cv::Mat& image)
{
	m_images[Origianl] = image;
}

void PCADetector::setEnableSkinSgmt(bool enableSkinSgmt)
{
	m_enableSkinSgmt = enableSkinSgmt;
}

void PCADetector::setScanStep(int scanStep)
{
	m_scanStep = scanStep;
}

void PCADetector::setScaleRate(double scaleRate)
{
	m_scaleRate = scaleRate;
}

void PCADetector::setGroupThreshold(int threshold)
{
	m_groupThreshold = threshold;
}

void PCADetector::setGroupEps(double eps)
{
	m_groupEps = eps;
}


// Constants for skin segmentation algorithms, may be variable as settings in the future
#define SKIN_SGMT_BLUR true
#define SKIN_SGMT_SMALL_CONTOUR_THRESHOLD 400
#define SKIN_SGMT_DILATION_SIZE 9
#define SKIN_SGMT_EROSION_SIZE 9
#define SKIN_SGMT_DILATION_TIMES 3
#define SKIN_SGMT_EROSION_TIMES 3
static const double SKIN_SGMT_PARAM_A = 25.39;
static const double SKIN_SGMT_PARAM_B = 14.03;
static const double SKIN_SGMT_PARAM_ECX = 1.60;
static const double SKIN_SGMT_PARAM_ECY = 2.41;
static const double SKIN_SGMT_PARAM_THETA = 2.53;
static const double SKIN_SGMT_PARAM_CX = 109.38;
static const double SKIN_SGMT_PARAM_CY = 152.02;
static const double SKIN_SGMT_PARAM_CGL = 85.0;
static const double SKIN_SGMT_PARAM_CGR = 135.0;
static const double SKIN_SGMT_PARAM_CRL = 260.0;
static const double SKIN_SGMT_PARAM_CRR = 280.0;
static const double SKIN_SGMT_PARAM_YL = 60.0;
static const cv::Mat SKIN_SGMT_ROTATION_MAT = (cv::Mat_<double>(2, 2) << cos(SKIN_SGMT_PARAM_THETA), sin(SKIN_SGMT_PARAM_THETA),
	-sin(SKIN_SGMT_PARAM_THETA), cos(SKIN_SGMT_PARAM_THETA));
#define SQUARE(x) ((x) * (x))
void PCADetector::performSkinSegmentation()
{
	if (m_images[Origianl].channels() == 1)
	{
		// If the original is grayscale, then skin segmentation is unavailable.
		emit postMessage("Original image is grayscale, skin segmentation is unavailable.");
		m_images[SkinSegmented] = m_images[Origianl];
		return;
	}

	cv::cvtColor(m_images[Origianl], m_images[SkinSegmented], CV_BGR2GRAY);
	if (!m_enableSkinSgmt)
	{
		// If skin segmentation is not required, then return.
		return;
	}

	int imgRows = m_images[Origianl].rows;
	int imgCols = m_images[Origianl].cols;
	int imgChannels = m_images[Origianl].channels();
	cv::Mat binaryMask = cv::Mat::zeros(imgRows, imgCols, CV_8UC1);
	cv::Mat YCrCbImage;

	cv::cvtColor(m_images[Origianl], YCrCbImage, CV_BGR2YCrCb);
	
	// Blur the gray scale image if necessary
	if (SKIN_SGMT_BLUR)
	{
		GaussianBlur(m_images[SkinSegmented], m_images[SkinSegmented], cv::Size(3, 3), 1.0);
	}
	
	// Check each pixel to see if it matches the criteria of the color of skin
	for (int row = 0; row < imgRows; ++row)
	{
		const uchar *ptr_BGRData = m_images[Origianl].ptr<uchar>(row);
		const uchar *ptr_YCrCbData = YCrCbImage.ptr<uchar>(row);
		uchar *ptr_MaskData = binaryMask.ptr<uchar>(row);

		for (int col = 0; col < imgCols; ++col)
		{
			double  R = ptr_BGRData[col * imgChannels + 2];
			double	G = ptr_BGRData[col * imgChannels + 1];
			double  B = ptr_BGRData[col * imgChannels];
			double  Y = ptr_YCrCbData[col * imgChannels];
			double Cr = ptr_YCrCbData[col * imgChannels + 1];
			double Cb = ptr_YCrCbData[col * imgChannels + 2];
			double Cg = 128.0 - 0.318 * R + 0.439 * G - 0.121 * B;

			cv::Mat modified_CrCb_Mat = SKIN_SGMT_ROTATION_MAT *
				(cv::Mat_<double>(2, 1) << Cb - SKIN_SGMT_PARAM_CX, Cr - SKIN_SGMT_PARAM_CY);
			double modCr = modified_CrCb_Mat.at<double>(0, 0);
			double modCb = modified_CrCb_Mat.at<double>(1, 0);

			if (Cr < SKIN_SGMT_PARAM_CRR - Cg &&
				Cr > SKIN_SGMT_PARAM_CRL - Cg &&
				Cg < SKIN_SGMT_PARAM_CGR      &&
				Cg > SKIN_SGMT_PARAM_CGL      &&
				 Y > SKIN_SGMT_PARAM_YL       &&
				 SQUARE((modCr - SKIN_SGMT_PARAM_ECX) / SKIN_SGMT_PARAM_A) +
				 SQUARE((modCb - SKIN_SGMT_PARAM_ECY) / SKIN_SGMT_PARAM_B) < 1)
			{
				ptr_MaskData[col] = 1;
			}
		}
	}

	// Perform morphological operations to improve the skin mask
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierachy;

	// Remove small contours
	findContours(binaryMask.clone(), contours, hierachy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	if (contours.size())
	{
		for (int idx = 0; idx >= 0; idx = hierachy[idx][0])
		{
			const std::vector<cv::Point> &contour = contours[idx];
			if (fabs(contourArea(cv::Mat(contour))) <= SKIN_SGMT_SMALL_CONTOUR_THRESHOLD)
			{
				drawContours(binaryMask, contours, idx, cv::Scalar(0), CV_FILLED, 8, hierachy);
			}
		}
	}

	// Apply dilation
	cv::Mat dilateKernel = cv::Mat::ones(SKIN_SGMT_DILATION_SIZE, SKIN_SGMT_DILATION_SIZE, CV_8UC1);
	dilate(binaryMask, binaryMask, dilateKernel, cv::Point(-1, -1), SKIN_SGMT_DILATION_TIMES);

	// Fill holes in contours
	contours.clear();
	hierachy.clear();
	findContours(binaryMask.clone(), contours, hierachy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	if (contours.size())
	{
		for (int idx = 0; idx >= 0; idx = hierachy[idx][0])
		{
			drawContours(binaryMask, contours, idx, cv::Scalar(1), CV_FILLED, 8, hierachy);
		}
	}

	// Apply erosion
	cv::Mat erodeKernel = cv::Mat::ones(SKIN_SGMT_EROSION_SIZE, SKIN_SGMT_EROSION_SIZE, CV_8UC1);
	erode(binaryMask, binaryMask, erodeKernel, cv::Point(-1, -1), SKIN_SGMT_EROSION_TIMES);

	// Apply binary mask to grayscale image
	m_images[SkinSegmented] = m_images[SkinSegmented].mul(binaryMask);
	emit postMessage("Skin segmentation completed.");
}


void PCADetector::run()
{
	// Status check
	if (!m_classifier)
	{
		emit postMessage(tr("<strong>ERROR:</strong> Classifier NOT found."));
		return;
	}

	if (!m_classifier->isAvailable())
	{
		emit postMessage(tr("<strong>ERROR:</strong> Classifier NOT trained."));
		return;
	}

	if (m_images[Origianl].empty())
	{
		emit postMessage(tr("<strong>ERROR:</strong> No image selected."));
		return;
	}

	// Perform face detection
	emit processStarted();
	QTime time;
	time.start();
	// First of all, perform skin segmentation on the imported image
	emit postMessage("Face detection started.");
	performSkinSegmentation();

	cv::Mat downsampledImage = m_images[SkinSegmented].clone();
	cv::Mat detectWindow;

	cv::Size windowSize = m_classifier->templateSize();

	double scale = 1.0;
	int imgCols = downsampledImage.cols;
	int imgRows = downsampledImage.rows;
	m_resultRects.clear();

	int iteration = 0;
	while (imgCols > windowSize.width && imgRows > windowSize.height)
	{
		iteration++;
		int results = 0;

		for (int row = 0; row < imgRows - windowSize.height; row += m_scanStep)
		{
			for (int col = 0; col < imgCols - windowSize.width; col += m_scanStep)
			{
				getRectSubPix(downsampledImage,
					windowSize,
					cv::Point2f(col + windowSize.width / 2.0,
					row + windowSize.height / 2.0),
					detectWindow);

				// Continue if detect window contains value of 0
				if (countNonZero(detectWindow) != windowSize.area())
				{
					continue;
				}

				equalizeHist(detectWindow, detectWindow);
				detectWindow.reshape(1, windowSize.area()).convertTo(detectWindow, CV_32FC1, 1 / 255.0f);

				if (m_classifier->predict(detectWindow))
				{
					// Marked as face candidate
					int x = col * scale;
					int y = row * scale;
					int width = windowSize.width * scale;
					int height = windowSize.height * scale;
					cv::Rect resultRect(x, y, width, height);
					m_resultRects.push_back(resultRect);

					results++;
				}
			}
		}
		emit postMessage(tr("Iteration <strong>%1</strong> completed, <strong>%2</strong> face candidates detected.").arg(iteration).arg(results));
		// Scale down the image for another iteration
		scale *= m_scaleRate;
		imgCols = m_images[SkinSegmented].cols / scale;
		imgRows = m_images[SkinSegmented].rows / scale;
		resize(m_images[SkinSegmented], downsampledImage, cv::Size(imgCols, imgRows));
	}

	// Group rectangles if necessary
	emit postMessage("Grouping overlapped rectangles.");
	cv::groupRectangles(m_resultRects, m_groupThreshold, m_groupEps);

	emit postMessage(tr("Face detection completed in <strong>%1s</strong>, <strong>%2</strong> faces detected.").arg(time.elapsed() / 1000.0).arg(m_resultRects.size()));
	emit processFinished();
}