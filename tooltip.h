#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QDialog>
#include <QFile>
#include <utils.h>

class QLabel;
class Tooltip : public QDialog
{
    Q_OBJECT
public:
    Tooltip(QWidget *parent = nullptr);
    ~Tooltip();

    void setText(const QString &text);
    static void popup(QPoint pos, const QString &text, QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    QLabel *label_;
};

#endif // TOOLTIP_H

