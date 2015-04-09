#include "toolbar.h"

namespace UI {

Toolbar::Toolbar(QWidget *parent) :
    QToolBar(parent)
{

    this->_apk = new QAction(icon("apk"), tr("Load apk"), this);
    this->_decompile = new QAction(icon("all"),tr("Decompile all"),this);
    this->_decompile_dex = new QAction(icon("dex"),tr("Decompile dex"),this);
    this->_decompile_res = new QAction(icon("res"),tr("Decompile resource"),this);
    this->_dex2jar = new QAction(icon("d2j"),tr("dex2jar"),this);
    this->_showjava = new QAction(icon("java"),tr("Show java"),this);
    this->_build = new QAction(icon("build"), text("label_build"), this);
    this->_directory = new QAction(icon("directory"), text("label_directory"), this);    
    this->_shell = new QAction(icon("shell"), text("label_shell"), this);

    this->reset();

    this->connect(this->_directory, SIGNAL(triggered()), this, SLOT(__directory()));
    this->connect(this->_apk, SIGNAL(triggered()), this, SLOT(__apk()));
    this->connect(this->_build, SIGNAL(triggered()), this, SLOT(__build()));
    this->connect(this->_decompile, SIGNAL(triggered()), this, SLOT(__decompile()));
    this->connect(this->_decompile_dex, SIGNAL(triggered()), this, SLOT(__decompile_dex()));
    this->connect(this->_decompile_res,SIGNAL(triggered()),this,SLOT(__decompile_res()));
    this->connect(this->_dex2jar,SIGNAL(triggered()),this,SLOT(__dex2jar()));
    this->connect(this->_showjava,SIGNAL(triggered()),this,SLOT(__showjava()));
    this->connect(this->_shell,SIGNAL(triggered()),this,SLOT(__shell()));

    this->addAction(this->_directory);
    this->addAction(this->_apk);
    this->addAction(this->_decompile);
    this->addAction(this->_decompile_dex);
    this->addAction(this->_decompile_res);
    this->addAction(this->_dex2jar);
    this->addAction(this->_showjava);
    this->addAction(this->_build);
    this->addAction(this->_shell);
    this->setAcceptDrops(false);
    this->setMovable(false);
}

void Toolbar::disable(const int action, const bool block)
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

void Toolbar::enable(const int action, const bool block)
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

QAction *Toolbar::get(const int action)
{
    switch (action)
    {
    case APK:
        return this->_apk;
    case BUILD:
        return this->_build;
    case DECOMPILE:
        return this->_decompile;
    case DECOMPILE_DEX:
        return this->_decompile_dex;
    case DECOMPILE_RES:
        return this->_decompile_res;
    case DEX2JAR:
        return this->_dex2jar;
    case SHOW_JAVA:
        return this->_showjava;
    case DIRECTORY:
        return this->_directory;
    case SHELL:
        return this->_shell;
    default:
        return 0;
    }
}

void Toolbar::reset()
{
    this->_build->setEnabled(false);
    this->_decompile->setEnabled(false);
    this->_decompile_dex->setEnabled(false);
    this->_decompile_res->setEnabled(false);
    this->_dex2jar->setEnabled(false);
    this->_showjava->setEnabled(false);
}

void Toolbar::toggle(const int action, const bool check, const bool block)
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


