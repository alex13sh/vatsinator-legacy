/*
 * maprenderer.cpp
 * Copyright (C) 2014-2015  Michał Garapich <michal@garapich.pl>
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

#include <QtGui>
#include <chrono>

#include "plugins/mapdrawer.h"
#include "storage/settingsmanager.h"
#include "ui/map/maparea.h"
#include "ui/map/mapconfig.h"
#include "ui/map/mapitem.h"
#include "ui/map/mapscene.h"
#include "vatsimdata/pilot.h"
#include "vatsimdata/airport.h"
#include "vatsimdata/fir.h"
#include "vatsimdata/vatsimdatahandler.h"
#include "vatsinatorapplication.h"

#include "maprenderer.h"

namespace {
    
    inline qreal toMercator(qreal lat)
    {
        return qRadiansToDegrees(qLn(qTan(M_PI / 4 + qDegreesToRadians(lat) / 2)));
    }
    
    inline qreal fromMercator(qreal y)
    {
        return qRadiansToDegrees(2 * qAtan(qExp(qDegreesToRadians(y))) - M_PI / 2);
    }
    
}

MapRenderer::MapRenderer(QObject* parent) :
    QObject(parent),
    __mapDrawer(nullptr),
    __scene(new MapScene(this))
{
    __restoreMapState();
    connect(vApp()->vatsimDataHandler(), &VatsimDataHandler::vatsimDataUpdated, this, &MapRenderer::updated);
    connect(qApp, &QCoreApplication::aboutToQuit, this, &MapRenderer::__saveMapState);
}

MapRenderer::~MapRenderer()
{
    if (__mapDrawer)
        delete __mapDrawer;
}

WorldTransform
MapRenderer::transform() const
{
    return WorldTransform(viewport(), center(), zoom());
}

LonLat
MapRenderer::mapToLonLat(const QPoint& point)
{
    qreal m = qMax(viewport().width(), viewport().height());
    
    qreal x = (point.x() * 360 - 180 * viewport().width()) / (m * zoom()) + center().longitude();
    qreal y = fromMercator((180 * viewport().height() - point.y() * 360) / (m * zoom()) + toMercator(center().latitude()));
    
    return LonLat(x, y).bound();
}

void
MapRenderer::setMapDrawer(MapDrawer* drawer)
{
    if (__mapDrawer)
        delete __mapDrawer;
    
    __mapDrawer = drawer;
    __mapDrawer->initialize(this);
    
    emit mapDrawerChanged(__mapDrawer);
}

void
MapRenderer::setZoom(qreal zoom)
{
    __zoom = zoom;
    __updateScreen();
    emit updated();
    
    if (!scene()->isAnimating())
        emit zoomChanged(__zoom);
}

void
MapRenderer::setCenter(const LonLat& center)
{
    __center = center;
    __updateScreen();
    emit updated();
    emit centerChanged(__center);
}

qreal
MapRenderer::zoomStep(int steps)
{
    //count limiter for this function
    __actualZoomMaximum =
        qFloor(qLn((MapConfig::zoomMaximum() - MapConfig::zoomMinimum()) / MapConfig::zoomNormalizeCoef()) / qLn(MapConfig::zoomBase() + (MapConfig::zoomCoefficient() * 0.01)));
    
    //set the actual zoom level according to number of scroll wheel steps
    __actualZoom += steps;
    
    //limiting range of zoom
    __actualZoom = qBound(0, __actualZoom, __actualZoomMaximum);
    
    // count value of closeup
    return MapConfig::zoomMinimum() + MapConfig::zoomNormalizeCoef() *
        qPow(MapConfig::zoomBase() + (MapConfig::zoomCoefficient() * 0.01), __actualZoom);
}

void
MapRenderer::setViewport(const QSize& size)
{
    __viewport = size;
    __updateScreen();
    emit updated();
    emit viewportChanged(__viewport);
}

void
MapRenderer::paint(QPainter* painter, const QSet<MapItem*>& selectedItems)
{
    WorldTransform transform = this->transform();
    
    if (__mapDrawer) {
        __mapDrawer->draw(painter, transform);
    }
    
    scene()->inRect(__screen, [painter, &transform](const MapArea* area) {
        area->draw(painter, transform);
    });
    
    auto items = scene()->itemsInRect(__screen);
    std::sort(items.begin(), items.end(), [](auto a, auto b) {
        return a->z() < b->z();
    });
    
    std::for_each(items.begin(), items.end(), [painter, &transform, &selectedItems](auto item) {
        item->draw(painter, transform, selectedItems.contains((MapItem*&)item) ? MapItem::DrawSelected : static_cast<MapItem::DrawFlags>(0));
    });
}

void
MapRenderer::__restoreMapState()
{
    QSettings settings;
    
    settings.beginGroup("MapState");
    
    __actualZoom = settings.value("actualZoomCoefficient", 0).toInt();
    __zoom = settings.value("zoom", MapConfig::zoomDefault()).toReal();
    __center = settings.value("center", QVariant::fromValue<LonLat>(LonLat(0.0, 0.0))).value<LonLat>();
    
    settings.endGroup();
}

void
MapRenderer::__updateScreen()
{
    __screen.setTopLeft(mapToLonLat(QPoint(0, 0)));
    __screen.setBottomRight(mapToLonLat(QPoint(__viewport.width(), __viewport.height())));
    if (__screen.right() < __screen.left()) {
        __screen.setRight(MapConfig::longitudeMax());
    }
}

void
MapRenderer::__saveMapState()
{
    QSettings settings;
    
    settings.beginGroup("MapState");
    
    settings.setValue("actualZoomCoefficient", __actualZoom);
    settings.setValue("zoom", __zoom);
    settings.setValue("center", QVariant::fromValue<LonLat>(__center));
    
    settings.endGroup();
}