#ifndef VPZ_APKSTUDIO_UI_MENUBAR_H
#define VPZ_APKSTUDIO_UI_MENUBAR_H

#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QString>
#include <QWidget>

#include "../utility/resource.h"

namespace UI {

class Menubar : public QMenuBar
{
    Q_OBJECT
private:
    // Edit
    QAction * _copy;
    QAction * _cut;
    QAction * _goto;
    QAction * _paste;
    QAction * _redo;
    QAction * _undo;
    QAction *_findAndReplace;
    // File
    QAction * _apk;
    QAction * _close;
    QAction * _directory;
    QAction * _print;
    QAction * _quit;
    QAction * _save;
    QAction * _save_all;
    QAction * _settings;
    // Project
    QAction * _build;
    QAction * _clean;
    QAction * _properties;
    // View
    QAction * _sidebar;
    QAction * _toggle_java_view;
    QAction * _toggle_console_view;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("menubar", name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("menubar", key);
    }
private slots:
    // Edit
    void __copy()
    {
        emit action(COPY);
    }
    void __cut()
    {
        emit action(CUT);
    }
    void __goto()
    {
        emit action(GOTO);
    }
    void __paste()
    {
        emit action(PASTE);
    }
    void __redo()
    {
        emit action(REDO);
    }
    void __undo()
    {
        emit action(UNDO);
    }
    // File
    void __close()
    {
        emit action(CLOSE);
    }
    void __apk()
    {
        emit action(APK);
    }
    void __directory()
    {
        emit action(DIRECTORY);
    }
    void __print()
    {
        emit action(PRINT);
    }
    void __quit()
    {
        emit action(QUIT);
    }
    void __save()
    {
        emit action(SAVE);
    }
    void __save_all()
    {
        emit action(SAVE_ALL);
    }
    void __settings()
    {
        emit action(SETTINGS);
    }
    void __build()
    {
        emit action(BUILD);
    }
    // Project
    void __clean()
    {
        emit action(CLEAN);
    }
    void __properties()
    {
        emit action(PROPERTIES);
    }
    // View
    void __sidebar(bool checked)
    {
        emit toggled(SIDEBAR, checked);
    }
    void __toggle_console_view(bool checked) {
        emit toggled(TOGGLE_CONSOLE_VIEW,checked);
    }
    void __toggle_java_view(bool checked) {
        emit toggled(TOGGLE_JAVA_VIEW,checked);
    }
    void __toggle_find_edit(bool checked) {
        emit toggled(FIND_AND_REPLACE,checked);
    }

public:
    enum Action {
        BUILD=1,
        CLEAN,
        CLOSE,
        COPY,
        CUT,
        GOTO,
        INSTALL,
        SIDEBAR,
        TOGGLE_CONSOLE_VIEW,
        TOGGLE_JAVA_VIEW,
        APK,
        DIRECTORY,
        PASTE,
        PRINT,
        PROPERTIES,
        REDO,
        FIND_AND_REPLACE,
        QUIT,
        SAVE,
        SAVE_ALL,
        SETTINGS,
        UNDO
    };
    Menubar(QWidget * = 0);
    void enable(const int, const bool);
    void disable(const int, const bool);
    QAction * get(const int);
    void reset();
    void toggle(const int, const bool, const bool = false);
signals:
    void action(const int);
    void toggled(const int, const bool);
};

} // namespace UI



#endif // VPZ_APKSTUDIO_UI_MENUBAR_H
