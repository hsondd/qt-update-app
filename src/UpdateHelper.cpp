#include "UpdateHelper.h"

#include "updater.h"

void UpdaterHelper::checkForUpdates() {
    Updater::instance().checkAndShowUI();
}
