#pragma once
#include <QObject>
#include <QQmlEngine>

class UpdaterHelper : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:
    explicit UpdaterHelper(QObject *parent = nullptr) : QObject(parent) {}
    Q_INVOKABLE void checkForUpdates();
};