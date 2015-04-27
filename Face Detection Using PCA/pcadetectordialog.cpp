#include "pcadetectordialog.h"

PCADetectorDialog::PCADetectorDialog(PCADetector *detector, QWidget *parent)
	: QDialog(parent), m_detector(detector)
{
	initControllers();
	QLabel *scanStepLabel = new QLabel("Scan step:");
	QLabel *scaleRateLabel = new QLabel("Scale rate:");
	QLabel *groupThresholdLabel = new QLabel("Grouping threshold:");
	QLabel *groupEpsLabel = new QLabel("Grouping EPS:");

	QGroupBox *groupBox = new QGroupBox("Face Detection Parameters");
	QGridLayout *groupBoxLayout = new QGridLayout;
	groupBoxLayout->addWidget(skinSgmtCheckBox, 0, 0, 1, 2);
	groupBoxLayout->addWidget(scanStepLabel, 1, 0);
	groupBoxLayout->addWidget(scanStepSpinBox, 1, 1);
	groupBoxLayout->addWidget(scaleRateLabel, 2, 0);
	groupBoxLayout->addWidget(scaleRateSpinBox, 2, 1);
	groupBoxLayout->addWidget(groupThresholdLabel, 3, 0);
	groupBoxLayout->addWidget(groupThresholdSpinBox, 3, 1);
	groupBoxLayout->addWidget(groupEpsLabel, 4, 0);
	groupBoxLayout->addWidget(groupEpsSpinBox, 4, 1);

	groupBox->setLayout(groupBoxLayout);

	QPushButton *startButton = new QPushButton("Start");
	QPushButton *cancelButton = new QPushButton("Cancel");
	QDialogButtonBox *buttonBox = new QDialogButtonBox;
	buttonBox->addButton(startButton, QDialogButtonBox::AcceptRole);
	buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(groupBox);
	mainLayout->addSpacing(20);
	mainLayout->addWidget(buttonBox);

	setLayout(mainLayout);	
	setWindowTitle("Detection configuration");

	// Connect signal and slot
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(onStartClicked()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void PCADetectorDialog::initControllers()
{
	scanStepSpinBox = new QSpinBox;
	scanStepSpinBox->setRange(1, 10);
	scanStepSpinBox->setValue(1);

	scaleRateSpinBox = new QDoubleSpinBox;
	scaleRateSpinBox->setRange(1.05, 10.0);
	scaleRateSpinBox->setSingleStep(0.05);
	scaleRateSpinBox->setValue(1.2);

	groupThresholdSpinBox = new QSpinBox;
	groupThresholdSpinBox->setRange(0, 10);
	groupThresholdSpinBox->setValue(1);

	groupEpsSpinBox = new QDoubleSpinBox;
	groupEpsSpinBox->setRange(0.05, 10.0);
	groupEpsSpinBox->setSingleStep(0.05);
	groupEpsSpinBox->setValue(0.8);

	skinSgmtCheckBox = new QCheckBox("Perform skin segmentation");
	skinSgmtCheckBox->setCheckState(Qt::Checked);
}

PCADetectorDialog::~PCADetectorDialog()
{

}

void PCADetectorDialog::onStartClicked()
{
	m_detector->m_enableSkinSgmt = skinSgmtCheckBox->isChecked();
	m_detector->m_scanStep = scanStepSpinBox->value();
	m_detector->m_scaleRate = scaleRateSpinBox->value();
	m_detector->m_groupThreshold = groupThresholdSpinBox->value();
	m_detector->m_groupEps = groupEpsSpinBox->value();
	m_detector->start();
	accept();
}