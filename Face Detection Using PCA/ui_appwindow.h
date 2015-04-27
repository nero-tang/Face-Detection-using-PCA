#ifndef UI_APPWINDOW_H
#define UI_APPWINDOW_H

#include "QtWidgets"

class AppUI
{
public:
	enum TreeWigetType
	{
		FaceTemplateTree = 0,
		NonfaceTemplateTree,
		EigenfaceTree,
		DetectResultTree
	};

	// Menu bar
	QMenuBar *menuBar;
	QAction *aboutAction;

	// Dock 
	QDockWidget *dockWidget;
	QTextBrowser *logList;

	// Status bar
	QStatusBar *statusBar;

	// Tool Bar
	QToolBar *toolBar;
	QAction *loadImageAct;
	QAction *loadFaceTempAct;
	QAction *loadNonfaceTempAct;
	QAction *startTrainAct;
	QAction *startDetectAct;

	// Central widget
	QWidget *centralWidget;

	// Element Viewer
	QTabWidget *elemViewTab;
	QTreeWidget *faceTempTree;
	QTreeWidget *nonfaceTempTree;
	QTreeWidget *eigenfaceTree;
	QTreeWidget *detectResultTree;
	QLabel *meanfaceHolder;
	QLabel *elementHolder;

	// Image viewer
	QTabWidget *imageViewTab;
	QLabel *originalImageHolder;
	QLabel *skinSgmtImageHolder;
	QLabel *markedImageHolder;
	QScrollArea *originalImageScrArea;
	QScrollArea *skinSgmtImageScrArea;
	QScrollArea *markedImageSrcArea;

	// Progress bar
	QProgressBar *progressBar;

	void setup(QMainWindow *mainwindow)
	{
		// Menu Bar
		menuBar = new QMenuBar;
		mainwindow->setMenuBar(menuBar);

		aboutAction = menuBar->addAction("About");
		

		// Dock Widget
		dockWidget = new QDockWidget("Log");
		dockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);

		mainwindow->addDockWidget(Qt::BottomDockWidgetArea, dockWidget);
		logList = new QTextBrowser;

		dockWidget->setWidget(logList);


		// Tool Bar
		toolBar = new QToolBar("Tool bar");
		mainwindow->addToolBar(toolBar);

		loadImageAct = toolBar->addAction(QIcon(":/File/images/My Pictures.png"), "Load an image for face detection");
		loadFaceTempAct = toolBar->addAction(QIcon(":/File/images/Folder Generic Green-01.png"), "Load face templates");
		loadNonfaceTempAct = toolBar->addAction(QIcon(":/File/images/Folder Generic Red-01.png"), "Load non-face templates");
		toolBar->addSeparator();
		startTrainAct = toolBar->addAction(QIcon(":/File/images/Button Play-01.png"), "Press to train PCA classifier");
		startDetectAct = toolBar->addAction(QIcon(":/File/images/Button Turn On-01.png"), "Press to start face detection");
		

		// Status bar
		statusBar = new QStatusBar;
		mainwindow->setStatusBar(statusBar);


		// Central widget
		centralWidget = new QWidget;
		mainwindow->setCentralWidget(centralWidget);


		// Element tree section
		elemViewTab = new QTabWidget;

		faceTempTree = new QTreeWidget;
		faceTempTree->setColumnCount(3);
		faceTempTree->setHeaderLabels((QStringList() << "File" << "Size" << "Type"));
		elemViewTab->insertTab(0, faceTempTree, "Face");

		nonfaceTempTree = new QTreeWidget;
		nonfaceTempTree->setColumnCount(3);
		nonfaceTempTree->setHeaderLabels((QStringList() << "File" << "Size" << "Type"));
		elemViewTab->insertTab(1, nonfaceTempTree, "Non-face");

		eigenfaceTree = new QTreeWidget;
		eigenfaceTree->setColumnCount(2);
		eigenfaceTree->setHeaderLabels((QStringList() << "Index" << "Eigenvalue"));
		elemViewTab->insertTab(2, eigenfaceTree, "Eigenface");

		detectResultTree = new QTreeWidget;
		detectResultTree->setColumnCount(3);
		detectResultTree->setHeaderLabels((QStringList() << "Index" << "Position" << "Size"));
		elemViewTab->insertTab(3, detectResultTree, "Result");

		meanfaceHolder = new QLabel;
		meanfaceHolder->setFixedSize(100, 100);
		meanfaceHolder->setPixmap(QPixmap(":/File/images/unknown.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		meanfaceHolder->setScaledContents(true);

		elementHolder = new QLabel;
		elementHolder->setFixedSize(100, 100);
		elementHolder->setPixmap(QPixmap(":/File/images/unknown.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		elementHolder->setScaledContents(true);

		QGridLayout *elemViewLayout = new QGridLayout;
		elemViewLayout->addWidget(elemViewTab, 0, 0, 1, 2);
		elemViewLayout->addWidget(meanfaceHolder, 1, 0, Qt::AlignCenter);
		elemViewLayout->addWidget(elementHolder, 1, 1, Qt::AlignCenter);

		/*
		* Image view section, displaying original image (imported by user), skin segmented image and image marked with faces detected
		*/
		imageViewTab = new QTabWidget;
		originalImageScrArea = new QScrollArea;
		originalImageHolder = new QLabel;
		originalImageHolder->setPixmap(QPixmap(":/File/images/unknown.png"));
		originalImageHolder->setAlignment(Qt::AlignCenter);
		originalImageScrArea->setWidget(originalImageHolder);
		originalImageScrArea->setWidgetResizable(true);
		imageViewTab->insertTab(0, originalImageScrArea, "Original Image");

		skinSgmtImageScrArea = new QScrollArea;
		skinSgmtImageHolder = new QLabel;
		skinSgmtImageHolder->setPixmap(QPixmap(":/File/images/unknown.png"));
		skinSgmtImageHolder->setAlignment(Qt::AlignCenter);
		skinSgmtImageScrArea->setWidget(skinSgmtImageHolder);
		skinSgmtImageScrArea->setWidgetResizable(true);
		imageViewTab->insertTab(1, skinSgmtImageScrArea, "Skin Mask");

		markedImageSrcArea = new QScrollArea;
		markedImageHolder = new QLabel;
		markedImageHolder->setPixmap(QPixmap(":/File/images/unknown.png"));
		markedImageHolder->setAlignment(Qt::AlignCenter);
		markedImageSrcArea->setWidget(markedImageHolder);
		markedImageSrcArea->setWidgetResizable(true);
		imageViewTab->insertTab(2, markedImageSrcArea, "Detection Result");


		// progress bar
		progressBar = new QProgressBar;
		progressBar->setFixedHeight(30);
		progressBar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

		// Manage central widget layout
		QGridLayout *mainLayout = new QGridLayout;
		mainLayout->addLayout(elemViewLayout, 0, 0);
		mainLayout->addWidget(imageViewTab, 0, 1, -1, 1);
		mainLayout->addWidget(progressBar, 1, 0);

		centralWidget->setLayout(mainLayout);

	}
};

#endif