#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "ui_appwindow.h"
#include "pcaclassifierdialog.h"
#include "pcadetectordialog.h"
#include "templateloader.h"
#include "Global.h"

class appWindow : public QMainWindow
{
	Q_OBJECT

public:
	appWindow(QWidget *parent = 0);
	~appWindow();

private:
	// UI component
	AppUI ui;
	// PCA classifier
	PCAClassifier m_classifier;
	PCAClassifierDialog *m_classifierDialog;
	// PCA detector
	PCADetector m_detector;
	PCADetectorDialog *m_detectorDialog;
	// Template loader
	TemplateLoader m_loader;

	// Private functions
	void loadTemplates(PCAClassifier::TemplateType type);
	void setTreeWigetInfoList(const QList<QTreeWidgetItem *>& templateInfos, AppUI::TreeWigetType type);
	
private slots:
	void printMessage(const QString& msg);
	void updateTemplateWidth(int width);
	void updateTemplateHeight(int height);
	void onTrainingFinished();
	void onDetectionFinshed();
	void loadImage();
	void loadFaceTemplate();
	void loadNonFaceTemplate();
	void loadTemplateInfoList(const QList<QTreeWidgetItem *>& templateInfos, PCAClassifier::TemplateType type);
	void displaySelectedTreeWidgetItem(QTreeWidgetItem *selectedItem);
	void performPCATraining();
	void performFaceDetection();
	void busyProgressbar(int maxProgress = 0);
	void resetProgressbar();
	void showAbout();
};

#endif // APPWINDOW_H
