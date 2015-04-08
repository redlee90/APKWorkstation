#include "dex2jar.h"
#include <QDebug>

namespace Runtime {

dex2jar::dex2jar(const QString& _apk, const QString& _outDir, const QString& _tag) {
    this->_apk = _apk;
    this->_outDir = _outDir;
    this->_tag = _tag;
}

void dex2jar::run() {
    // Arguments
    QStringList arguments;
    arguments << Utility::Configuration::apkstudio().append("/dex2jar/d2j-dex2jar.sh");
    arguments << this->_apk;
    arguments << QString("-o");
    arguments << QString(this->_outDir).append("/base.jar");

    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    process.start(QString("sh"), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit newStatusInfo(this->_apk, QString());
    }
    // Wait (Read)
    process.waitForReadyRead(-1);
    // Wait (Stop)
    process.waitForFinished(-1);

    QString jarOutput(process.readAllStandardOutput());
    emit newConsoleInfo(jarOutput);

    QString baseJar = QString(this->_outDir).append("/base.jar");

    QFileInfo info(baseJar);
    if (info.exists()) {
       emit newStatusInfo(this->_apk, baseJar);
    }
}
}
