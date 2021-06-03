#include "transparentplaintextedit.h"


TransparentPlainTextEdit::TransparentPlainTextEdit(QWidget *parent): QPlainTextEdit(parent)
{
    this->parent = parent;
    this->font = QFont("微软雅黑",11,-1,false);
    this->font.setWeight(QFont::Weight::Bold);
    textColor = QColor(245,245,245,255);
    editorBasicStyle = "background:transparent;border-width:0;border-style:outset;border-radius: 5px;";
    setFont(this->font);
    setMouseTracking(true); //开启鼠标追踪


    //创建一个菜单 添加事件
    menu = new QMenu(this);
    menu->setWindowFlags(menu->windowFlags() | Qt::FramelessWindowHint);
    menu->setAttribute(Qt::WA_TranslucentBackground);
    QAction *op_text_color = new QAction("Text Color",menu);
    QAction *op_bg_color = new QAction("Background Color",menu);
    QAction *ac_help = new QAction("Help",menu);
    QAction *ac_on_top = new QAction("Stay On Top",menu);


    menu->addAction(op_text_color);
    menu->addAction(op_bg_color);
    menu->addAction(ac_help);
    menu->addAction(ac_on_top);


    connect(op_text_color,SIGNAL(triggered(bool)),this,SLOT(changeTextColor()));
    connect(op_bg_color,SIGNAL(triggered(bool)),this,SLOT(changeBgColor()));
    connect(ac_help,SIGNAL(triggered(bool)),this,SLOT(showHelpToolTip()));
    connect(ac_on_top,SIGNAL(triggered(bool)),this,SIGNAL(stayOnTopSignal()));


    helpText = readFile(":/text/help.txt").trimmed();
    setStyleSheetByQssPath(menu,":/styles/menu_style.qss");
    setStyleSheetByQssPath(this->verticalScrollBar(),":/styles/scrollbar_style.qss");
    this->setStyleSheet(editorBasicStyle + convertColorToStyleStr(textColor));
}

void TransparentPlainTextEdit::setInsertTextColor(QColor col)
{
    QTextCharFormat fmt;
    fmt.setForeground(col);
    QTextCursor cursor = textCursor();
    cursor.mergeCharFormat(fmt);
    mergeCurrentCharFormat(fmt);
}

void  TransparentPlainTextEdit::setFontSize(int size){
    this->font.setPointSize(size);
}

void TransparentPlainTextEdit::changeTextColor(){
    QColor c = QColorDialog::getColor(textColor, nullptr,
                                      tr("Text Color"),
                                      QColorDialog::ShowAlphaChannel);
    if(!c.isValid()) return;
    textColor = c;

    this->setStyleSheet(editorBasicStyle + convertColorToStyleStr(c));
}

void TransparentPlainTextEdit::changeBgColor(){
    QColor c = QColorDialog::getColor(this->bgColorDup, nullptr,
                                      tr("Background color"),
                                      QColorDialog::ShowAlphaChannel);
    if(!c.isValid()) return;
    // if alpha reach 0, then the window can not catch the mouse.
    c.setAlpha(c.alpha()<MIN_ALPHA?MIN_ALPHA:c.alpha());
    emit changeBgColorSignal(c);
}

void TransparentPlainTextEdit::setBgColorDup(QColor c){
    this->bgColorDup = c;
}

void TransparentPlainTextEdit::showHelpToolTip(){
    Tooltip::popup(QCursor::pos(), helpText, this);
}

void TransparentPlainTextEdit::contextMenuEvent(QContextMenuEvent*)
{
    //让菜单移动鼠标位置并显示
    menu->exec(QCursor::pos());
}

void TransparentPlainTextEdit::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
    this->QPlainTextEdit::mousePressEvent(event);
}

void TransparentPlainTextEdit::mouseMoveEvent(QMouseEvent *event)
{
    if(QApplication::keyboardModifiers() == Qt::ControlModifier){
        this->QPlainTextEdit::mouseMoveEvent(event);
        event->accept();
    }else{
        event->ignore();
    }

}

void TransparentPlainTextEdit::wheelEvent(QWheelEvent *event){
    if(QApplication::keyboardModifiers() == Qt::ControlModifier){
        QPoint numDegrees = event->angleDelta();
        if(!numDegrees.isNull()){
            if(numDegrees.y()>0) //增大字体
            {
                int nextSize = this->font.pointSize() + 1;
                if(nextSize <= MAX_FONT_POINT_SIZE){
                    setFontSize(nextSize);
                    setFont(this->font);
                }

            }
            else //减小字体
            {
                int nextSize = this->font.pointSize() - 1;
                if(nextSize >= MIN_FONT_POINT_SIZE){
                    setFontSize(nextSize);
                    setFont(this->font);
                }
            }
        }
        event->accept();
    }else{
        this->QPlainTextEdit::wheelEvent(event);
        event->ignore();
    }
}


