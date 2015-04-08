#ifndef VPZ_APKSTUDIO_UI_IDE_H
#define VPZ_APKSTUDIO_UI_IDE_H

#include <QApplication>
#include <QClipboard>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QDialog>
#include <QDir>
#include <QFileInfo>
#include <QFileDialog>
#include <QInputDialog>
#include <QIcon>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPrintDialog>
#include <QPrinter>
#include <QSize>
#include <QSplitter>
#include <QString>
#include <QTextStream>
#include <QTextEdit>
#include <QVariant>
#include <QWidget>

#include "editorsmali.h"
#include "editorjava.h"
#include "menubar.h"
#include "projects.h"
#include "statusbar.h"
#include "toolbar.h"
#include "../dialog/find.h"
#include "../dialog/project.h"
#include "../dialog/settings.h"
#include "../runtime/decompile.h"
#include "../runtime/decodedex.h"
#include "../runtime/decoderes.h"
#include "../runtime/dex2jar.h"
#include "../runtime/showjava.h"
#include "../runtime/recompile.h"
#include "../utility/resource.h"



namespace UI {

class IDE : public QMainWindow
{
    Q_OBJECT
private:
    Dialog::Project* project;
    // Clipbard
    QClipboard *_clipboard;
    // Dialog
    Dialog::Find *_find;
    Dialog::Find *_replace;
    // Event
    void closeEvent(QCloseEvent *);
    // Function
    void context();
    void open(const QString &);
    static const QString path()
    {
        return Utility::Resource::root();
    }
    void terminate();

    // Panel
    Projects *_projects;
    Editors *_editorSmali;
    editorJava *_editorJava;
    QTextEdit *_console;

    // Resource
    static QString text(const char *key)
    {
        return Utility::Resource::text("ide", key);
    }
    // Splitter
    QSplitter *_mainHorizontal;
    QSplitter *_leftVertical;
    QSplitter *_rightVertical;
    QSplitter *_editorHorizontal;
    // UI
    Menubar *_menubar;
    Statusbar *_statusbar;
    Toolbar *_toolbar;
private slots:
    void __action(const int);
    void __build()
    {
        this->__action(Toolbar::BUILD);
    }
    void __changed();
    void __clipboard(const QClipboard::Mode & = QClipboard::Selection);
    void __closed(const QString &);
    void __cutable(const bool);
    //void __decompile(const QString &, const QString &);
    void __deleted(const QString &);
    void __edit(const QString &);
    void __editorSmali(const int);
    void __message(const QString &);
    void __output(const QString &);
    void __projects(const bool);
    void __progress(const int);
    void __recompile(const QString &, const QString &);
    void __redoable(const bool);
    void __renamed(const QString &, const QString &);
    void __toggle(const int, const bool);
    void __undoable(const bool);
public:
    // Constructor
    IDE(QWidget * = 0);
    // Destrcutor
    ~IDE() { }
public slots:
    void __initialize();
    void __showConsoleInfo(const QString &);
    void __showStatusInfo(const QString &, const QString &);
    void __showDex2JarStatusInfo(const QString &, const QString &);
    void __showShowJavaStatusInfo(const QString &);
};

} // namespace UI



#endif // VPZ_APKSTUDIO_UI_IDE_H
