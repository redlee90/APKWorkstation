#include "editorsmali.h"

namespace UI {

Editors::Editors(QWidget *parent) :
    QWidget(parent)
{
    // Toolbar
    this->_toolbar = new QToolBar(this);
    // Action
    this->_revert = new QAction(icon("revert"), text("label_revert"), this->_toolbar);
    this->_save = new QAction(icon("save"), text("label_save"), this->_toolbar);
    this->_save_all = new QAction(icon("save_all"), tr("Save All"),this->_toolbar);
    this->_undo = new QAction(icon("undo"),tr("Undo"),this->_toolbar);
    this->_redo = new QAction(icon("redo"),tr("Redo"),this->_toolbar);
    this->_find = new QAction(icon("find"),tr("Find/Replace"),this->_toolbar);
    // Combo
    this->_combo = new QComboBox(this->_toolbar);
    this->_combo->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    // List
    this->_list = new QList<QString>();
    // Tabs
    this->_tabs = new QTabWidget(this);
    /*
     * @Prepare
     */
    // Action
    this->reset();
    // Tabs
    this->_tabs->setTabsClosable(true);
    // Toolbar
    this->_toolbar->setAcceptDrops(false);
    this->_toolbar->setMovable(false);
    // Widget
    this->setMinimumSize(QSize(160, 160));
    /*
     * @Bind
     */
    // Action
    this->connect(this->_revert, SIGNAL(triggered()), this, SLOT(__revert()));
    this->connect(this->_save, SIGNAL(triggered()), this, SLOT(__save()));
    this->connect(this->_save_all,SIGNAL(triggered()),this,SLOT(__save_all()));
    this->connect(this->_redo,SIGNAL(triggered()),this,SLOT(__redo()));
    this->connect(this->_undo,SIGNAL(triggered()),this,SLOT(__undo()));
    this->connect(this->_find,SIGNAL(toggled(const bool)),this,SLOT(__findAndReplace(const bool)));
    // List
    this->connect(this->_combo, SIGNAL(currentIndexChanged(const int)), this, SLOT(__changed(const int)));
    // Tabs
    this->connect(this->_tabs, SIGNAL(tabCloseRequested(const int)), this, SLOT(__close(int)));
    this->connect(this->_tabs, SIGNAL(currentChanged(const int)), this, SLOT(__changed(const int)));
    // Actions
    QList<QAction *> state;
    state << this->_save;
    state << this->_save_all;
    state << this->_revert;
    state << this->_undo;
    state << this->_redo;
    state << this->_find;
    // Toolbar
    this->_toolbar->addActions(state);
    this->_toolbar->addWidget(this->_combo);
    // Layout
    layout->setContentsMargins(0,0,0,0);
    this->_toolbar->setContentsMargins(0,0,0,0);
    this->_tabs->setContentsMargins(0,0,0,0);
    layout->addWidget(this->_toolbar);
    layout->addWidget(this->_tabs);
    this->setLayout(layout);
}

void Editors::close()
{
    if (this->_list->size() < 1)
        return;
    int index = this->_tabs->currentIndex();
    this->close(index);
}

void Editors::close(const QString &project)
{
    if (this->_list->size() < 1)
        return;
    for (int index = 0; index < this->_list->size();) {
        if (this->_list->at(index).startsWith(project))
            this->close(index);
        else
            index++;
    }
}

void Editors::close(const int index)
{
    if (index >= this->_list->size())
        return;
    QWidget *widget = this->_tabs->widget(index);
    Coder *coder = qobject_cast<Coder *>(widget);
    if (coder) {
        this->disconnect(coder, SIGNAL(close_()), this, SLOT(__close()));
        this->disconnect(coder, SIGNAL(undoAvailable(bool)), this, SLOT(__undoable(const bool)));
        this->disconnect(coder, SIGNAL(redoAvailable(const bool)), this, SLOT(__redoable(const bool)));
        this->disconnect(coder, SIGNAL(save_()), this, SLOT(__save()));
        this->_combo->removeItem(index);
        this->_list->removeAt(index);
        this->_tabs->removeTab(index);
        this->reset();
    }
}

void Editors::deleted(const QString &path)
{
    int index = this->_list->indexOf(path);
    if (index > -1)
        this->close(index);
}

void Editors::load(const QString &path)
{
    QStringList text;
    text << QString("java");
    text << QString("smali");
    text << QString("txt");
    text << QString("xml");
    text << QString("yml");
    QFileInfo info(path);
    if (info.exists() && info.isFile()) {
        int tab = this->_list->indexOf(path);
        if (tab > -1) {
            this->_tabs->setCurrentIndex(tab);
            return;
        }
        QString extension = info.suffix();
        if (!text.contains(extension))
            return;
        Coder *coder = new Coder(this->_tabs);
        this->connect(coder, SIGNAL(copyAvailable(const bool)), this, SLOT(__cutable(const bool)));
        //this->connect(coder, SIGNAL(changed(const int, const int)), this, SLOT(__changed(const int, const int)));
        this->connect(coder, SIGNAL(close_()), this, SLOT(__close()));
        this->connect(coder, SIGNAL(undoAvailable(bool)), this, SLOT(__undoable(const bool)));
        this->connect(coder, SIGNAL(redoAvailable(const bool)), this, SLOT(__redoable(const bool)));
        this->connect(coder, SIGNAL(save_()), this, SLOT(__save()));
        if (info.suffix() == QString("yml"))
            coder->setReadOnly(true);
        coder->read(info.absoluteFilePath());
        QString label = info.fileName();
        if (label.length() > 24)
            label = label.mid(0, 24);
        int index = this->_tabs->addTab(coder, icon(extension.toStdString().c_str()), label);
        this->_list->append(info.absoluteFilePath());
        this->_tabs->setCurrentIndex(index);
        this->_tabs->setTabToolTip(index, info.absoluteFilePath());
        this->_combo->addItem(icon(extension.toStdString().c_str()), label, QVariant(info.absoluteFilePath()));
        this->__changed(index);
    }
}

void Editors::renamed(const QString &current, const QString &previous)
{
    int index = this->_list->indexOf(previous);
    if (index > -1) {
        QFileInfo info(current);
        this->_combo->setItemData(index, QVariant(info.absoluteFilePath()), ROLE_PATH);
        this->_combo->setItemText(index, info.fileName());
        this->_list->replace(index, info.absoluteFilePath());
        this->_tabs->setTabText(index, info.fileName());
        this->_tabs->setTabToolTip(index, info.absoluteFilePath());
        QWidget *widget = this->_tabs->widget(index);
        Coder *coder = qobject_cast<Coder *>(widget);
        if (coder)
            coder->path(info.absoluteFilePath());
    }
}

void Editors::reset()
{
    // Disable
    this->_revert->setEnabled(false);
    this->_save->setEnabled(false);
    this->_save_all->setEnabled(false);
    this->_redo->setEnabled(false);
    this->_undo->setEnabled(false);
    this->_find->setCheckable(true);
    this->_find->setChecked(false);
    // Current
    int index = this->_tabs->currentIndex();
    // Close
    if (index > -1) {
        this->_revert->setEnabled(true);
        this->_save->setEnabled(true);
        this->_save_all->setEnabled(true);
        this->_find->setChecked(true);
        Coder *coder = this->coder();
        if (coder) {
            if (coder->document()->availableRedoSteps() < 1)
                emit redoable(false);
            if (coder->document()->availableUndoSteps() < 1)
                emit undoable(false);
            if (coder->selected())
                this->__cutable(true);
            else
                this->__cutable(false);
        }
    }
    emit count(this->_list->count());
}

void Editors::save()
{
    Coder *coder = this->coder();
    if (coder) {
        QString line;
        if (coder->save())
            line = text("message_save");
        else
            line = text("failure_save");
        emit message(line.arg(coder->path()));
    }
}

void Editors::__changed(const int index)
{
    if (index >= this->_list->size())
        return;
    if (this->_combo->currentIndex() != index)
        this->_combo->setCurrentIndex(index);
    if (this->_tabs->currentIndex() != index)
        this->_tabs->setCurrentIndex(index);
    if (index > -1) {
        this->_tabs->currentWidget()->setFocus();
        emit changed();
    }
    this->reset();
}

void Editors::__revert()
{
    QString detail = text("message_revert").arg(this->_list->at(this->_tabs->currentIndex()));
    int result = QMessageBox::question(this, text("title_revert"), detail, QMessageBox::Yes, QMessageBox::No);
    if (result == QMessageBox::Yes) {
        Coder *coder = this->coder();
        if (coder) {
            QString text;
            if (coder->revert())
                text.append("Reloaded file contents from %1");
            else
                text.append("Unable to reload %1");
            emit message(text.arg(coder->path()));
        }
    }
}

// void Editors::__find() {
//    Coder *coder = this->coder();
//    if (!coder || (coder == 0))
//        return;
//    if (this->_findDialog)
//        delete this->_findDialog;
//    this->_findDialog = new Dialog::Find(false, this);
//    this->_findDialog->editor(coder);
//    this->_findDialog->show();
// }

} // namespace UI


