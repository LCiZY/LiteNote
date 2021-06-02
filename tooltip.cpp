#include "tooltip.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QEvent>

Tooltip::Tooltip(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    label_ = new QLabel(this);
    label_->setFont(QFont("Comic Sans MS",11));
    QGridLayout *mLayout = new QGridLayout(this);
    mLayout->addWidget(label_);
    mLayout->setContentsMargins(0,0,0,0);
    setStyleSheetByQssPath(label_, ":/styles/tooltip_style.qss");
    this->installEventFilter(this);
   // this->setStyleSheet("QWidget { background: transparent; }");

}

Tooltip::~Tooltip()
{
}

void Tooltip::setText(const QString &text)
{
    label_->setText(text);
}

bool Tooltip::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == this){
        if (QEvent::WindowDeactivate == e->type()){
            this->close();
            e->accept();
            return true;
        }
    }
    return QWidget::eventFilter(obj, e);
}

void Tooltip::popup(QPoint pos, const QString &text, QWidget *parent)
{
    Tooltip *t = new Tooltip(parent);
    t->setText(text);
    t->show();
    //t->setWindowFlags(t->windowFlags() | Qt::WindowStaysOnTopHint);
    t->move(pos);
}

