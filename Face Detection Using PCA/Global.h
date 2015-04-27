#ifndef GLOBAL_H
#define GLOBAL_H

#include "opencv2/opencv.hpp"
#include "QString"
#include "QImage"
#include "QPixmap"

// Project Version
#define VERSION_MAJOR 0
#define VERSION_MINOR 2
#define VERSION_BUILD 2

// Stringify with macro expansion
#define _TOSTR(x)   #x
#define TOSTR(x)  _TOSTR(x)

// Versioning
static const char* const project_version_string = TOSTR(VERSION_MAJOR) "." TOSTR(VERSION_MINOR) "." TOSTR(VERSION_BUILD) "(" __DATE__ ", " __TIME__ ")";
#define PROJCT_VERSION TOSTR(VERSION_MAJOR) "." TOSTR(VERSION_MINOR) "." TOSTR(VERSION_BUILD)

// Image convert from OpenCV to Qt
QImage Mat2QImage(const cv::Mat& mat);
QPixmap Mat2QPixmap(const cv::Mat& mat);

// About project
QString aboutProject();

#endif