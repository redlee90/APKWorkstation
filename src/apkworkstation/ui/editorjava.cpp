#include "editorjava.h"
#include <QFileInfo>
#include <QVBoxLayout>

namespace UI {

editorJava::editorJava(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    this->_toolbar = new QToolBar(this);
    this->_searchLabel = new QLabel(this);
    this->_searchLabel->setText("Search:");
    this->_searchText = new QLineEdit(this->_toolbar);
    this->_comboBox = new QComboBox(this->_toolbar);
    this->_comboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    this->_comboBox->setDuplicatesEnabled(false);
    this->_search = new QAction(QIcon(Utility::Resource::icon("javaviewer","search")),tr("Search"),this->_toolbar);
    this->_toolbar->addWidget(this->_searchLabel);
    this->_toolbar->addWidget(this->_searchText);
    this->_toolbar->addAction(this->_search);
    this->_toolbar->addWidget(this->_comboBox);
    this->_coder = new Coder(this);
    this->_coder->setReadOnly(true);
    this->_coder->read(Utility::Configuration::apkstudio().append("/ReadMe.txt"));
    //this->_coder->setLineWrapMode(QTextEdit::FixedPixelWidth);
    layout->setContentsMargins(0,0,0,0);
    this->_toolbar->setContentsMargins(0,0,0,0);
    this->_coder->setContentsMargins(0,0,0,0);
    layout->addWidget(this->_toolbar);
    layout->addWidget(this->_coder);
    this->setLayout(layout);
    this->_list = new QList<QString>();
    // List
    this->connect(this->_comboBox, SIGNAL(currentIndexChanged(const int)), this, SLOT(__changed(const int)));
    this->connect(this->_search,SIGNAL(triggered()),this,SLOT(search()));
}

void editorJava::load(const QString &path)
{
    QFileInfo info(path);
    if (info.exists() && !info.isDir()) {
        this->_coder->read(info.absoluteFilePath());
        if (!this->_list->contains(info.absoluteFilePath())) {
            this->_list->append(info.absoluteFilePath());
            this->_comboBox->addItem(info.fileName(),info.absoluteFilePath());
        }
    }
}

void editorJava::__changed(const int index)
{
    if (index >= this->_list->size()) {
        return;
    }

    if (this->_comboBox->currentIndex() != index) {
        this->_comboBox->setCurrentIndex(index);
    }

    this->load(this->_comboBox->itemData(index).toString());
}

void editorJava::search()
{
    bool result = false;
    const QString &searchable = this->_searchText->text();
    result = this->_coder->find(searchable);
    if (!result) {
        this->_cursor = this->_coder->textCursor();
        this->_cursor.setPosition(0);
        //this->_cursor.setPosition(QTextCursor::Start);
        this->_coder->setTextCursor(this->_cursor);
    }
}

}

