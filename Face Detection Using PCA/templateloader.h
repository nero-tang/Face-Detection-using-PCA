#ifndef IMPORTTHREAD_H
#define IMPORTTHREAD_H

#include <QThread>
#include <QTreeWidgetItem>
#include <QDir>
#include <QFileDialog>
#include "pcaclassifier.h"

class TemplateLoader : public QThread
{
	Q_OBJECT

public:
	TemplateLoader(QObject *parent = 0);
	~TemplateLoader();

	void loadTemplates(PCAClassifier *classifier, const QFileInfoList& fileInfoList, PCAClassifier::TemplateType type);

signals:
	void updateProgress(int progress);
	void updateTemplateInfo(const QList<QTreeWidgetItem *>& templateInfoList, PCAClassifier::TemplateType type);
	void postMessage(const QString& msg);

protected:
	void run();

private:
	QFileInfoList m_fileInfoList;
	PCAClassifier::TemplateType m_type;
	PCAClassifier *m_classifier;
};

#endif // IMPORTTHREAD_H
