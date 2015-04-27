#include "pcaclassifierdialog.h"

PCAClassifierDialog::PCAClassifierDialog(PCAClassifier *classifier, QWidget *parent)
	: QDialog(parent), m_classifier(classifier)
{
	const QMetaObject *metaObj = m_classifier->metaObject();
	QMetaEnum enumType;

	// PCA Settings
	QGroupBox *pcaGroup = new QGroupBox(tr("Principal Component Analysis"));

	varianceSpinBox = new QDoubleSpinBox;
	QLabel *princompsLabel = new QLabel(tr("Retained variance (%):"));

	QHBoxLayout *pcaLayout = new QHBoxLayout;
	pcaLayout->addWidget(princompsLabel);
	pcaLayout->addStretch(1);
	pcaLayout->addWidget(varianceSpinBox);

	pcaGroup->setLayout(pcaLayout);

	// SVM Settings
	QGroupBox *svmGroup = new QGroupBox(tr("Support Vector Machine"));

	QLabel *svmTypeLabel = new QLabel(tr("Type of SVM:"));
	svmTypeComboBox = new QComboBox;
	enumType = metaObj->enumerator(metaObj->indexOfEnumerator("SVMType"));
	for (int i = 0; i < enumType.keyCount(); ++i)
	{
		QString item = tr(enumType.key(i));
		svmTypeComboBox->addItem(item);
	}

	QLabel *kernelTypeLabel = new QLabel(tr("Kernel:"));
	kernelTypeComboBox = new QComboBox;
	enumType = metaObj->enumerator(metaObj->indexOfEnumerator("KernelType"));
	for (int i = 0; i < enumType.keyCount(); ++i)
	{
		QString item = tr(enumType.key(i));
		kernelTypeComboBox->addItem(item);
	}

	QFrame *separator = new QFrame;
	separator->setFrameShape(QFrame::HLine);
	separator->setFrameShadow(QFrame::Sunken);

	QLabel *degreeLabel = new QLabel(tr("degree (POLY):"));
	degreeSpinBox = new QDoubleSpinBox;

	QLabel *gammaLabel = new QLabel(tr("gamma (POLY / RBF / SIGMOID):"));
	gammaSpinBox = new QDoubleSpinBox;

	QLabel *coef0Label = new QLabel(tr("coef0 (POLY / SIGMOID)"));
	coef0SpinBox = new QDoubleSpinBox;

	QLabel *CvalueLabel = new QLabel(tr("C (C_SVC / EPS_SVR / NU_SVR):"));
	CvalueSpinBox = new QDoubleSpinBox;

	QLabel *nuLabel = new QLabel(tr("nu (NU_SVC / ONE_CLASS / NU_SVR):"));
	nuSpinBox = new QDoubleSpinBox;

	QLabel *pLabel = new QLabel(tr("p (EPS_SVR):"));
	pSpinBox = new QDoubleSpinBox;

	QGridLayout *svmLayout = new QGridLayout;
	svmLayout->addWidget(svmTypeLabel, 0, 0);
	svmLayout->addWidget(svmTypeComboBox, 0, 1);
	svmLayout->addWidget(kernelTypeLabel, 1, 0);
	svmLayout->addWidget(kernelTypeComboBox, 1, 1);
	svmLayout->addWidget(separator, 2, 0, 1, -1);
	svmLayout->addWidget(degreeLabel, 3, 0);
	svmLayout->addWidget(degreeSpinBox, 3, 1);
	svmLayout->addWidget(gammaLabel, 4, 0);
	svmLayout->addWidget(gammaSpinBox, 4, 1);
	svmLayout->addWidget(coef0Label, 5, 0);
	svmLayout->addWidget(coef0SpinBox, 5, 1);
	svmLayout->addWidget(CvalueLabel, 6, 0);
	svmLayout->addWidget(CvalueSpinBox, 6, 1);
	svmLayout->addWidget(nuLabel, 7, 0);
	svmLayout->addWidget(nuSpinBox, 7, 1);
	svmLayout->addWidget(pLabel, 8, 0);
	svmLayout->addWidget(pSpinBox, 8, 1);

	svmGroup->setLayout(svmLayout);

	QPushButton *startButton = new QPushButton(tr("Start"));
	QPushButton *cancelButton = new QPushButton(tr("Cancel"));
	
	QDialogButtonBox *buttonBox = new QDialogButtonBox;
	buttonBox->addButton(startButton, QDialogButtonBox::AcceptRole);
	buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);


	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(pcaGroup);
	mainLayout->addSpacing(10);
	mainLayout->addWidget(svmGroup);
	mainLayout->addSpacing(10);
	mainLayout->addWidget(buttonBox);
	
	this->initParameters();
	this->setLayout(mainLayout);
	this->setWindowTitle("Training configuration");


	// Connect signal and slot
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(onStartClicked()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

}

PCAClassifierDialog::~PCAClassifierDialog()
{

}

void PCAClassifierDialog::initParameters()
{
	// Retained variance
	varianceSpinBox->setRange(1.0, 100.0);
	varianceSpinBox->setSingleStep(0.1);
	varianceSpinBox->setValue(50.0);

	// Degree
	degreeSpinBox->setRange(1.0, 100.0);
	degreeSpinBox->setSingleStep(1.0);
	degreeSpinBox->setDecimals(0);
	degreeSpinBox->setValue(3.0);

	// Gamma
	gammaSpinBox->setRange(-1024.0, 1024.0);
	gammaSpinBox->setSingleStep(0.05);
	gammaSpinBox->setDecimals(2);
	gammaSpinBox->setValue(1.0);

	// Coef0
	coef0SpinBox->setRange(-1024.0, 1024.0);
	coef0SpinBox->setSingleStep(0.1);
	coef0SpinBox->setValue(0.0);

	// Cvalue
	CvalueSpinBox->setRange(-1024.0, 1024.0);
	CvalueSpinBox->setSingleStep(0.5);
	CvalueSpinBox->setValue(1);

	// nu
	nuSpinBox->setRange(-1024.0, 1024.0);
	nuSpinBox->setSingleStep(0.1);
	nuSpinBox->setValue(0.5);

	// p
	pSpinBox->setRange(-1024.0, 1024.0);
	pSpinBox->setSingleStep(0.1);
	pSpinBox->setValue(0.1);
}

void PCAClassifierDialog::onStartClicked()
{
	m_classifier->retainedVariance = varianceSpinBox->value() / 100.0;
	
	CvSVMParams &params = m_classifier->svmParams;
	const QMetaObject *metaObj = m_classifier->metaObject();
	QMetaEnum enumType;
	enumType = metaObj->enumerator(metaObj->indexOfEnumerator("SVMType"));
	params.svm_type = enumType.keyToValue(svmTypeComboBox->currentText().toStdString().c_str());
	enumType = metaObj->enumerator(metaObj->indexOfEnumerator("KernelType"));
	params.kernel_type = enumType.keyToValue(kernelTypeComboBox->currentText().toStdString().c_str());
	params.degree = degreeSpinBox->value();
	params.gamma = gammaSpinBox->value();
	params.coef0 = coef0SpinBox->value();
	params.C = CvalueSpinBox->value();
	params.nu = nuSpinBox->value();
	params.p = pSpinBox->value();

	m_classifier->start();
	accept();
}