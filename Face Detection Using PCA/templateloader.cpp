#include "templateloader.h"

TemplateLoader::TemplateLoader(QObject *parent)
: QThread(parent), m_classifier(0)
{

}

TemplateLoader::~TemplateLoader()
{

}

void TemplateLoader::loadTemplates(PCAClassifier* classifier, const QFileInfoList& fileInfoList, PCAClassifier::TemplateType type)
{
	m_fileInfoList = fileInfoList;
	m_type = type;
	m_classifier = classifier;
	start();
}

void TemplateLoader::run()
{
	static const QStringList templateTypeNames = QStringList() << "face templates" << "non-face templates";
	emit postMessage(tr("Loading %1, %2 files in total.").arg(templateTypeNames.at(m_type)).arg(m_fileInfoList.size()));

	std::vector<cv::Mat> templates;
	QList<QTreeWidgetItem *> templateInfoList;
	QString path = m_fileInfoList.first().absoluteDir().path();

	for (int i = 0; i < m_fileInfoList.size(); ++i)
	{
		QFileInfo fileInfo = m_fileInfoList.at(i);

		cv::Mat templateImg = cv::imread(fileInfo.filePath().toLocal8Bit().data(), 0);
		if (templateImg.size() != m_classifier->templateSize())
		{
			resize(templateImg, templateImg, m_classifier->templateSize());
		}
		equalizeHist(templateImg, templateImg);
		templates.push_back(templateImg);

		QStringList templateInfo = QStringList() << fileInfo.baseName()
			<< tr("%1 Bytes").arg(fileInfo.size()) << tr("%1 File").arg(fileInfo.suffix().toUpper());
		templateInfoList.append(new QTreeWidgetItem(templateInfo));
		
		emit updateProgress(i + 1);
	}

	m_classifier->setTemplates(templates, m_type);
	emit updateTemplateInfo(templateInfoList, m_type);	
	emit postMessage(tr("Templates loaded from %1").arg(path));
}