#include "menubar.h"



namespace UI {

Menubar::Menubar(QWidget *parent) :
    QMenuBar(parent)
{
    /*
     * @Initialize
     */
    // Edit
    QMenu *edit = new QMenu(text("label_edit"), this);
    this->_copy = new QAction(icon("copy"), text("label_copy"), edit);
    this->_cut = new QAction(icon("cut"), text("label_cut"), edit);
    this->_goto = new QAction(icon("goto"), text("label_goto"), edit);
    this->_paste = new QAction(icon("paste"), text("label_paste"), edit);
    this->_redo = new QAction(icon("redo"), text("label_redo"), edit);
    this->_undo = new QAction(icon("undo"), text("label_undo"), edit);
    this->_findAndReplace = new QAction(icon("find"),tr("Find/Replace"),edit);
    // File
    QMenu *file = new QMenu(text("label_file"), this);
    this->_apk = new QAction(icon("apk"), text("label_apk"), file);
    this->_close = new QAction(icon("close"), text("label_close"), file);
    this->_directory = new QAction(icon("directory"), text("label_directory"), file);
    this->_print = new QAction(icon("print"), text("label_print"), file);
    this->_quit = new QAction(icon("quit"), text("label_quit"), file);
    this->_save = new QAction(icon("save"), text("label_save"), file);
    this->_save_all = new QAction(icon("save_all"), text("label_save_all"), file);
    this->_settings = new QAction(icon("settings"), text("label_settings"), file);
    // Project
    QMenu *project = new QMenu(text("label_project"), this);
    this->_build = new QAction(icon("build"), text("label_build"), project);
    this->_clean = new QAction(icon("clean"), text("label_clean"), project);
    this->_properties = new QAction(icon("properties"), text("label_properties"), project);
    // View
    QMenu *view = new QMenu(text("label_view"), this);
    this->_sidebar = new QAction(icon("sidebar"), text("label_sidebar"), view);
    this->_toggle_java_view = new QAction(icon("toggle_java_view"),tr("Toggle Java View"),view);
    this->_toggle_console_view = new QAction(icon("toggle_console_view"),tr("Toggle Console View"),view);
    /*
     * @Prepare
     */
    // Edit
    this->_copy->setShortcut(Qt::CTRL | Qt::Key_C);
    this->_cut->setShortcut(Qt::CTRL | Qt::Key_X);
    this->_goto->setShortcut(Qt::CTRL | Qt::Key_G);
    this->_paste->setShortcut(Qt::CTRL | Qt::Key_V);
    this->_redo->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_Z);
    this->_undo->setShortcut(Qt::CTRL | Qt::Key_Z);
    QList<QKeySequence> findAndReplaceShort;
    findAndReplaceShort.append(QKeySequence(Qt::CTRL + Qt::Key_F));
    findAndReplaceShort.append(QKeySequence(Qt::CTRL + Qt::Key_R));
    this->_findAndReplace->setShortcuts(findAndReplaceShort);
    this->_findAndReplace->setCheckable(true);
    // File
    this->_apk->setShortcut(Qt::CTRL | Qt::Key_N);
    this->_close->setShortcut(Qt::CTRL | Qt::Key_W);
    this->_directory->setShortcut(Qt::CTRL | Qt::Key_O);
    this->_print->setShortcut(Qt::CTRL | Qt::Key_P);
    this->_quit->setShortcut(Qt::CTRL | Qt::Key_Q);
    this->_save->setShortcut(Qt::CTRL | Qt::Key_S);
    this->_save_all->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);
    this->_settings->setShortcut(Qt::Key_F10);
    // Project
    this->_build->setShortcut(Qt::Key_F5);
    this->_clean->setShortcut(Qt::ALT | Qt::Key_C);
    this->_properties->setShortcut(Qt::ALT | Qt::Key_P);
    // View
    this->_sidebar->setShortcut(Qt::ALT | Qt::Key_Left);
    this->_sidebar->setCheckable(true);
    this->_toggle_java_view->setShortcut(Qt::ALT | Qt::Key_Right);
    this->_toggle_java_view->setCheckable(true);
    this->_toggle_console_view->setShortcut(Qt::ALT | Qt::Key_Up);
    this->_toggle_console_view->setCheckable(true);
    /*
     * @Bind
     */
    // Edit
    this->connect(this->_copy, SIGNAL(triggered()), this, SLOT(__copy()));
    this->connect(this->_cut, SIGNAL(triggered()), this, SLOT(__cut()));
    this->connect(this->_goto, SIGNAL(triggered()), this, SLOT(__goto()));
    this->connect(this->_paste, SIGNAL(triggered()), this, SLOT(__paste()));
    this->connect(this->_redo, SIGNAL(triggered()), this, SLOT(__redo()));
    this->connect(this->_undo, SIGNAL(triggered()), this, SLOT(__undo()));
    this->connect(this->_findAndReplace,SIGNAL(toggled(const bool)),this,SLOT(__toggle_find_edit(bool)));
    // File
    this->connect(this->_apk, SIGNAL(triggered()), this, SLOT(__apk()));
    this->connect(this->_close, SIGNAL(triggered()), this, SLOT(__close()));
    this->connect(this->_directory, SIGNAL(triggered()), this, SLOT(__directory()));
    this->connect(this->_print, SIGNAL(triggered()), this, SLOT(__print()));
    this->connect(this->_quit, SIGNAL(triggered()), this, SLOT(__quit()));
    this->connect(this->_save, SIGNAL(triggered()), this, SLOT(__save()));
    this->connect(this->_save_all, SIGNAL(triggered()), this, SLOT(__save_all()));
    this->connect(this->_settings, SIGNAL(triggered()), this, SLOT(__settings()));
    // Project
    this->connect(this->_build, SIGNAL(triggered()), this, SLOT(__build()));
    this->connect(this->_clean, SIGNAL(triggered()), this, SLOT(__clean()));
    this->connect(this->_properties, SIGNAL(triggered()), this, SLOT(__properties()));
    // View
    this->connect(this->_sidebar, SIGNAL(toggled(bool)), this, SLOT(__sidebar(bool)));
    this->connect(this->_toggle_console_view,SIGNAL(toggled(bool)),this,SLOT(__toggle_console_view(bool)));
    this->connect(this->_toggle_java_view,SIGNAL(toggled(bool)),this,SLOT(__toggle_java_view(bool)));
    /*
     * @Prepare
     */
    this->reset();
    /*
     * @Inflate
     */
    // Edit
    edit->addAction(this->_undo);
    edit->addAction(this->_redo);
    edit->addSeparator();
    edit->addAction(this->_cut);
    edit->addAction(this->_copy);
    edit->addAction(this->_paste);
    edit->addSeparator();
    edit->addAction(this->_goto);
    this->_findAndReplace->setChecked(false);
    edit->addAction(this->_findAndReplace);
    // File
    file->addAction(this->_apk);
    file->addAction(this->_directory);
    file->addSeparator();
    file->addAction(this->_save);
    file->addAction(this->_save_all);
    file->addAction(this->_close);
    file->addSeparator();
    file->addAction(this->_print);
    file->addSeparator();
    file->addAction(this->_settings);
    file->addSeparator();
    file->addAction(this->_quit);
    // Project
    project->addAction(this->_clean);
    project->addAction(this->_build);
    project->addSeparator();
    project->addAction(this->_properties);
    // View
    this->_sidebar->setChecked(true);
    view->addAction(this->_sidebar);
    this->_toggle_console_view->setChecked(false);
    view->addAction(this->_toggle_console_view);
    this->_toggle_java_view->setChecked(false);
    view->addAction(this->_toggle_java_view);
    // Menu
    this->addAction(file->menuAction());
    this->addAction(edit->menuAction());
    this->addAction(project->menuAction());
    this->addAction(view->menuAction());
}

void Menubar::disable(const int action, const bool block)
{
    QAction *pointer = this->get(action);
    if (pointer != 0) {
        if (block)
            this->blockSignals(true);
        pointer->setEnabled(false);
        if (block)
            this->blockSignals(false);
    }
}

void Menubar::enable(const int action, const bool block)
{
    QAction *pointer = this->get(action);
    if (pointer != 0) {
        if (block)
            this->blockSignals(true);
        pointer->setEnabled(true);
        if (block)
            this->blockSignals(false);
    }
}

QAction *Menubar::get(const int action)
{
    switch (action)
    {
    case COPY:
        return this->_copy;
    case CUT:
        return this->_cut;
    case GOTO:
        return this->_goto;
    case PASTE:
        return this->_paste;
    case REDO:
        return this->_redo;
    case UNDO:
        return this->_undo;
    case FIND_AND_REPLACE:
        return this->_findAndReplace;
    case APK:
        return this->_apk;
    case CLOSE:
        return this->_close;
    case DIRECTORY:
        return this->_directory;
    case PRINT:
        return this->_print;
    case QUIT:
        return this->_quit;
    case SAVE:
        return this->_save;
    case SAVE_ALL:
        return this->_save_all;
    case SETTINGS:
        return this->_settings;
    case BUILD:
        return this->_build;
    case CLEAN:
        return this->_clean;
    case PROPERTIES:
        return this->_properties;
    case SIDEBAR:
        return this->_sidebar;
    case TOGGLE_CONSOLE_VIEW:
        return this->_toggle_console_view;
    case TOGGLE_JAVA_VIEW:
        return this->_toggle_java_view;
    default:
        return 0;
    }
}

void Menubar::reset()
{
    this->_build->setEnabled(false);
    this->_clean->setEnabled(false);
    this->_close->setEnabled(false);
    this->_copy->setEnabled(false);
    this->_cut->setEnabled(false);
    this->_goto->setEnabled(false);
    this->_sidebar->setChecked(false);
    this->_toggle_console_view->setChecked(false);
    this->_toggle_java_view->setChecked(false);
    this->_paste->setEnabled(false);
    this->_print->setEnabled(false);
    this->_properties->setEnabled(false);
    this->_redo->setEnabled(false);
    this->_save->setEnabled(false);
    this->_save_all->setEnabled(false);
    this->_undo->setEnabled(false);
    this->_findAndReplace->setChecked(false);
}

void Menubar::toggle(const int action, const bool check, const bool block)
{
    QAction *pointer = this->get(action);
    if (pointer != 0) {
        if (block)
            this->blockSignals(true);
        if (pointer->isCheckable())
            pointer->setChecked(check);
        if (block)
            this->blockSignals(false);
    }
}

} // namespace UI


