#ifndef EDITORJAVA_H
#define EDITORJAVA_H

#include <QWidget>
#include <QString>
#include <QTabWidget>
#include <QToolBar>
#include <QComboBox>
#include <QList>
#include "coder.h"
#include "../dialog/find.h"



namespace UI {

class editorJava : public QWidget
{
    Q_OBJECT
public:
    explicit editorJava(QWidget *parent = 0);
    void load(const QString &path);
    Coder *_coder;

private:
    QToolBar *_toolbar;
    QComboBox *_comboBox;
    QList<QString>* _list;
    QAction* _find;
    Dialog::Find* _findDialog;

public slots:
    void __changed(const int index);
    void find();
};

}

#endif // EDITORJAVA_H
