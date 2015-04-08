#ifndef VPZ_APKSTUDIO_UI_TOOLBAR_H
#define VPZ_APKSTUDIO_UI_TOOLBAR_H

#include <QAction>
#include <QIcon>
#include <QObject>
#include <QToolBar>
#include <QWidget>

#include "../utility/resource.h"



namespace UI {

class Toolbar : public QToolBar
{
    Q_OBJECT
public:
    // Action
    QAction *_directory;
    QAction *_apk;
    QAction *_build;
    QAction *_decompile;
    QAction *_decompile_dex;
    QAction *_decompile_res;
    QAction *_dex2jar;
    QAction *_showjava;
    QAction *_print;
    QAction *_shell;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("toolbar", name);
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("toolbar", key);
    }
private slots:
    void __apk()
    {
        emit action(APK);
    }
    void __build()
    {
        emit action(BUILD);
    }
    void __decompile() {
        emit action(DECOMPILE);
    }
    void __decompile_dex() {
        emit action(DECOMPILE_DEX);
    }
    void __decompile_res() {
        emit action(DECOMPILE_RES);
    }
    void __dex2jar() {
        emit action(DEX2JAR);
    }

    void __showjava() {
        emit action(SHOW_JAVA);
    }

    void __directory()
    {
        emit action(DIRECTORY);
    }
    void __print()
    {
        emit action(PRINT);
    }
    void __shell() {
        emit action(SHELL);
    }

public:
    // Constructor
    Toolbar(QWidget *parent = 0);
    // Destructor
    ~Toolbar() { }
    // Enum
    enum Action {
        APK = 30,
        BUILD,
        DECOMPILE,
        DECOMPILE_DEX,
        DECOMPILE_RES,
        DEX2JAR,
        SHOW_JAVA,
        DIRECTORY,
        PRINT,
        SHELL,
    };
    // Function
    void enable(const int, const bool);
    void disable(const int, const bool);
    QAction * get(const int);
    void reset();
    void toggle(const int, const bool, const bool = false);
signals:
    void action(int);
};

} // namespace UI



#endif // VPZ_APKSTUDIO_UI_TOOLBAR_H
