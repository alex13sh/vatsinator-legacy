/*
    metar.cpp
    Copyright (C) 2012  Michał Garapich garrappachc@gmail.com

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

#include "vatsimdata/vatsimdatahandler.h"

#include "metar.h"
#include "defines.h"

Metar::Metar() : __icao("ZZZZ") {}

Metar::Metar(const QString& _icao, const QString& _metar) :
		__icao(_icao),
		__metar(_metar),
		__lastFetchedTime(QDateTime::currentDateTimeUtc()) {}

void
Metar::setMetar(const QString& _m) {
	__metar = _m;
	__lastFetchedTime = QDateTime::currentDateTimeUtc();
}


