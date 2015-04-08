#include "statusbar.h"



namespace UI {

Statusbar::Statusbar(QWidget *parent) :
    QToolBar(parent)
{
    // Action
    this->_sidebar = new QAction(icon("sidebar"), tr("Toggle Project View"), this);
    this->_toggleJavaView = new QAction(icon("toggle_java_view"),tr("Toggle Java View"),this);
    this->_toggleConsoleView = new QAction(icon("toggle_console_view"),tr("Toggle Console View"),this);
    // Label
    this->_message = new QLabel(text("label_message"), this);
    // Progress
    this->_progress = new QProgressBar(this);
    // Spacer
    QWidget *spacer = new QWidget(this);
    /*
     * @Prepare
     */
    // Action
    this->_sidebar->setCheckable(true);
    this->_sidebar->setChecked(true);
    this->_toggleJavaView->setCheckable(true);
    this->_toggleJavaView->setChecked(false);
    this->_toggleConsoleView->setCheckable(true);
    this->_toggleConsoleView->setChecked(false);
    // Message
    this->_message->setStyleSheet("color: #333333; margin-left: 8px;");
    // Progress
    this->_progress->setMaximum(100);
    this->_progress->setMaximumHeight(16);
    this->_progress->setMaximumWidth(160);
    this->_progress->setMinimum(0);
    this->_progress->setStyleSheet("margin-right: 8px;");
    this->_progress->setTextVisible(false);
    // Spacer
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // Toolbar
    this->setAcceptDrops(false);
    this->setMovable(false);
    QMargins margins = this->contentsMargins();
    margins.setRight(4);
    this->setContentsMargins(margins);

    // Action
    this->connect(this->_sidebar, SIGNAL(toggled(const bool)), this, SLOT(__sidebar(const bool)));
    this->connect(this->_toggleJavaView,SIGNAL(toggled(const bool)),this,SLOT(__toggle_java_view(const bool)));
    this->connect(this->_toggleConsoleView,SIGNAL(toggled(const bool)),this,SLOT(__toggle_console_view(const bool)));

    // Action
    this->addAction(this->_sidebar);
    this->addAction(this->_toggleConsoleView);
    this->addAction(this->_toggleJavaView);
    // Progress
    this->addWidget(this->_message);
    // Spacer
    this->addWidget(spacer);
    // Progress
    this->addWidget(this->_progress);
}

QAction *Statusbar::get(const int action)
{
    switch (action)
    {
    case SIDEBAR:
        return this->_sidebar;
    case TOGGLE_JAVA_VIEW:
        return this->_toggleJavaView;
    case TOGGLE_CONSOLE_VIEW:
        return this->_toggleConsoleView;
    default:
        return 0;
    }
}

void Statusbar::toggle(const int action, const bool check, const bool block)
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

void Statusbar::message(const QString &text)
{
    if (text.isNull() || text.isEmpty())
        return;
    this->_message->setText(text);
}

void Statusbar::progress(const int value)
{
    if (value > -1) {
        if (this->_progress->maximum() < 100)
            this->_progress->setMaximum(100);
        this->_progress->setValue(value);
    } else {
        this->_progress->setMaximum(0);
        this->_progress->setValue(0);
    }
}

} // namespace UI


