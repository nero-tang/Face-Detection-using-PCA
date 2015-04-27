#include "Global.h"

QImage Mat2QImage(const cv::Mat& mat)
{
	if (mat.type() == CV_8UC1)
	{
		// Set the color table (used to translate color indexes to qRgb values)
		QVector<QRgb> colorTable;
		for (int i = 0; i < 256; ++i)
		{
			colorTable.push_back(qRgb(i, i, i));
		}
		// Copy input Mat
		const uchar *qImageBuffer = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
		img.setColorTable(colorTable);
		return img;
	}
	// 8-bits unsigned, NO. OF CHANNELS=3
	if (mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *qImageBuffer = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return img.rgbSwapped();
	}
	else
	{
		return QImage();
	}
}

QPixmap Mat2QPixmap(const cv::Mat& mat)
{
	return QPixmap::fromImage(Mat2QImage(mat));
}

QString aboutProject()
{
	static QString about = "<h3>Face Detector using PCA</h3>\n"
		"<p>Version: " + QObject::tr(project_version_string) + "</p>"
		"<p>" + QObject::tr("A face detector based on Qt and OpenCV.\n") + "</p>"
		"<p>" + QObject::tr("Distributed under the MIT license.\n") + "</p>"
		"<p>" + QObject::tr("This is a Demo application for my undergraduate final project:\n") + "</p>"
		"<h4>" + QObject::tr("Face Detection using Principal Component Analysis(PCA)") + "</h4>\n"
		"<p>" + QObject::tr("Project ID: QWAR3") + "</p>"
		"<p>" + QObject::tr("Year: 2012-2013") + "</p>"
		"<p>" + QObject::tr("Supervisor: Mr. Andy Watson") + "</p>"
		"<p>" + QObject::tr("Author: Yufei Tang") + "</p>"
		"<h4>" + QObject::tr("Beijing University of Posts and Telecommunications") + "</h4>\n"
		"<h4>" + QObject::tr("Queen Mary, University of London") + "</h4>\n"
		;
	return about;
}