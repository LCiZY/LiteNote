#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QMouseEvent>
#include <transparentplaintextedit.h>
#include <QDebug>
#include <windows.h>
#include <winuser.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void setBgColor(QColor c);
    void stayOnTop();

private:
    void testEdge();  //检测鼠标是否接近窗口边缘
    QPoint m_startPoint;
    QPoint dragPosition;   //鼠标拖动的位置
    int    edgeMargin;     //鼠标检测的边缘距离
    enum {nodir,
          top = 0x01,
          bottom = 0x02,
          left = 0x04,
          right = 0x08,
          topLeft = 0x01 | 0x04,
          topRight = 0x01 | 0x08,
          bottomLeft = 0x02 | 0x04,
          bottomRight = 0x02 | 0x08} resizeDir; //更改尺寸的方向

private:
    Ui::MainWindow *ui;
    TransparentPlainTextEdit *edit;
    QColor bg_color;
};

#endif // MAINWINDOW_H
