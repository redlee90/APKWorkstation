
QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = apkworkstation
TEMPLATE = app

SOURCES += \
    src/apkworkstation/ui/ide.cpp \
    src/apkworkstation/ui/menubar.cpp \
    src/apkworkstation/ui/projects.cpp \
    src/apkworkstation/ui/toolbar.cpp \
    src/apkworkstation/main.cpp \
    src/apkworkstation/dialog/settings.cpp \
    src/apkworkstation/utility/format.cpp \
    src/apkworkstation/utility/ui.cpp \
    src/apkworkstation/ui/completer.cpp \
    src/apkworkstation/ui/highlighter.cpp \
    src/apkworkstation/ui/coder.cpp \
    src/apkworkstation/ui/statusbar.cpp \
    src/apkworkstation/ui/xmlhighlighter.cpp \
    src/apkworkstation/dialog/project.cpp \
    src/apkworkstation/runtime/decompile.cpp \
    src/apkworkstation/runtime/recompile.cpp \
    src/apkworkstation/runtime/framework.cpp \
    src/apkworkstation/dialog/find.cpp \
    src/apkworkstation/runtime/build.cpp \
    src/apkworkstation/utility/text.cpp \
    src/apkworkstation/dialog/add.cpp \
    src/apkworkstation/runtime/rename.cpp \
    src/apkworkstation/runtime/decodedex.cpp \
    src/apkworkstation/runtime/decoderes.cpp \
    src/apkworkstation/runtime/dex2jar.cpp \
    src/apkworkstation/runtime/showjava.cpp \
    src/apkworkstation/ui/editorsmali.cpp \
    src/apkworkstation/ui/editorjava.cpp

HEADERS += \
    src/apkworkstation/bridge/constant.h \
    src/apkworkstation/bridge/variant.h \
    src/apkworkstation/ui/ide.h \
    src/apkworkstation/ui/menubar.h \
    src/apkworkstation/ui/projects.h \
    src/apkworkstation/ui/toolbar.h \
    src/apkworkstation/dialog/settings.h \
    src/apkworkstation/utility/configuration.h \
    src/apkworkstation/utility/format.h \
    src/apkworkstation/utility/resource.h \
    src/apkworkstation/utility/ui.h \
    src/apkworkstation/ui/completer.h \
    src/apkworkstation/ui/highlighter.h \
    src/apkworkstation/ui/coder.h \
    src/apkworkstation/ui/statusbar.h \
    src/apkworkstation/ui/xmlhighlighter.h \
    src/apkworkstation/dialog/project.h \
    src/apkworkstation/runtime/decompile.h \
    src/apkworkstation/runtime/recompile.h \
    src/apkworkstation/runtime/framework.h \
    src/apkworkstation/dialog/find.h \
    src/apkworkstation/runtime/build.h \
    src/apkworkstation/utility/text.h \
    src/apkworkstation/dialog/add.h \
    src/apkworkstation/runtime/rename.h \
    src/apkworkstation/runtime/decodedex.h \
    src/apkworkstation/runtime/decoderes.h \
    src/apkworkstation/runtime/dex2jar.h \
    src/apkworkstation/runtime/showjava.h \
    src/apkworkstation/ui/editorsmali.h \
    src/apkworkstation/ui/editorjava.h

RESOURCES += \
    res/language/language.qrc \
    res/completion/completion.qrc \
    res/highlight/highlight.qrc \
    res/font/font.qrc \
    res/icon/icon.qrc

TRANSLATIONS += \
    res/language/en.ts

win32:RC_FILE = res/icon/windows.rc
