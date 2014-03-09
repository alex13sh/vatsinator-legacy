/*
 * firitem.h
 * Copyright (C) 2014  Michał Garapich <michal@garapich.pl>
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

#ifndef FIRITEM_H
#define FIRITEM_H

#include <QtOpenGL>
#include <QObject>
#include <QPointF>

#include "ui/map/mapitem.h"

class Fir;
class VertexBufferObject;

class FirItem : public QObject, public MapItem {
  Q_OBJECT
  
  /**
   * FirItem is used to draw single FIR border, background and label
   * on the map.
   */
  
public:
  FirItem(const Fir*, QObject* = nullptr);
  FirItem() = delete;
  
  virtual ~FirItem();
  
  void drawBorders() const;
  void drawBackground() const;
  void drawLabel() const;
  
  /**
   * Label coordinates.
   */
  const QPointF& position() const override;
  QString tooltipText() const override;
  QMenu* menu(QWidget*) const override;
  void showDetailsWindow() const override;
  
  inline const Fir*
  data() const { return __fir; }
  
private:
  void __prepareVbo();
  
private slots:
  void __generateLabel() const;
  
private:
  const Fir* __fir;
  QPointF    __position;
  
  VertexBufferObject* __borders;
  VertexBufferObject* __triangles;
  
  mutable GLuint __label;
  
};

#endif // FIRITEM_H
