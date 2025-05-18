// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import PanCrack
import QtQuick.Timeline 1.0

Window {
    id: window

    width: loader_screen01.width
    height: loader_screen01.height

    visible: true
    color: "#00ffff"
    title: "PanCrack"

    Loader {
        id: loader_screen01
        width: 1920
        height: 1080
        source: "Screen01.ui.qml"
    }
    Loader {
        id: loader_loading
        width: 360
        height: 180
        source: "Loading.qml"
    }
    StateGroup {
        id: stateGroup
        state: "LoadingState"
        states: [
            State {
                name: "LoadingState"

                PropertyChanges {
                    target: loader_screen01
                    visible: false
                    active: true
                }

                PropertyChanges {
                    target: window
                    width: 360
                    height: 180
                }
            },
            State {
                name: "MainScreenState"

                PropertyChanges {
                    target: loader_screen01
                    active: true
                }

                PropertyChanges {
                    target: loader_loading
                    visible: false
                    active: false
                }
            }
        ]
    }
    Timeline {
        id: timeline
        animations: [
            TimelineAnimation {
                id: timelineAnimation
                running: false
                loops: 1
                duration: 1000
                to: 1000
                from: 0
            }
        ]
        startFrame: 0
        endFrame: 1000
        enabled: false
    }
    Timer {
        // interval: 1000
        interval: 17000
        running: true
        onTriggered: {
            stateGroup.state = "MainScreenState"
            window.showFullScreen()
        }
    }
}

