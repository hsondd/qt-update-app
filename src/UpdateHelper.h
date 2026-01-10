#pragma once
#include <QObject>
#include <QQmlEngine> // <--- Thêm dòng này

class UpdaterHelper : public QObject {
    Q_OBJECT
    QML_ELEMENT       // <--- Bắt buộc có dòng này để QML nhận diện
public:
    explicit UpdaterHelper(QObject *parent = nullptr) : QObject(parent) {} // Thêm constructor cho chuẩn
    Q_INVOKABLE void checkForUpdates();
};