#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGridLayout>



#define min(a,b) ((a)<(b)? (a) :(b))
#define max(a,b) ((a)>(b)? (a) :(b))

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("LiteNote");
    setWindowIcon(QIcon(":/icon/icon.png"));
    edgeMargin = 6;        //设置检测边缘为6
    resizeDir = nodir;   //初始化检测方向为无
    setWindowFlags(Qt::FramelessWindowHint);  //设置无边框
    setMouseTracking(true); //开启鼠标追踪
    setAttribute(Qt::WA_TranslucentBackground);

    QGridLayout* gl = new QGridLayout(this);
    gl->setHorizontalSpacing(0);
    gl->setContentsMargins(3,3,3,3);
    gl->setVerticalSpacing(0);

    edit = new TransparentPlainTextEdit(this);
    connect(edit,SIGNAL(changeBgColorSignal(QColor)),this,SLOT(setBgColor(QColor)));
    connect(edit,SIGNAL(stayOnTopSignal()),this,SLOT(stayOnTop()));


    gl->addWidget(edit);
    setLayout(gl);
    setBgColor(QColor(0, 0, 0, 0x20));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setBgColor(QColor c){
    this->bg_color = c;
    this->edit->setBgColorDup(c);
    this->update();
}

void MainWindow::stayOnTop(){
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    this->show();
    if (this->isMinimized())
    {
        this->showNormal();
    }
    //set window stay on top
    ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    //set window do not stay on top
    //::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    //this->activateWindow();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), bg_color); /* 设置透明颜色 */
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_startPoint = frameGeometry().topLeft() - event->globalPos();
        dragPosition = event->globalPos() - frameGeometry().topLeft();  //获得鼠标按键位置相对窗口左上面的位置
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() & Qt::LeftButton){                 //如果左键是按下的
        if(resizeDir == nodir){                             //如果鼠标不是放在边缘那么说明这是在拖动窗口
            this->move(event->globalPos() + m_startPoint);
        }
        else{
            int ptop,pbottom,pleft,pright;                   //窗口上下左右的值
            ptop = frameGeometry().top();
            pbottom = frameGeometry().bottom();
            pleft = frameGeometry().left();
            pright = frameGeometry().right();
            if(resizeDir & top){                               //检测更改尺寸方向中包含的上下左右分量
                if(height() == minimumHeight()){
                    ptop = min(event->globalY(),ptop);
                }
                else if(height() == maximumHeight()){
                    ptop = max(event->globalY(),ptop);
                }
                else{
                    ptop = event->globalY();
                }
            }
            else if(resizeDir & bottom){
                if(height() == minimumHeight()){
                    pbottom = max(event->globalY(),ptop);
                }
                else if(height() == maximumHeight()){
                    pbottom = min(event->globalY(),ptop);
                }
                else{
                    pbottom = event->globalY();
                }
            }

            if(resizeDir & left){                        //检测左右分量
                if(width() == minimumWidth()){
                    pleft = min(event->globalX(),pleft);
                }
                else if(width() == maximumWidth()){
                    pleft = max(event->globalX(),pleft);
                }
                else{
                    pleft = event->globalX();
                }
            }
            else if(resizeDir & right){
                if(width() == minimumWidth()){
                    pright = max(event->globalX(),pright);
                }
                else if(width() == maximumWidth()){
                    pright = min(event->globalX(),pright);
                }
                else{
                    pright = event->globalX();
                }
            }
            setGeometry(QRect(QPoint(pleft,ptop),QPoint(pright,pbottom)));
        }
    }
    else
        testEdge();   //当不拖动窗口、不改变窗口大小尺寸的时候  检测鼠标边缘


}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();
    if(resizeDir != nodir){         //还原鼠标样式
        testEdge();
    }
}


void MainWindow::testEdge()
{
    int diffLeft = abs(cursor().pos().x() - frameGeometry().left());      //计算鼠标距离窗口上下左右有多少距离
    int diffRight = abs(cursor().pos().x() - frameGeometry().right());
    int diffTop = abs(cursor().pos().y() - frameGeometry().top());
    int diffBottom = abs(cursor().pos().y() - frameGeometry().bottom());

    QCursor tempCursor;                                    //获得当前鼠标样式，注意:只能获得当前鼠标样式然后再重新设置鼠标样式
    tempCursor = cursor();                                 //因为获得的不是鼠标指针，所以不能这样用:cursor().setXXXXX
    if(diffTop < edgeMargin){                              //根据 边缘距离 分类改变尺寸的方向
        if(diffLeft < edgeMargin){
            resizeDir = topLeft;
            tempCursor.setShape(Qt::SizeFDiagCursor);
        }
        else if(diffRight < edgeMargin){
            resizeDir = topRight;
            tempCursor.setShape(Qt::SizeBDiagCursor);
        }
        else{
            resizeDir = top;
            tempCursor.setShape(Qt::SizeVerCursor);
        }
    }
    else if(diffBottom < edgeMargin){
        if(diffLeft < edgeMargin){
            resizeDir = bottomLeft;
            tempCursor.setShape(Qt::SizeBDiagCursor);
        }
        else if(diffRight < edgeMargin){
            resizeDir = bottomRight;
            tempCursor.setShape(Qt::SizeFDiagCursor);
        }
        else{
            resizeDir = bottom;
            tempCursor.setShape(Qt::SizeVerCursor);
        }
    }
    else if(diffLeft < edgeMargin){
        resizeDir = left;
        tempCursor.setShape(Qt::SizeHorCursor);
    }
    else if(diffRight < edgeMargin){
        resizeDir = right;
        tempCursor.setShape(Qt::SizeHorCursor);
    }
    else{
        resizeDir = nodir;
        tempCursor.setShape(Qt::ArrowCursor);
    }

    setCursor(tempCursor);                    //重新设置鼠标,主要是改样式

}
