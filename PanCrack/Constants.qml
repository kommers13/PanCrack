pragma Singleton
import QtQuick 2.15
import QtQuick.Controls 2.15

QtObject {
    readonly property int width: 1920
    readonly property int height: 1080

    property string relativeFontDirectory: "fonts"

    /* Edit this comment to add your custom font */
    readonly property font font: Qt.font({
        family: Qt.application.font.family,
        pixelSize: Qt.application.font.pixelSize
    })

    readonly property font largeFont: Qt.font({
        family: Qt.application.font.family,
        pixelSize: Qt.application.font.pixelSize * 1.6
    })

    readonly property color backgroundColor: "#EAEAEA"

    // Заменяем StudioApplication на стандартное решение
    property url fontPath: Qt.resolvedUrl("../PanCrackContent/" + relativeFontDirectory)
}