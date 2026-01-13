#include <QApplication>
#include <QQmlApplicationEngine>
#include "updater.h"

#ifdef Q_OS_MAC
#include "sparkleupdater.h"
#else
#include "defaultupdater.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#ifdef Q_OS_MAC
    auto updater = new updater::SparkleUpdater();
    updater->setAutomaticDownload(true);
    Updater::setInstance(updater);
#else
    auto updater = new updater::DefaultUpdater();
    updater->setAutomaticDownload(true);
    updater->setManifestUrl(
        QUrl(QStringLiteral("https://github.com/hsondd/qt-update-app/releases/latest/download/appcast-win.xml")));
    Updater::setInstance(updater);
#endif

    QQmlApplicationEngine engine;
    engine.loadFromModule("TestGithubUpdate", "Main");
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
