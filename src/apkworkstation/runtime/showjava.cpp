#include "showjava.h"

namespace Runtime {

showjava::showjava(const QString& _outDir) {
    this->_outDir = _outDir;
    process = new QProcess;
    connect(process,SIGNAL(readyRead()),this,SLOT(__readRead()));
    connect(process,SIGNAL(finished(int)),this,SLOT(__finished(int)));
}

void showjava::run() {
    // Arguments
    QStringList arguments;
    arguments << Utility::Configuration::apkstudio().append("/showjava/showjava.sh");
    arguments << this->_outDir;

    // Process
    process->setEnvironment(QProcess::systemEnvironment());
    // Start
    process->start(QString("sh"), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process->waitForStarted()) {
        emit newStatusInfo("Decompile java failed",1);
    }
}

void showjava::__readRead()
{
    QString jarOutput(process->readAllStandardOutput());
    emit newStatusInfo(jarOutput,0);
}

void showjava::__finished(int flag)
{
    //delete process;
    QFileInfo info(this->_outDir.append("/java"));
    if (info.exists() && info.isDir()) {
        emit newStatusInfo(QString("Decompile java successfully to ").append(info.absoluteFilePath()),1);
    }
}

}

