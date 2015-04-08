#include "showjava.h"

namespace Runtime {

showjava::showjava(const QString& _outDir) {
    this->_outDir = _outDir;
}

void showjava::run() {
    // Arguments
    QStringList arguments;
    arguments << Utility::Configuration::apkstudio().append("/showjava/showjava.sh");
    arguments << this->_outDir;

    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::ForwardedChannels);
    // Start
    process.start(QString("sh"), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit newStatusInfo(this->_outDir, QString());
    }
    // Wait (Read)
    process.waitForReadyRead(-1);
    // Wait (Stop)
    process.waitForFinished(-1);

    QString jarOutput(process.readAllStandardOutput());
    emit newConsoleInfo(jarOutput);

    QFileInfo info(this->_outDir.append("/java"));
    if (info.exists() && info.isDir()) {
        emit newStatusInfo(info.absoluteFilePath(),info.absoluteFilePath());
    }
}
}

