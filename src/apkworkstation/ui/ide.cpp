#include "ide.h"



namespace UI {

IDE::IDE(QWidget *parent)
    : QMainWindow(parent)
{
    this->_clipboard = QApplication::clipboard();
    // Dialog
    this->_find = NULL;
    this->_replace = NULL;
    // Menubar
    this->_menubar = new Menubar(this);
    this->_projects = new Projects;
    this->_console = new QTextEdit;
    this->_console->setReadOnly(true);
    this->_editorSmali = new Editors;
    this->_editorJava = new editorJava;
    // Splitter
    this->_mainHorizontal = new QSplitter(Qt::Horizontal, this);
    this->_leftVertical = new QSplitter(Qt::Vertical,this->_mainHorizontal);
    this->_rightVertical = new QSplitter(Qt::Vertical,this->_mainHorizontal);
    this->_mainHorizontal->addWidget(this->_leftVertical);
    this->_mainHorizontal->addWidget(this->_rightVertical);
    this->_leftVertical->addWidget(this->_projects);
    this->_editorHorizontal = new QSplitter(Qt::Horizontal,this->_rightVertical);
    this->_rightVertical->addWidget(this->_editorHorizontal);
    this->_rightVertical->addWidget(this->_console);
    this->_editorHorizontal->addWidget(this->_editorSmali);
    this->_editorHorizontal->addWidget(this->_editorJava);
    // Statusbar
    this->_statusbar = new Statusbar(this);
    // Toolbar
    this->_toolbar = new Toolbar(this);
    // Window
    this->resize(QSize(1152, 648));
    this->setMinimumSize(QSize(640, 360));
    this->setWindowTitle(tr("APKWorkstation"));
    // Clipboard
    this->connect(this->_clipboard, SIGNAL(changed(const QClipboard::Mode &)), this, SLOT(__clipboard(const QClipboard::Mode &)));
    // Menubar
    this->connect(this->_menubar, SIGNAL(action(const int)), this, SLOT(__action(const int)));
    this->connect(this->_menubar, SIGNAL(toggled(const int, const bool)), this, SLOT(__toggle(const int, const bool)));
    // Editor for Smali
    this->connect(this->_editorSmali, SIGNAL(changed()), this, SLOT(__changed()));
    this->connect(this->_editorSmali, SIGNAL(cutable(const bool)), this, SLOT(__cutable(const bool)));
    this->connect(this->_editorSmali, SIGNAL(count(const int)), this, SLOT(__editorSmali(const int)));
    this->connect(this->_editorSmali, SIGNAL(message(const QString &)), this, SLOT(__message(const QString &)));
    this->connect(this->_editorSmali, SIGNAL(progress(const int)), this, SLOT(__progress(const int)));
    this->connect(this->_editorSmali, SIGNAL(redoable(const bool)), this, SLOT(__redoable(const bool)));
    this->connect(this->_editorSmali, SIGNAL(undoable(const bool)), this, SLOT(__undoable(const bool)));
    // Projects
    this->connect(this->_projects, SIGNAL(build()), this, SLOT(__build()));
    this->connect(this->_projects, SIGNAL(closed(const QString &)), this, SLOT(__closed(const QString &)));
    this->connect(this->_projects, SIGNAL(deleted(const QString &)), this, SLOT(__deleted(const QString &)));
    this->connect(this->_projects, SIGNAL(edit(const QString &)), this, SLOT(__edit(const QString &)));
    this->connect(this->_projects, SIGNAL(renamed(const QString &, const QString &)), this, SLOT(__renamed(const QString &, const QString &)));
    this->connect(this->_projects, SIGNAL(message(const QString &)), this, SLOT(__message(const QString &)));
    this->connect(this->_projects, SIGNAL(selected(const bool)), this, SLOT(__projects(const bool)));
    // Toolbar
    this->connect(this->_toolbar, SIGNAL(action(const int)), this, SLOT(__action(const int)));
    // Statusbar
    this->connect(this->_statusbar, SIGNAL(toggled(const int, const bool)), this, SLOT(__toggle(const int, const bool)));

    // Menubar
    this->setMenuBar(this->_menubar);
    // Splitter
    this->_rightVertical->setStretchFactor(0, 1);
    this->_rightVertical->setStretchFactor(1, 3);
    this->_mainHorizontal->setStretchFactor(0, 1);
    this->_mainHorizontal->setStretchFactor(1, 3);
    this->_leftVertical->setStretchFactor(0, 2);
    this->_leftVertical->setStretchFactor(1, 1);
    // Statusbar
    this->addToolBar(Qt::BottomToolBarArea, this->_statusbar);
    // Toolbar
    this->addToolBar(Qt::TopToolBarArea, this->_toolbar);
    // Window
    this->setCentralWidget(this->_mainHorizontal);
    this->context();
}

void IDE::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, text("title_close"), text("message_close"), QMessageBox::No | QMessageBox::Yes))
        event->accept();
}

void IDE::context()
{
#ifdef Q_OS_WIN
    QSettings apk("HKEY_CURRENT_USER\\Software\\Classes\\.apk", QSettings::NativeFormat);
    apk.setValue("Content Type", "application/vnd.android.package-archive");
    apk.setValue("DefaultIcon", QCoreApplication::applicationFilePath().append(", 0"));
    apk.sync();
#endif
}

void IDE::open(const QString &path)
{
    if (path.isEmpty())
        return;
    this->_projects->load(path);
}

void IDE::__action(const int action)
{
    switch (action)
    {

    case UI::Menubar::APK:
    case UI::Toolbar::APK:
    {
        project = new Dialog::Project(this);
        int retCode = project->exec();
        this->connect(project,SIGNAL(loadAPK(const QString &)),this->_statusbar,SLOT(showMessage(const QString &)));
        if (retCode==QDialog::Accepted) {
            this->_toolbar->_decompile->setEnabled(true);
            this->_toolbar->_decompile_dex->setEnabled(true);
            this->_toolbar->_decompile_res->setEnabled(true);
            this->_toolbar->_dex2jar->setEnabled(true);
            QString succ = project->apk()+" loads successfully";
            emit project->loadAPK(succ);
        } else {
            emit project->loadAPK(QString("Cancelled loading apk"));
        }
        break;
    }
    case UI::Toolbar::DECOMPILE:
    {
        QString location = QString(project->location()).append('/').append(project->name());
        // Prepare
        Runtime::Decompile *decompile = new Runtime::Decompile(project->apk(), location, project->framework());
        // Bind
        this->connect(decompile, SIGNAL(output(const QString &)), this, SLOT(__output(const QString &)));
        this->connect(decompile, SIGNAL(newStatusInfo(const QString &, const QString &)), this, SLOT(__showStatusInfo(const QString &, const QString &)));
        this->connect(decompile,SIGNAL(newInfo(const QString &)),this,SLOT(__showConsoleInfo(const QString &)));
        // Execute
        decompile->start();
        // Status
        this->_statusbar->progress(-1);
        this->_statusbar->message(text("start_decompile").arg(project->apk()));
        break;
    }
    case UI::Toolbar::DECOMPILE_DEX:
    {
        QString location = QString(project->location()).append('/').append(project->name());
        // Prepare
        Runtime::decodedex *decode_dex = new Runtime::decodedex(project->apk(), location, project->framework());
        // Bind
        this->connect(decode_dex, SIGNAL(output(const QString &)), this, SLOT(__output(const QString &)));
        this->connect(decode_dex, SIGNAL(newStatusInfo(const QString &, const QString &)), this, SLOT(__showStatusInfo(const QString &, const QString &)));
        this->connect(decode_dex,SIGNAL(newConsoleInfo(const QString &)),this,SLOT(__showConsoleInfo(const QString &)));
        // Execute
        decode_dex->start();
        // Status
        this->_statusbar->progress(-1);
        this->_statusbar->message(tr("Decompling dex"));
        break;
    }
    case UI::Toolbar::DECOMPILE_RES:
    {
        QString location = QString(project->location()).append('/').append(project->name());
        // Prepare
        Runtime::decoderes *decode_res = new Runtime::decoderes(project->apk(), location, project->framework());
        // Bind
        this->connect(decode_res, SIGNAL(output(const QString &)), this, SLOT(__output(const QString &)));
        this->connect(decode_res, SIGNAL(newStatusInfo(const QString &, const QString &)), this, SLOT(__showStatusInfo(const QString &, const QString &)));
        this->connect(decode_res,SIGNAL(newConsoleInfo(const QString &)),this,SLOT(__showConsoleInfo(const QString &)));
        // Execute
        decode_res->start();
        // Status
        this->_statusbar->progress(-1);
        this->_statusbar->message(tr("Decompling resources"));
        break;
    }
    case UI::Menubar::BUILD:
    case UI::Toolbar::BUILD:
    {
        QString directory = this->_projects->selected();
        if (directory.isEmpty())
            break;
        // Prepare
        Runtime::Recompile *recompile = new Runtime::Recompile(directory);
        // Bind
        this->connect(recompile, SIGNAL(output(const QString &)), this, SLOT(__output(const QString &)));
        this->connect(recompile, SIGNAL(recompile(const QString &, const QString &)), this, SLOT(__recompile(const QString &, const QString &)));
        this->connect(recompile, SIGNAL(newInfo(const QString &)), this, SLOT(__showConsoleInfo(const QString &)));
        // Execute
        recompile->start();
        // Status
        this->_statusbar->progress(-1);
        this->_statusbar->message(text("start_recompile").arg(directory));
        break;
    }
    case UI::Toolbar::DEX2JAR:
    {
        QString location = QString(project->location()).append('/').append(project->name());
        // Prepare
        Runtime::dex2jar *dex2_jar = new Runtime::dex2jar(project->apk(), location, project->framework());
        // Bind
        this->connect(dex2_jar, SIGNAL(output(const QString &)), this, SLOT(__output(const QString &)));
        this->connect(dex2_jar, SIGNAL(newStatusInfo(const QString &, const QString &)), this, SLOT(__showDex2JarStatusInfo(const QString &, const QString &)));
        this->connect(dex2_jar,SIGNAL(newConsoleInfo(const QString &)),this,SLOT(__showConsoleInfo(const QString &)));
        // Execute
        dex2_jar->start();
        // Status
        this->_statusbar->progress(-1);
        this->_statusbar->message(tr("Converting dex to jar"));
        this->_toolbar->_showjava->setEnabled(true);
        break;
    }

    case UI::Toolbar::SHOW_JAVA:
    {
        QString location = QString(project->location()).append('/').append(project->name());
        // Prepare
        Runtime::showjava *show_java = new Runtime::showjava(location);
        // Bind
        this->connect(show_java, SIGNAL(output(const QString &)), this, SLOT(__output(const QString &)));
        this->connect(show_java, SIGNAL(newStatusInfo(const QString &, const QString &)), this, SLOT(__showShowJavaStatusInfo(const QString &)));
        this->connect(show_java,SIGNAL(newConsoleInfo(const QString &)),this,SLOT(__showConsoleInfo(const QString &)));
        // Execute
        show_java->start();
        // Status
        this->_statusbar->progress(-1);
        this->_statusbar->message(tr("Converting base.jar to java"));
        break;
    }

    case UI::Menubar::CLEAN:
    {
        QString path = this->_projects->selected();
        if (path.isEmpty())
            break;
        bool success = false;
        QDir directory(QString(path).append("/build"));
        if (directory.exists()) {
            directory.setFilter( QDir::NoDotAndDotDot | QDir::Files );
            foreach(QString item, directory.entryList()) {
                directory.remove(item);
                success = true;
            }
            directory.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
            foreach(QString item, directory.entryList()) {
                QDir sub(directory.absoluteFilePath(item));
                sub.removeRecursively();
                success = true;
            }
        }
        if (success) {
            this->_projects->refresh(path);
            this->_statusbar->message(text("success_clean").arg(path));
        } else
            this->_statusbar->message(text("success_clean").arg(path));
        break;
    }
    case UI::Menubar::CLOSE:
        this->_editorSmali->close();
        break;
    case UI::Menubar::COPY:
        this->_editorSmali->copy();
        break;
    case UI::Menubar::CUT:
        this->_editorSmali->cut();
        break;
    case UI::Menubar::DIRECTORY:
    case UI::Toolbar::DIRECTORY:
    {
        QString path = QFileDialog::getOpenFileName(this, text("title_project"), IDE::path(), QString("apktool.yml (*.yml)"), 0, 0);
        if (path.isNull() || path.isEmpty())
            break;
        QFileInfo info(path);
        if (info.exists() && info.isFile())
            this->open(info.absoluteFilePath());
        break;
    }
    case UI::Menubar::FIND:
    {
        Coder *coder = this->_editorSmali->coder();
        if (!coder || (coder == 0))
            break;
        if (this->_find)
            delete this->_find;
        this->_find = new Dialog::Find(false, this);
        this->_find->editor(coder);
        this->_find->show();
        break;
    }
    case UI::Menubar::GOTO:
    {
        Coder *coder = this->_editorSmali->coder();
        if (!coder || (coder == 0))
            break;
        bool ok;
        int line = QInputDialog::getInt(this, text("title_goto"), text("message_goto"), 1, 1, coder->document()->blockCount(), 1, &ok);
        if (ok) {
            QTextCursor cursor(coder->document()->findBlockByLineNumber(line - 1));
            coder->setTextCursor(cursor);
        }
        break;
    }
    case UI::Menubar::PASTE:
        this->_editorSmali->paste();
        break;
    case UI::Menubar::PRINT:
    //case UI::Toolbar::PRINT:
    {
        Coder *coder = this->_editorSmali->coder();
        if (!coder || (coder == 0))
            break;
        QPrinter printer;
        QPrintDialog *dialog = new QPrintDialog(&printer, this);
        if (dialog->exec() != QDialog::Accepted)
            break;
        coder->print(&printer);
        break;
    }
    case UI::Menubar::REDO:
        this->_editorSmali->redo();
        break;
    case UI::Menubar::SAVE:
        this->_editorSmali->save();
        break;
    case UI::Menubar::SAVE_ALL:
        this->_editorSmali->saveall();
        break;
    case UI::Menubar::UNDO:
        this->_editorSmali->undo();
        break;
    case UI::Menubar::REPLACE:
    {
        Coder *coder = this->_editorSmali->coder();
        if (!coder || (coder == 0))
            break;
        if (this->_replace != 0)
            delete this->_replace;
        this->_replace = new Dialog::Find(true, this);
        this->_replace->editor(coder);
        this->_replace->show();
        break;
    }
    case UI::Menubar::QUIT:
        this->close();
        break;
    case UI::Menubar::SETTINGS:
    {
        Dialog::Settings *settings = new Dialog::Settings(this);
        settings->exec();
        break;
    }
    case UI::Toolbar::SHELL:      
    {
        QProcess *process = new QProcess(this);
        QStringList arguments;
        QString command;
#ifdef Q_OS_MAC
        command.append("/usr/bin/osascript");
        QString aScript;
        aScript.append("tell application \"terminal\"\n")
                .append("activate\n")
                .append("do script \"cd ")
                .append(Utility::Configuration::apkstudio())
                .append(";clear\"\n")
                .append("end tell\n");
        arguments << QString("-l");
        arguments << QString("AppleScript");
        process->start(command,arguments);
        process->write(aScript.toUtf8());
        process->closeWriteChannel();

#elif Q_OS_WIN
        command.append("cmd.exe");
        arguments << QString("/k");
        arguments << QString("cd /d ").append(Utility::Configuration::apkstudio());
        process->start(command,arguments);
#else
        command.append("gnome-terminal");
        arguments << QString("--working-directory=").append(Utility::Configuration::apkstudio());       
        process->start(command,arguments);
#endif
        break;
    }

    default:
        break;
    }
}

void IDE::__changed()
{
    Coder *coder = this->_editorSmali->coder();
    if (!coder || (coder == 0))
        return;
    if (this->_find && (this->_find != NULL))
        this->_find->editor(coder);
    if (this->_replace && (this->_replace!= NULL))
        this->_replace->editor(coder);
}

void IDE::__clipboard(const QClipboard::Mode &mode)
{
    if (mode == QClipboard::Clipboard) {
        if (this->_clipboard->ownsClipboard())
            this->_menubar->enable(Menubar::PASTE, true);
        else
            this->_menubar->enable(Menubar::PASTE, false);
    }
}

void IDE::__closed(const QString &path)
{
    this->_editorSmali->close(path);
}

void IDE::__cutable(const bool yes)
{
    this->_menubar->disable(Menubar::COPY, true);
    this->_menubar->disable(Menubar::CUT, true);
    if (yes) {
        this->_menubar->enable(Menubar::COPY, true);
        this->_menubar->enable(Menubar::CUT, true);
    }
}

void IDE::__deleted(const QString &path)
{
    this->_editorSmali->deleted(path);
}

void IDE::__edit(const QString &path)
{
    this->_editorSmali->load(path);
    QString copy = path;
    QString fileName = copy.replace(this->_projects->selected(),QString(""));
    fileName.replace(QString(".smali"),QString(".java"));
    fileName.replace(QString("/smali"),QString(""));
    fileName = this->_projects->selected().append("/java").append(fileName);
    QFileInfo info(fileName);
    if (info.exists()) {
        this->_editorJava->load(info.absoluteFilePath());
    }
}

void IDE::__editorSmali(const int count)
{
    this->_menubar->disable(Menubar::CLOSE, true);
    this->_menubar->disable(Menubar::FIND, true);
    this->_menubar->disable(Menubar::GOTO, true);
    this->_menubar->disable(Menubar::PASTE, true);
    this->_menubar->disable(Menubar::PRINT, true);
    this->_menubar->disable(Menubar::REPLACE, true);
    this->_menubar->disable(Menubar::SAVE, true);
    this->_menubar->disable(Menubar::SAVE_ALL, true);
    this->_toolbar->disable(Toolbar::PRINT, true);
    if (count > 0) {
        this->_menubar->enable(Menubar::CLOSE, true);
        this->_menubar->enable(Menubar::FIND, true);
        this->_menubar->enable(Menubar::GOTO, true);
        if (this->_clipboard->ownsClipboard())
            this->_menubar->enable(Menubar::PASTE, true);
        this->_menubar->enable(Menubar::PRINT, true);
        this->_menubar->enable(Menubar::REPLACE, true);
        this->_menubar->enable(Menubar::SAVE, true);
        this->_menubar->enable(Menubar::SAVE_ALL, true);
    } else {
        this->_menubar->disable(Menubar::COPY, true);
        this->_menubar->disable(Menubar::CUT, true);
        this->_menubar->disable(Menubar::REDO, true);
        this->_menubar->disable(Menubar::UNDO, true);
        this->_editorSmali->_redo->setEnabled(false);
        this->_editorSmali->_undo->setEnabled(false);
    }
}

void IDE::__initialize()
{
    /*
     * @Splitter
     */
    // Main
    QList<int> sizes_1 = this->_mainHorizontal->sizes();
    int width_1 = sizes_1[0] + sizes_1[1];
    sizes_1[0] = static_cast<int>(width_1 / 5);
    sizes_1[1] = width_1 - sizes_1[0];
    this->_mainHorizontal->setSizes(sizes_1);

    QList<int> sizes_2 = this->_rightVertical->sizes();
    int width_2 = sizes_2[0] + sizes_2[1];
    sizes_2[1] = 0;
    sizes_2[0] = width_2 - sizes_2[1];
    this->_rightVertical->setSizes(sizes_2);

    QList<int> sizes_3 = this->_editorHorizontal->sizes();
    int width_3 = sizes_3[0]+sizes_3[1];
    sizes_3[0] = width_3;
    sizes_3[1] = 0;
    this->_editorHorizontal->setSizes(sizes_3);

    /*
     * @CLI
     */
    QStringList arguments = QCoreApplication::arguments();
    if (arguments.count() > 0) {
        foreach (const QString &argument, arguments) {
            if (argument.isEmpty())
                continue;
            QFileInfo file(argument);
        }
    }
}

void IDE::__showConsoleInfo(const QString& info) {
    this->_console->setText(info);
}

void IDE::__showStatusInfo(const QString& apk, const QString& path) {
    this->_statusbar->progress(0);
    if (path.isEmpty()) {
        this->_statusbar->message(text("stop_decompile_failed").arg(apk));
        return;
    }
    this->_statusbar->message(text("stop_decompile_success").arg(apk));
    this->open(path);
}

void IDE::__showDex2JarStatusInfo(const QString& apk, const QString& jar) {
    this->_statusbar->progress(0);
    if (jar.isEmpty()) {
        this->_statusbar->message(QString("dex2jar failed"));
        return;
    }
    QString out=apk;
    out = out.append("successfully converted to ").append(jar);
    this->_statusbar->message(out);
}

void IDE::__showShowJavaStatusInfo(const QString& java)
{
    this->_statusbar->progress(0);
    if (java.isEmpty()) {
        this->_statusbar->message(QString("show java failed"));
        return;
    }

    QString out = QString("successfully converted to java files at ").append(java);
    this->_statusbar->message(out);
}

void IDE::__message(const QString &text)
{
    QString message = QString(text);
    if (text.length() > 64) {
        QString left = QString(text).left(32);
        QString right = QString(text).right(32);
        message = QString(left).append("...").append(right);
    }
    emit this->_statusbar->message(message.trimmed());
}

void IDE::__output(const QString &text)
{
    if (text.isEmpty())
        return;
    // Directory
    QDir directory(Utility::Configuration::log());
    if (!directory.exists())
        directory.mkdir(Utility::Configuration::log());
    QString name = QString(Utility::Format::time(QDateTime::currentDateTime(), QString("yyyy-MM-dd_hh-mm-ss"))).append(".txt");
    QFile file(QString(directory.absolutePath()).append('/').append(name));
    if (file.exists())
        file.remove();
    if (!file.open(QIODevice::Text | QIODevice::WriteOnly))
        return;
    QTextStream stream(&file);
    stream << text << endl;
    file.close();
    QProcess::startDetached(Utility::Configuration::text(), QStringList(file.fileName()));
}

void IDE::__projects(const bool selected)
{
    if (selected) {
        this->_menubar->enable(Menubar::BUILD, true);
        this->_menubar->enable(Menubar::CLEAN, true);
        this->_menubar->enable(Menubar::PROPERTIES, true);
        this->_toolbar->enable(Toolbar::BUILD, true);
    } else {
        this->_menubar->disable(Menubar::BUILD, true);
        this->_menubar->disable(Menubar::CLEAN, true);
        this->_menubar->disable(Menubar::PROPERTIES, true);
        this->_toolbar->disable(Toolbar::BUILD, true);
    }
}

void IDE::__progress(const int value)
{
    emit this->_statusbar->progress(value);
}

void IDE::__recompile(const QString &directory, const QString &path)
{
    this->_statusbar->progress(0);
    if (path.isEmpty()) {
        this->_statusbar->message(text("stop_recompile_failed").arg(directory));
        this->_projects->refresh(directory, true);
        return;
    }
    this->_statusbar->message(text("stop_recompile_success").arg(directory));
    this->_statusbar->progress(0);
    QFileInfo project(directory);
    if (project.exists() && project.isDir())
        this->_projects->refresh(project.absoluteFilePath());
}

void IDE::__redoable(const bool yes)
{
    if (yes) {
       this->_menubar->enable(Menubar::REDO, true);
       this->_editorSmali->_redo->setEnabled(true);
    }

    else {
        this->_menubar->disable(Menubar::REDO, true);
        this->_editorSmali->_redo->setEnabled(false);
    }

}

void IDE::__renamed(const QString &current, const QString &previous)
{
    this->_editorSmali->renamed(current, previous);
}

void IDE::__toggle(const int action, const bool checked)
{
    switch (action)
    {
    case UI::Statusbar::SIDEBAR:
    case UI::Menubar::SIDEBAR:
    {
        QList<int> sizes = this->_mainHorizontal->sizes();
        int width = sizes[0] + sizes[1];
        if (checked) {
            sizes[0] = static_cast<int>(width / 4);
            sizes[1] = width - sizes[0];
        } else {
            sizes[1] = sizes[0] + sizes[1];
            sizes[0] = 0;
        }
        this->_mainHorizontal->setSizes(sizes);
        this->_menubar->toggle(Menubar::SIDEBAR, checked, true);
        this->_statusbar->toggle(Statusbar::SIDEBAR, checked, true);
        break;
    }
    case UI::Statusbar::TOGGLE_JAVA_VIEW:
    case UI::Menubar::TOGGLE_JAVA_VIEW:
    {
        QList<int> sizes = this->_editorHorizontal->sizes();
        int width = sizes[0] + sizes[1];
        if (checked) {
            sizes[0] = static_cast<int>(width / 2);
            sizes[1] = width - sizes[0];
        } else {
            sizes[0] = sizes[0] + sizes[1];
            sizes[1] = 0;
        }
        this->_editorHorizontal->setSizes(sizes);
        this->_menubar->toggle(Menubar::TOGGLE_JAVA_VIEW, checked, true);
        this->_statusbar->toggle(Statusbar::TOGGLE_JAVA_VIEW, checked, true);
        break;
    }
    case UI::Statusbar::TOGGLE_CONSOLE_VIEW:
    case UI::Menubar::TOGGLE_CONSOLE_VIEW:
    {
        QList<int> sizes = this->_rightVertical->sizes();
        int width = sizes[0] + sizes[1];
        if (checked) {
            sizes[1] = static_cast<int>(width / 4);
            sizes[0] = width - sizes[1];
        } else {
            sizes[0] = sizes[0] + sizes[1];
            sizes[1] = 0;
        }
        this->_rightVertical->setSizes(sizes);
        this->_menubar->toggle(Menubar::TOGGLE_CONSOLE_VIEW, checked, true);
        this->_statusbar->toggle(Statusbar::TOGGLE_CONSOLE_VIEW, checked, true);
        break;
    }
    default:
        break;
    }
}

void IDE::__undoable(const bool yes)
{
    if (yes) {
        this->_menubar->enable(Menubar::UNDO, true);
        this->_editorSmali->_undo->setEnabled(true);
    }
    else {
        this->_menubar->disable(Menubar::UNDO, true);
        this->_editorSmali->_undo->setEnabled(false);
    }
}

} // namespace UI


