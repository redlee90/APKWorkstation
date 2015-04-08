#include "editorjava.h"
#include <QFileInfo>
#include <QVBoxLayout>

namespace UI {

editorJava::editorJava(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    this->_findDialog = 0;
    this->_toolbar = new QToolBar(this);
    this->_comboBox = new QComboBox(this->_toolbar);
    this->_comboBox->setDuplicatesEnabled(false);
    this->_find = new QAction(QIcon(Utility::Resource::icon("editors","find")),tr("find"),this->_toolbar);
    this->_toolbar->addAction(this->_find);
    this->_toolbar->addWidget(this->_comboBox);
    this->_coder = new Coder(this);
    this->_coder->setReadOnly(true);
    this->_coder->setPlainText("Welcome to APKWorkstation");
    layout->addWidget(this->_toolbar);
    layout->addWidget(this->_coder);
    this->setLayout(layout);
    this->_list = new QList<QString>();
    // List
    this->connect(this->_comboBox, SIGNAL(currentIndexChanged(const int)), this, SLOT(__changed(const int)));
    this->connect(this->_find,SIGNAL(triggered()),this,SLOT(find()));

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

void editorJava::find()
{
    if (this->_findDialog) {
        delete this->_findDialog;
    }
    this->_findDialog = new Dialog::Find(false, this);
    this->_findDialog->editor(this->_coder);
    this->_findDialog->show();
}

}

