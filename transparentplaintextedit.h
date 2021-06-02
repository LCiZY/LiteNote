#ifndef TRANSPARENTPLAINTEXTEDIT_H
#define TRANSPARENTPLAINTEXTEDIT_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QFont>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPlainTextEdit>
#include <QContextMenuEvent>
#include <QScrollBar>
#include <QMenu>
#include <QAction>
#include <tooltip.h>
#include <QContextMenuEvent>
#include <math.h>
#include <QColorDialog>
#include <QRgb>
#include <utils.h>

#include<QDebug>

class TransparentPlainTextEdit : public QPlainTextEdit
{
     Q_OBJECT
public:
    explicit TransparentPlainTextEdit(QWidget *parent = 0);
    void setInsertTextColor(QColor c);
    void setBgColorDup(QColor c);
    void setFontSize(int size = 13);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);  //右键菜单事件

public slots:
    void changeTextColor();
    void changeBgColor();
    void showHelpToolTip();

signals:
    void changeBgColorSignal(QColor);
    void stayOnTopSignal();

private:
    QPoint m_startPoint;
    QFont font;
    QString editorBasicStyle;
    QColor textColor;
    QColor bgColorDup;
    QString helpText;
    QWidget *parent;
    QMenu *menu;
    const int MIN_FONT_POINT_SIZE = 8;
    const int MAX_FONT_POINT_SIZE = 128;
    const int MIN_ALPHA = 1;
};

#endif // TRANSPARENTPLAINTEXTEDIT_H
