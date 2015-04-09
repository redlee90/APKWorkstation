#ifndef EDITORJAVA_H
#define EDITORJAVA_H

#include <QWidget>
#include <QString>
#include <QTabWidget>
#include <QToolBar>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QList>
#include "coder.h"

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
    QLabel* _searchLabel;
    QLineEdit* _searchText;
    QTextCursor _cursor;
    QComboBox *_comboBox;
    QList<QString>* _list;
    QAction* _search;

public slots:
    void __changed(const int index);
    void search();
};

}

#endif // EDITORJAVA_H
