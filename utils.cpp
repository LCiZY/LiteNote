#include<utils.h>



QString convertColorToStyleStr(QColor c){
    return QString("color:rgba(%1,%2,%3,%4)").arg(QString::number(c.red()),
                                                        QString::number(c.green()),
                                                        QString::number(c.blue()),
                                                        QString::number(c.alpha()));
}

bool setStyleSheetByQssPath(QWidget* w,QString qssFilePath){
    QString style = readFile(qssFilePath);
    if(!style.isEmpty()){
        w->setStyleSheet(style);
    }
    return !style.isEmpty();
}

QString readFile(QString path){
    QFile file(path);
    if(file.open(QFile::ReadOnly)){
        QString content = file.readAll();
        file.close();
        return content;
    }
    return QString();
}
