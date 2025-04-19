import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Windows
import QtQuick.Timeline 1.0

Rectangle {
    id: loading_root
    // title: "Answers"
    width: 240
    height: 130

    Item {
        id: percents_item   // свойство opacity item используется в качестве счетчика
        opacity: 1
        visible: true
    }

    ProgressBar {
        id: progressBar
        x: 20
        y: 98
        width: 200
        height: 16
        value: 1.00

        Text {
            id: _text
            x: 91
            y: 1
            text: (percents_item.opacity * 100).toFixed(0) + "%"
            font.pixelSize: 10
        }
    }

    Timeline {
        id: timeline
        animations: [
            TimelineAnimation {
                id: loadingAnimation
                running: true
                loops: 1
                duration: 15000
                to: 15000
                from: 0
            },
            TimelineAnimation {
                id: percentsAnimation
                running: true
                loops: 1
                duration: 15000
                to: 15000
                from: 0
            }
        ]
        startFrame: 0
        endFrame: 15000
        enabled: true

        KeyframeGroup {
            target: progressBar
            property: "value"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0.2
                frame: 1787
            }

            Keyframe {
                value: 0.3
                frame: 6340
            }

            Keyframe {
                value: 0.6
                frame: 7977
            }

            Keyframe {
                value: 0.95
                frame: 12116
            }

            Keyframe {
                value: 1
                frame: 15000
            }
        }

        KeyframeGroup {
            target: percents_item
            property: "opacity"
            Keyframe {
                value: 0
                frame: 0
            }

            Keyframe {
                value: 0.2
                frame: 1769
            }

            Keyframe {
                value: 0.3
                frame: 6322
            }

            Keyframe {
                value: 0.6
                frame: 7958
            }

            Keyframe {
                value: 0.95
                frame: 12097
            }

            Keyframe {
                value: 1
                frame: 15000
            }
        }
    }
}
