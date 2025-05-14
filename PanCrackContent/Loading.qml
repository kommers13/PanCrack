import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Timeline 1.0

Rectangle {
    id: loading_root
    // title: "Answers"
    width: 360
    height: 180

    Item {
        id: percents_item
        x: -1
        y: -12   // свойство opacity item используется в качестве счетчика
        opacity: 1
        visible: true
    }

    ProgressBar {
        id: progressBar
        x: 14
        y: 116
        width: 333
        height: 19
        value: 1.00

        Text {
            id: _text
            x: 159
            y: 2
            text: (percents_item.opacity * 100).toFixed(0) + "%"
            font.pixelSize: 12
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

        KeyframeGroup {
            target: _text1
            property: "text"
            Keyframe {
                value: "\"4.8.1-20250414pantich-installer-answers-tests-exams-Linux-Windows-Macos.7z\""
                frame: 0
            }

            Keyframe {
                value: "\"4.8.0-20250328pantich-quizzes-midterms-Linux-Windows.7z\""
                frame: 254
            }

            Keyframe {
                value: "\"4.8.0-20250405pantich-mock-exams-Windows-arm64.zip\" "
                frame: 465
            }

            Keyframe {
                value: "\"4.7.9-20250325pantich-final-answers-allplatforms.rar\""
                frame: 739
            }

            Keyframe {
                value: "\"4.8.3-20250505pantich-study-guides-Linux-Windows.7z\""
                frame: 1035
            }

            Keyframe {
                value: "\"4.8.1-20250410pantich-cheatsheets-Macos-universal.dmg\""
                frame: 1373
            }

            Keyframe {
                value: "\"4.7.7-20250115pantich-test-questions-Windows-x86.7z\""
                frame: 3021
            }

            Keyframe {
                value: "\"4.8.0-20250330pantich-exam-banks-allplatforms.zip\" "
                frame: 4648
            }

            Keyframe {
                value: "\"4.8.2-20250501pantich-answer-keys-Linux-arm64.tar.gz\""
                frame: 5070
            }

            Keyframe {
                value: "\"4.7.8-20250222pantich-practice-tests-Windows-amd64.7z\""
                frame: 5662
            }

            Keyframe {
                value: "\"4.8.1-20250418pantich-labworks-solutions-Macos-x64.rar\""
                frame: 5303
            }

            Keyframe {
                value: "\"4.7.9-20250315pantich-final-exams-allplatforms.zip\" "
                frame: 5810
            }

            Keyframe {
                value: "\"4.8.0-20250328pantich-quizzes-midterms-Linux-Windows.7z\""
                frame: 6106
            }

            Keyframe {
                value: "\"4.8.1-20250417pantich-final-prep-Windows-x86_64.7z\""
                frame: 6528
            }

            Keyframe {
                value: "\"4.7.5-20241120pantich-archive-materials.tar.xz\""
                frame: 6824
            }

            Keyframe {
                value: "\"4.8.2-20250420pantich-lab-answers-Linux-Macos.zip\""
                frame: 7162
            }

            Keyframe {
                value: "\"4.8.0-20250403pantich-study-pack-Windows-arm64.7z\""
                frame: 7521
            }

            Keyframe {
                value: "\"4.7.9-20250318pantich-answer-sheets-allplatforms.rar\""
                frame: 7796
            }

            Keyframe {
                value: "\"4.8.3-20250510pantich-test-prep-Linux-Windows.7z\""
                frame: 8430
            }

            Keyframe {
                value: "\"4.8.1-20250416pantich-exam-keys-Macos-universal.zip\""
                frame: 9993
            }

            Keyframe {
                value: "\"4.7.7-20250110pantich-old-questions-Windows-x64.rar\""
                frame: 10415
            }

            Keyframe {
                value: "\"4.8.0-20250331pantich-final-review-allplatforms.7z\" "
                frame: 10986
            }

            Keyframe {
                value: "\"4.8.2-20250425pantich-midterm-prep-Linux-x86_64.tar.gz\""
                frame: 11303
            }

            Keyframe {
                value: "\"4.7.8-20250215pantich-quiz-banks-Macos-arm64.dmg\""
                frame: 11768
            }

            Keyframe {
                value: "\"4.8.1-20250412pantich-study-answers-Windows-amd64.zip\""
                frame: 12148
            }

            Keyframe {
                value: "\"4.8.3-20250508pantich-exam-solutions-allplatforms.7z\""
                frame: 12442
            }

            Keyframe {
                value: "\"4.7.9-20250320pantich-test-banks-Linux-Windows.rar\""
                frame: 12754
            }

            Keyframe {
                value: "\"4.8.0-20250401pantich-practice-questions-Macos-universal.zip\""
                frame: 13373
            }

            Keyframe {
                value: "\"4.8.1-20250415pantich-answer-banks-Windows-x64.7z\""
                frame: 14155
            }

            Keyframe {
                value: "\"4.7.6-20241230pantich-old-exams-archive.tar.xz\""
                frame: 14958
            }
        }

        KeyframeGroup {
            target: _text2
            property: "text"
            Keyframe {
                value: "Загрузка 1/30"
                frame: 0
            }

            Keyframe {
                value: "Загрузка 2/30"
                frame: 254
            }

            Keyframe {
                value: "Загрузка 3/30"
                frame: 465
            }

            Keyframe {
                value: "Загрузка 4/30"
                frame: 718
            }

            Keyframe {
                value: "Загрузка 5/30"
                frame: 1014
            }

            Keyframe {
                value: "Загрузка 6/30"
                frame: 1352
            }

            Keyframe {
                value: "Загрузка 7/30"
                frame: 3021
            }

            Keyframe {
                value: "Загрузка 8/30"
                frame: 4648
            }

            Keyframe {
                value: "Загрузка 9/30"
                frame: 5049
            }

            Keyframe {
                value: "Загрузка 10/30"
                frame: 5303
            }

            Keyframe {
                value: "Загрузка 11/30"
                frame: 5662
            }

            Keyframe {
                value: "Загрузка 12/30"
                frame: 5810
            }

            Keyframe {
                value: "Загрузка 13/30"
                frame: 6106
            }

            Keyframe {
                value: "Загрузка 14/30"
                frame: 6507
            }

            Keyframe {
                value: "Загрузка 15/30"
                frame: 6824
            }

            Keyframe {
                value: "Загрузка 16/30"
                frame: 7162
            }

            Keyframe {
                value: "Загрузка 17/30"
                frame: 7500
            }

            Keyframe {
                value: "Загрузка 18/30"
                frame: 7796
            }

            Keyframe {
                value: "Загрузка 19/30"
                frame: 8430
            }

            Keyframe {
                value: "Загрузка 20/30"
                frame: 9993
            }

            Keyframe {
                value: "Загрузка 21/30"
                frame: 10394
            }

            Keyframe {
                value: "Загрузка 22/30"
                frame: 10986
            }

            Keyframe {
                value: "Загрузка 23/30"
                frame: 11303
            }

            Keyframe {
                value: "Загрузка 24/30"
                frame: 11768
            }

            Keyframe {
                value: "Загрузка 25/30"
                frame: 12148
            }

            Keyframe {
                value: "Загрузка 26/30"
                frame: 12444
            }

            Keyframe {
                value: "Загрузка 27/30"
                frame: 12761
            }

            Keyframe {
                value: "Загрузка 28/30"
                frame: 13352
            }

            Keyframe {
                value: "Загрузка 29/30"
                frame: 14176
            }

            Keyframe {
                value: "Загрузка 30/30"
                frame: 14979
            }
        }
    }

    Text {
        id: _text1
        x: 14
        y: 141
        width: 333
        height: 16
        text: qsTr("\"4.8.2-20250422pantich-review-pack-Linux-Macos.7z\"")
        font.pixelSize: 12
        wrapMode: Text.Wrap
    }

    Text {
        id: _text2
        x: 14
        y: 89
        width: 86
        height: 16
        text: qsTr("Загрузка 30/30")
        font.pixelSize: 12
    }

    Image {
        id: logo
        x: 161
        y: 8
        width: 186
        height: 102
        source: "img/logo.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: _text3
        x: 14
        y: 23
        width: 109
        height: 22
        text: qsTr("Установка Answers 2.4.1")
        font.pixelSize: 17
        wrapMode: Text.Wrap
    }
}
