#ifndef FINDWIDGET_H
#define FINDWIDGET_H

#include <QWidget>
#include <QToolBar>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTextCursor>
#include <QCheckBox>

namespace UI {

class findWidget : public QWidget
{
    Q_OBJECT
public:
    explicit findWidget(QWidget *parent = 0);
    QPlainTextEdit *editor()
    {
        return this->_editor;
    }
    void editor(QPlainTextEdit *editor)
    {
        this->_editor = editor;
    }
private:
    QToolBar* _findToolBar;
    QLabel* _findLabel;
    QLineEdit* _findText;
    QCheckBox* _case;
    QCheckBox* _regex;
    QCheckBox* _whole;
    QPushButton* _findButton;
    QToolBar* _replaceToolBar;
    QLabel* _replaceLabel;
    QLineEdit* _replaceText;
    QPushButton* _replaceButton;
    QPushButton* _replaceAllButton;
    QPlainTextEdit *_editor;
    QTextCursor _cursor;
signals:

private slots:
    void find();
    void replace();
    void replaceAll();
};

#endif // FINDWIDGET_H
}
