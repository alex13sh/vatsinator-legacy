/*
 * tileurl.cpp
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

#include <QtCore>

#include "tileurl.h"

TileUrl::TileUrl() :
    __zoom(0)
{

}

TileUrl::TileUrl(quint64 x, quint64 y, quint64 zoom) :
    __x(x),
    __y(y),
    __zoom(zoom)
{

}

QUrl
TileUrl::toUrl() const
{
    if (!isValid())
        return QUrl();
    
//     return QUrl(QStringLiteral("http://c.tile.openstreetmap.org/") % path());
//     return QUrl(QStringLiteral("http://otile1.mqcdn.com/tiles/1.0.0/sat/") % path());
    return QUrl(QStringLiteral("http://a.basemaps.cartocdn.com/light_all/") % path());
}

QString
TileUrl::path() const
{
    if (!isValid())
        return QString();
    
    return QStringLiteral("%1/%2/%3.png").arg(
        QString::number(__zoom),
        QString::number(__x),
        QString::number(__y));
}

bool
TileUrl::isValid() const
{
    return __zoom > 0;
}

bool
TileUrl::operator ==(const TileUrl& other) const
{
    return __x == other.__x && __y == other.__y && __zoom == other.__zoom;
}

TileUrl
TileUrl::fromUrl(const QUrl& url)
{
    QRegExp rx("light_all/(\\d+)/(\\d+)/(\\d+).{3}");
    int res = rx.indexIn(url.path());
    if (res != 1) {
        qWarning("Failed parsing url (%s) - caps: %d", qPrintable(url.toString()), res);
        return TileUrl();
    }
    
    quint64 x = rx.cap(2).toULongLong();
    quint64 y = rx.cap(3).toULongLong();
    quint64 zoom = rx.cap(1).toULongLong();
    
    return TileUrl(x, y, zoom);
}
