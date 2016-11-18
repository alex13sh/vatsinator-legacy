/*
 * FlightDetailsPage.qml
 * Copyright (C) 2016  Michał Garapich <michal@garapich.pl>
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

import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import org.eu.vatsinator.Components 1.0
import org.eu.vatsinator.Vatsim 1.0

Page {
    id: root
    
    /// type:Vatsinator::Core::Pilot* The flight.
    property var flight: null
    
    signal airportClicked(var airport)
    
    header: ToolBar {
        id: toolbar
        
        height: 24 + 56 + 48
        
        GridLayout {
            columns: 2
            columnSpacing: 0
            rowSpacing: 0
            anchors.fill: parent
            
            Item {
                Layout.preferredHeight: 24
                Layout.columnSpan: 2
                Layout.fillWidth: true
            }
            
            Item {
                Layout.preferredHeight: 56
                Layout.preferredWidth: 56
            
                ToolButton {
                    anchors.centerIn: parent
                    height: 48
                    width: 48
                    
                    Image {
                        anchors.centerIn: parent
                        sourceSize.height: 24 * Screen.devicePixelRatio
                        sourceSize.width: 24 * Screen.devicePixelRatio
                        height: 24
                        width: 24
                        
                        source: "qrc:/icons/navigation/arrow_back_white.svg"
                    }
                    
                    onClicked: stackView.pop()
                }
            }
            
            Label {
                Layout.fillWidth: true
                
                font.pixelSize: 20
                font.weight: Font.Medium
                
                horizontalAlignment: Qt.AlignLeft
                verticalAlignment: Qt.AlignVCenter
                Material.theme: Material.Dark
                
                text: flight.callsign
            }
            
            TabBar {
                id: tabs
                
                Layout.columnSpan: 2
                Layout.fillWidth: true
                Layout.preferredHeight: 48
                
                Material.theme: Material.Dark
                Material.background: Material.primary
                Material.foreground: "white"
                Material.accent: "white"
                
                currentIndex: swipe.currentIndex
                
                TabButton {
                    height: 48
                    
                    font.pixelSize: 14
                    font.weight: Font.Medium
                    
                    text: qsTr("FLIGHT PLAN");
                }
                
                TabButton {
                    height: 48
                    
                    font.pixelSize: 14
                    font.weight: Font.Medium
                    
                    text: qsTr("PILOT");
                }
                
                TabButton {
                    height: 48
                    
                    font.pixelSize: 14
                    font.weight: Font.Medium
                    
                    text: qsTr("DETAILS");
                }
            }
        }
    }
    
    footer: ToolBar {
        height: Screen.orientation === Qt.PortraitOrientation ? 48 : 0
    }
    
    SwipeView {
        id: swipe
        
        anchors.margins: 0
        anchors.fill: parent
        
        currentIndex: tabs.currentIndex
        
        Item {
            Flickable {
                anchors.fill: parent
                contentWidth: parent.width
                contentHeight: plan.implicitHeight
                flickableDirection: Flickable.VerticalFlick
                
                ColumnLayout {
                    id: plan
                    
                    anchors.fill: parent
                    anchors.margins: 0
                    
                    spacing: 0
                    
                    RowLayout {
                        spacing: 16
                        
                        Item { Layout.preferredWidth: 8 }
                        
                        Label {
                            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                            font.pixelSize: 20
                            color: "#212121"
                            
                            text: flight.departure.icao
                            
                            MouseArea {
                                anchors.fill: parent
                                onClicked: root.airportClicked(flight.departure)
                            }
                        }
                        
                        FlightProgress {
                            Layout.fillWidth: true
                            
                            progress: flight.progress
                            color: Material.accent
                        }
                        
                        Label {
                            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                            font.pixelSize: 20
                            color: "#212121"
                            
                            text: flight.destination.icao
                            
                            MouseArea {
                                anchors.fill: parent
                                onClicked: root.airportClicked(flight.destination)
                            }
                        }
                        
                        Item { Layout.preferredWidth: 8 }
                    }
                    
                    Details {
                        name: qsTr("Flight rules")
                        value: flight.flightRules == Pilot.Ifr ? "IFR" : "VFR"
                        iconSource: "qrc:/icons/action/assignment_black.svg"
                    }
                    
                    Details {
                        name: qsTr("Cruise altitude")
                        value: flight.cruiseAltitude
                        iconSource: "qrc:/icons/image/filter_hdr_black.svg"
                    }
                    
                    Details {
                        name: qsTr("Planned TAS")
                        value: flight.plannedTas
                        iconSource: "qrc:/icons/content/forward.svg"
                    }
                    
                    CheckBox {
                        leftPadding: 72
                        
                        checked: false
                        text: qsTr("Track this flight")
                    }
                }
            }
        }
        
        Item {
            Flickable {
                anchors.fill: parent
                contentWidth: parent.width
                contentHeight: pilot.implicitHeight
                flickableDirection: Flickable.VerticalFlick
                
                GridLayout {
                    id: pilot
                    
                    anchors.fill: parent
                    anchors.margins: 0
                    
                    columns: 1
                    rowSpacing: 0
                    columnSpacing: 0
                    
                    Item { Layout.preferredHeight: 8 }
                    
                    Details {
                        name: qsTr("Pilot")
                        value: flight.realName + " (" + flight.pid + ")"
                    }
                    
                    Details {
                        name: qsTr("Server")
                        value: flight.serverName
                    }
                    
                    Details {
                        name: qsTr("Online from")
                        value: flight.onlineFrom
                    }
                }
            }
        }
        
        Item {
            Flickable {
                anchors.fill: parent
                contentWidth: parent.width
                contentHeight: details.implicitHeight
                flickableDirection: Flickable.VerticalFlick
                
                GridLayout {
                    id: details
                    
                    anchors.fill: parent
                    anchors.margins: 0
                    
                    columns: 1
                    rowSpacing: 0
                    columnSpacing: 0
                    
                    Item { Layout.preferredHeight: 8 }
                    
                    Details {
                        name: qsTr("Squawk")
                        value: flight.squawk
                    }
                    
                    Details {
                        name: qsTr("Ground speed")
                        value: qsTr("%1 knots").arg(flight.groundSpeed)
                    }
                    
                    Details {
                        name: qsTr("True Air Speed")
                        value: qsTr("%1 knots").arg(flight.tas)
                    }
                    
                    Details {
                        name: qsTr("Heading")
                        value: flight.heading
                    }
                    
                    Details {
                        name: qsTr("Altitude")
                        value: qsTr("%1 feet").arg(flight.altitude)
                    }
                }
            }
        }
    }
}