import QtQuick
import QtQuick.Controls
import TestGithubUpdate

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    UpdaterHelper {
        id: updater
    }

    Component.onCompleted: updater.checkForUpdatesInBackground()

    Button {
        text: "Check for Updates"
        onClicked: updater.checkForUpdates()
    }
}
