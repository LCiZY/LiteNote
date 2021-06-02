#ifndef UTILS_H
#define UTILS_H

#include<QString>
#include<QColor>
#include<QWidget>
#include<QFile>

/**
Convert object of QColor to QString that format like: color: rgba(r,g,b,a)
@param path path of file that would be read
@return the file's content, QString() if empty.
*/
QString readFile(QString path);

/**
Convert object of QColor to QString that format like: color: rgba(r,g,b,a)
@param w widget to set style
@param qssFilePath qss file path
@return QString like: color: rgba(r,g,b,a)
*/
QString convertColorToStyleStr(QColor c);
/**
Set widget's style
@param w widget to set style
@param qssFilePath qss file path
*/
bool setStyleSheetByQssPath(QWidget* w,QString qssFilePath);




#endif // UTILS_H
