#ifndef PCACLASSIFIERDIALOG_H
#define PCACLASSIFIERDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "pcaclassifier.h"

class PCAClassifierDialog : public QDialog
{
	Q_OBJECT

public:
	PCAClassifierDialog(PCAClassifier *classifier, QWidget *parent = 0);
	~PCAClassifierDialog();
	
private:
	// UI components
	QDoubleSpinBox *varianceSpinBox;
	QComboBox *svmTypeComboBox;
	QComboBox *kernelTypeComboBox;
	QDoubleSpinBox *degreeSpinBox;
	QDoubleSpinBox *gammaSpinBox;
	QDoubleSpinBox *coef0SpinBox;
	QDoubleSpinBox *CvalueSpinBox;
	QDoubleSpinBox *nuSpinBox;
	QDoubleSpinBox *pSpinBox;

	PCAClassifier *m_classifier;
	void initParameters();

private slots:
	void onStartClicked();
};

#endif // PCACLASSIFIERDIALOG_H
