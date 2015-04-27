#include "appwindow.h"
#include "Global.h"

appWindow::appWindow(QWidget *parent)
	: QMainWindow(parent), 
	m_classifier(this), 
	m_classifierDialog(0),
	m_detector(this, &m_classifier), 
	m_detectorDialog(0)
{
	// Setup UI
	ui.setup(this);

	qRegisterMetaType< QList<QTreeWidgetItem *> >("QList<QTreeWidgetItem *>");

	// Setup signals & slots
	connect(&m_classifier, SIGNAL(postMessage(const QString&)), this, SLOT(printMessage(const QString&)));
	connect(&m_classifier, SIGNAL(processStarted()), this, SLOT(busyProgressbar()));
	connect(&m_classifier, SIGNAL(processFinished()), this, SLOT(onTrainingFinished()));

	connect(&m_detector, SIGNAL(postMessage(const QString&)), this, SLOT(printMessage(const QString&)));
	connect(&m_detector, SIGNAL(processStarted()), this, SLOT(busyProgressbar()));
	connect(&m_detector, SIGNAL(processFinished()), this, SLOT(onDetectionFinshed()));

	connect(&m_loader, SIGNAL(postMessage(const QString&)), this, SLOT(printMessage(const QString&)));
	connect(&m_loader, SIGNAL(updateProgress(int)), ui.progressBar, SLOT(setValue(int)));
	connect(&m_loader, SIGNAL(updateTemplateInfo(const QList<QTreeWidgetItem *>&, PCAClassifier::TemplateType)), this, SLOT(loadTemplateInfoList(const QList<QTreeWidgetItem *>&, PCAClassifier::TemplateType)));
	connect(&m_loader, SIGNAL(finished()), this, SLOT(resetProgressbar()));

	connect(ui.faceTempTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(displaySelectedTreeWidgetItem(QTreeWidgetItem*)));
	connect(ui.nonfaceTempTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(displaySelectedTreeWidgetItem(QTreeWidgetItem*)));
	connect(ui.eigenfaceTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(displaySelectedTreeWidgetItem(QTreeWidgetItem*)));
	connect(ui.detectResultTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(displaySelectedTreeWidgetItem(QTreeWidgetItem*)));
	


	connect(ui.loadImageAct, &QAction::triggered, this, &appWindow::loadImage);
	connect(ui.loadFaceTempAct, &QAction::triggered, this, &appWindow::loadFaceTemplate);
	connect(ui.loadNonfaceTempAct, &QAction::triggered, this, &appWindow::loadNonFaceTemplate);
	connect(ui.startTrainAct, &QAction::triggered, this, &appWindow::performPCATraining);
	connect(ui.startDetectAct, &QAction::triggered, this, &appWindow::performFaceDetection);

	connect(ui.aboutAction, &QAction::triggered, this, &appWindow::showAbout);
	
}

appWindow::~appWindow()
{
	// Saving Settings
	m_classifier.quit();
	m_classifier.wait();
	m_detector.quit();
	m_detector.wait();
}

void appWindow::updateTemplateHeight(int height)
{
	cv::Size oldSize = m_classifier.templateSize();
	cv::Size newSize = cv::Size(oldSize.width, height);
	m_classifier.setTemplateSize(newSize);
}

void appWindow::updateTemplateWidth(int width)
{
	cv::Size oldSize = m_classifier.templateSize();
	cv::Size newSize = cv::Size(width, oldSize.height);
	m_classifier.setTemplateSize(newSize);
}

void appWindow::printMessage(const QString& msg)
{
	QDateTime time;
	QString logStr = time.currentDateTime().toString("yyyy.MM.dd HH:mm:ss ");
	logStr.append(msg);
	ui.logList->append(logStr);
	//ui.logList->scrollToItem(ui.logList->item(ui.logList->count() - 1));
}

void appWindow::loadImage()
{
	QStringList formats;
	foreach(QByteArray format, QImageReader::supportedImageFormats())
	if (format.toLower() == format)
	{
		formats.append("*." + format);
	}
	
	QString filename = QFileDialog::getOpenFileName(this, 
		tr("Please select an image"), QDir::currentPath(), 
		tr("Image files (%1)").arg(formats.join(' ')));

	if (filename.isEmpty())
	{
		return;
	}

	cv::Mat image = cv::imread(filename.toLocal8Bit().data());
	if (image.empty())
	{
		QMessageBox::warning(this, tr("Image Viewer"), tr("Cannot load file %1").arg(filename));
		return;
	}
	m_detector.setImage(image);
	ui.originalImageHolder->setPixmap(QPixmap::fromImage(Mat2QImage(image)));
	printMessage(tr("Image loaded from %1").arg(filename));
}

void appWindow::loadFaceTemplate()
{
	loadTemplates(PCAClassifier::FaceTemplate);
}

void appWindow::loadNonFaceTemplate()
{
	loadTemplates(PCAClassifier::Nonface);
}

void appWindow::loadTemplates(PCAClassifier::TemplateType type)
{
	static const QStringList dialogTitle = QStringList() << "Import face templates" << "Import non-face templates";

	QString path = QFileDialog::getExistingDirectory(this, 
		dialogTitle.at(type), 
		QDir::currentPath(), 
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (path.isEmpty())
	{
		return;
	}

	QDir dir(path);
	QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files | QDir::NoSymLinks, QDir::Name);
	if (fileInfoList.isEmpty())
	{
		QMessageBox::warning(this, dialogTitle.at(type), tr("%1 is an empty folder.").arg(path));
		return;
	}

	busyProgressbar(fileInfoList.size());
	ui.progressBar->setValue(0);
	m_loader.loadTemplates(&m_classifier, fileInfoList, type);
}

void appWindow::onTrainingFinished()
{
	ui.meanfaceHolder->setPixmap(QPixmap::fromImage(Mat2QImage(m_classifier.meanface())));
	QList<QTreeWidgetItem *> eigenfaceInfoList;
	int eigenfaces = m_classifier.eigenvalues().size();
	for (int i = 0; i < eigenfaces; ++i)
	{
		QStringList eigenfaceInfo = (QStringList() << QString::number(i)
			<< QString::number(m_classifier.eigenvalues()[i]));
		eigenfaceInfoList.append(new QTreeWidgetItem(eigenfaceInfo));
	}
	setTreeWigetInfoList(eigenfaceInfoList, AppUI::EigenfaceTree);
	resetProgressbar();
}

void appWindow::onDetectionFinshed()
{
	ui.skinSgmtImageHolder->setPixmap(QPixmap::fromImage(Mat2QImage(m_detector.image(PCADetector::SkinSegmented))));
	cv::Mat markedImage = m_detector.image(PCADetector::Origianl).clone();

	// Tree widget info list
	QList<QTreeWidgetItem *> resultInfoList;
	for (int i = 0; i < m_detector.results().size(); ++i)
	{
		cv::Rect rect = m_detector.results()[i];
		QStringList resultInfo = QStringList() << QString::number(i)
			<< tr("X: %1, Y: %2").arg(rect.x).arg(rect.y)
			<< tr("%1 x %2").arg(rect.width).arg(rect.height);
		resultInfoList.append(new QTreeWidgetItem(resultInfo));
		rectangle(markedImage, rect, cv::Scalar(255, 255, 0), 1);

	}
	setTreeWigetInfoList(resultInfoList, AppUI::DetectResultTree);
	ui.markedImageHolder->setPixmap(QPixmap::fromImage(Mat2QImage(markedImage)));
	resetProgressbar();
}

void appWindow::loadTemplateInfoList(const QList<QTreeWidgetItem *>& templateInfos, PCAClassifier::TemplateType type)
{
	setTreeWigetInfoList(templateInfos, static_cast<AppUI::TreeWigetType>(type));
}

void appWindow::setTreeWigetInfoList(const QList<QTreeWidgetItem *>& templateInfos, AppUI::TreeWigetType type)
{
	ui.elemViewTab->setCurrentIndex(type);
	QTreeWidget *treeWiget = static_cast<QTreeWidget *>(ui.elemViewTab->currentWidget());
	treeWiget->clear();
	treeWiget->addTopLevelItems(templateInfos);
}

void appWindow::displaySelectedTreeWidgetItem(QTreeWidgetItem *selectedItem)
{
	AppUI::TreeWigetType type = static_cast<AppUI::TreeWigetType>(ui.elemViewTab->currentIndex());
	QTreeWidget *treeWidget = static_cast<QTreeWidget *>(ui.elemViewTab->currentWidget());
	int index = treeWidget->indexOfTopLevelItem(selectedItem);
	cv::Mat imageToBeDisplayed;
	switch (type)
	{
	case AppUI::FaceTemplateTree:
	case AppUI::NonfaceTemplateTree:
		imageToBeDisplayed = m_classifier.templateImage(index, static_cast<PCAClassifier::TemplateType>(type));
		break;
	case AppUI::EigenfaceTree:
		imageToBeDisplayed = m_classifier.eigenfaces()[index];
		break;
	case AppUI::DetectResultTree:
		imageToBeDisplayed = m_detector.faceDetectedAtIndex(index);
		break;
	default:
		imageToBeDisplayed = cv::Mat::zeros(m_classifier.templateSize(), CV_8UC1);
		break;
	}
	ui.elementHolder->setPixmap(QPixmap::fromImage(Mat2QImage(imageToBeDisplayed)));
}

void appWindow::performPCATraining()
{
	if (!m_classifierDialog)
	{
		m_classifierDialog = new PCAClassifierDialog(&m_classifier, this);
	}
	m_classifierDialog->exec();
}

void appWindow::performFaceDetection()
{
	if (!m_detectorDialog)
	{
		m_detectorDialog = new PCADetectorDialog(&m_detector, this);
	}
	m_detectorDialog->exec();
}

void appWindow::busyProgressbar(int maxProgress)
{
	ui.progressBar->setRange(0, maxProgress);
	ui.loadImageAct->setEnabled(false);
	ui.loadFaceTempAct->setEnabled(false);
	ui.loadNonfaceTempAct->setEnabled(false);
	ui.startTrainAct->setEnabled(false);
	ui.startDetectAct->setEnabled(false);
}

void appWindow::resetProgressbar()
{
	ui.progressBar->setMaximum(1);
	ui.progressBar->reset();
	ui.loadImageAct->setEnabled(true);
	ui.loadFaceTempAct->setEnabled(true);
	ui.loadNonfaceTempAct->setEnabled(true);
	ui.startTrainAct->setEnabled(true);
	ui.startDetectAct->setEnabled(true);
}

void appWindow::showAbout()
{
	QMessageBox::about(this, "About", aboutProject());
}

