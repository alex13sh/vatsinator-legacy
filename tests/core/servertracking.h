/*
 * servertracking.h
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

#ifndef SERVERTRACKING_H
#define SERVERTRACKING_H

#include <core/servertracker.h>
#include <QObject>

class ServerTracking : public QObject {
    Q_OBJECT
    
private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void iteration_0();
    void iteration_1();
    
private:
    Vatsinator::Core::ServerTracker* m_serverTracker;
    int m_iteration = 0;
};

#endif // SERVERTRACKING_H
