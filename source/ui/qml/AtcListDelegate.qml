/*
 * AtcListDelegate.qml
 * Copyright (C) 2015  Michał Garapich <michal@garapich.pl>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

import QtQuick 2.4
import QtQuick.Controls 1.3

Rectangle {
    id: root
    
    signal clicked
    
    width: parent.width
    height: 150 /* TODO DPI-independent value */
    
    color: mouse.pressed ? palette.byHue(50) : palette.background()
    
    Column {
        anchors {
            left: parent.left
            leftMargin: 60
            right: parent.right
            rightMargin: 60
            verticalCenter: parent.verticalCenter
        }
        
        spacing: 5
        
        Row {
            width: parent.width
            spacing: 10
            
            Label {
                text: callsign
                font.bold: true
            }
            
            Label {
                text: icao
                verticalAlignment: Text.AlignVCenter
            }
        }
        
        Label {
            text: description
            font.italic: true
        }
        
        Rectangle {
            width: parent.width
            height: 3
            color: palette.divider()
        }
    }
    
    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
