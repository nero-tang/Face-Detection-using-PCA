#ifndef PCADETECTORDIALOG_H
#define PCADETECTORDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "pcadetector.h"

class PCADetectorDialog : public QDialog
{
	Q_OBJECT

public:
	explicit PCADetectorDialog(PCADetector *detector, QWidget *parent = 0);
	~PCADetectorDialog();

private:
	// UI Controller components
	QSpinBox *scanStepSpinBox;
	QDoubleSpinBox *scaleRateSpinBox;
	QSpinBox *groupThresholdSpinBox;
	QDoubleSpinBox *groupEpsSpinBox;
	QCheckBox *skinSgmtCheckBox;

	// Detector
	PCADetector *m_detector;

	void initControllers();

private slots:
	void onStartClicked();
};

#endif // PCADETECTORDIALOG_H
