#include "decoderes.h"

namespace Runtime {

decoderes::decoderes(const QString& _apk, const QString& _outDir, const QString& _tag) {
    this->_apk = _apk;
    this->_outDir = _outDir;
    this->_tag = _tag;
}

void decoderes::run() {
    // Arguments
    QStringList arguments;
    arguments << QString("-Xms").append(QString::number(Utility::Configuration::heap())).append("m");
    arguments << QString("-jar");
    arguments << Utility::Configuration::apktool();
    arguments << QString("--force");
    if (!this->_tag.isEmpty()) {
        arguments << QString("--frame-path");
        arguments << Utility::Configuration::framework();
        arguments << QString("--frame-tag");
        arguments << QString(this->_tag);
    }
    if (Utility::Configuration::verbose())
        arguments << QString("--verbose");
    arguments << QString("--output");
    arguments << QString(this->_outDir);
    arguments << QString("d");
    arguments << QString("-f");
    arguments << QString("-s");
    arguments << QString(this->_apk);
    // Process
    QProcess process;
    process.setEnvironment(QProcess::systemEnvironment());
    process.setProcessChannelMode(QProcess::MergedChannels);
    // Start
    process.start(QString("java"), arguments, QIODevice::ReadOnly);
    // Wait (Start)
    if (!process.waitForStarted()) {
        emit newStatusInfo(this->_apk, QString());
    }
    // Wait (Read)
    process.waitForReadyRead(-1);
    // Wait (Stop)
    process.waitForFinished(-1);

    QString decomOutput(process.readAllStandardOutput());
    emit newConsoleInfo(decomOutput);

    // Verify
    QString yml = QString(this->_outDir).append("/apktool.yml");
    QFileInfo info(yml);
    if (!info.exists() || !info.isFile()) {
        // Read
        QString output = process.readAll();
        emit decoderes::output(output);
        emit newStatusInfo(this->_apk, QString());
        return;
    } else
        // Broadcast
        emit newStatusInfo(this->_apk, info.absoluteFilePath());
}
}


