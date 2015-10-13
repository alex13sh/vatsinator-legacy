/*
    flightdetailswindow.h
    Copyright (C) 2012  Michał Garapich michal@garapich.pl

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FLIGHTDETAILSWINDOW_H
#define FLIGHTDETAILSWINDOW_H

#include <QWidget>
#include "ui/ui_flightdetailswindow.h"

class Pilot;

/**
 * A window that shows the selected flight's information.
 */
class FlightDetailsWindow : public QWidget, private Ui::FlightDetailsWindow {
    Q_OBJECT
    
signals:
    /**
     * Emitted when user wants to track the flight. \c pilot becomes
     * \c nullptr if user cancels flight tracking.
     */
    void flightTracked(const Pilot* pilot);
    
public:
    /**
     * Creates new window for the provided \c pilot. Passes \c parent
     * to the \c QWidget constructor.
     */
    explicit FlightDetailsWindow(const Pilot* pilot, QWidget* parent = nullptr);
    
protected:
    virtual void showEvent(QShowEvent* event) override;
    
private slots:
    void __updateAirports();
    void __updateInfo();
    void __airlineUpdated();
    
private:
    const Pilot* __pilot;
    
};

#endif // FLIGHTDETAILSWINDOW_H
