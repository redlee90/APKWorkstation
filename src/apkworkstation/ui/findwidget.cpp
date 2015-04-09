#include "findwidget.h"
#include <QVBoxLayout>

namespace UI {

findWidget::findWidget(QWidget *parent) :
    QWidget(parent)
{
    // find toolbar
    this->_findToolBar = new QToolBar(this);
    this->_findLabel = new QLabel(this->_findToolBar);
    this->_findLabel->setText("Find:");
    this->_findText = new QLineEdit(this->_findToolBar);
    this->_case = new QCheckBox("Case Sentivite",this->_findToolBar);
    this->_regex = new QCheckBox("Use Regex",this->_findToolBar);
    this->_whole = new QCheckBox("Whole Words",this->_findToolBar);
    this->_findButton = new QPushButton(tr("Find"),this->_findToolBar);
    this->_findToolBar->addWidget(this->_findLabel);
    this->_findToolBar->addWidget(this->_findText);
    this->_findToolBar->addWidget(this->_case);
    this->_findToolBar->addWidget(this->_regex);
    this->_findToolBar->addWidget(this->_whole);
    this->_findToolBar->addWidget(this->_findButton);

    //replace toolbar
    this->_replaceToolBar = new QToolBar(this);
    this->_replaceLabel = new QLabel(this->_replaceToolBar);
    this->_replaceLabel->setText("Replace with:");
    this->_replaceText = new QLineEdit(this->_replaceToolBar);
    this->_replaceButton = new QPushButton(tr("Replace"),this->_replaceToolBar);
    this->_replaceAllButton = new QPushButton(tr("Replace All"),this->_replaceAllButton);
    this->_replaceToolBar->addWidget(this->_replaceLabel);
    this->_replaceToolBar->addWidget(this->_replaceText);
    this->_replaceToolBar->addWidget(this->_replaceButton);
    this->_replaceToolBar->addWidget(this->_replaceAllButton);

    QVBoxLayout* _layout = new QVBoxLayout;
    _layout->setSpacing(0);
    _layout->addWidget(this->_findToolBar);
    _layout->addWidget(this->_replaceToolBar);
    _layout->setContentsMargins(0,0,0,0);
    this->_findToolBar->setContentsMargins(0,0,0,0);
    this->_replaceToolBar->setContentsMargins(0,0,0,0);
    this->setLayout(_layout);
    this->connect(this->_findButton,SIGNAL(clicked()),this,SLOT(find()));
    this->connect(this->_replaceButton,SIGNAL(clicked()),this,SLOT(replace()));
    this->connect(this->_replaceAllButton,SIGNAL(clicked()),this,SLOT(replaceAll()));
}

void findWidget::find()
{
    if (!this->_editor)
        return;
    const QString &searchable = this->_findText->text();
    bool result;
    QTextDocument::FindFlags flags;
        if (this->_case->isChecked())
            flags |= QTextDocument::FindCaseSensitively;
        if (this->_whole->isChecked())
            flags |= QTextDocument::FindWholeWords;
        if (this->_regex->isChecked()) {
            QRegExp regex(searchable, (this->_case->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));
            this->_cursor = this->_editor->document()->find(regex, this->_cursor, flags);
            this->_editor->setTextCursor(this->_cursor);
            result = !this->_cursor.isNull();
        } else {
            result = this->_editor->find(searchable, flags);
        }
    if (!result) {
        this->_cursor = this->_editor->textCursor();
        this->_cursor.setPosition(0);
        this->_editor->setTextCursor(this->_cursor);
    }
}

void findWidget::replace()
{
    if (!this->_editor)
        return;
    if (this->_editor->isReadOnly())
           return;
       if (!this->_editor->textCursor().hasSelection())
           this->find();
       else {
           this->_editor->textCursor().insertText(this->_replaceText->text());
           this->find();
       }
}

void findWidget::replaceAll()
{
    if (!this->_editor)
        return;
    if (this->_editor->isReadOnly())
            return;
        while (this->_editor->textCursor().hasSelection()) {
            this->_editor->textCursor().insertText(this->_replaceText->text());
            this->find();
        }
}

}
