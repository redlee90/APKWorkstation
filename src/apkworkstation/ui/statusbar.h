#ifndef VPZ_APKSTUDIO_UI_STATUSBAR_H
#define VPZ_APKSTUDIO_UI_STATUSBAR_H

#include <QAction>
#include <QDesktopServices>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QObject>
#include <QProgressBar>
#include <QString>
#include <QToolBar>
#include <QToolButton>
#include <QUrl>
#include <QWidget>

#include "../utility/resource.h"



namespace UI {

class Statusbar : public QToolBar
{
    Q_OBJECT
private:
    // Action
    QAction *_sidebar;
    QAction *_toggleJavaView;
    QAction *_toggleConsoleView;
    // Label
    QLabel *_message;
    // Progress
    QProgressBar *_progress;
    // Resource
    static QIcon icon(const char *name)
    {
        return Utility::Resource::icon("statusbar", name);
    }
    void open(const QString &url)
    {
        QDesktopServices::openUrl(QUrl(url));
    }
    static QString text(const char *key)
    {
        return Utility::Resource::text("statusbar", key);
    }
private slots:
    // Action
    void __sidebar(const bool checked)
    {
        emit toggled(SIDEBAR, checked);
    }
    void __toggle_java_view(const bool checked)
    {
        emit toggled(TOGGLE_JAVA_VIEW,checked);
    }
    void __toggle_console_view(const bool checked)
    {
        emit toggled(TOGGLE_CONSOLE_VIEW,checked);
    }

public slots:
    void showMessage (const QString & info) {
        this->_message->setText(info);
    }

public:
    // Constructor
    Statusbar(QWidget *parent = 0);
    // Enum
    enum Action {
        SIDEBAR = 40,
        TOGGLE_JAVA_VIEW,
        TOGGLE_CONSOLE_VIEW
    };
    // Function
    QAction * get(const int);
    void message(const QString &);
    void progress(const int);
    void toggle(const int, const bool, const bool = false);
    // Destructor
    ~Statusbar() { }
signals:
    void toggled(const int, const bool);
};

} // namespace UI



#endif // VPZ_APKSTUDIO_UI_STATUSBAR_H
