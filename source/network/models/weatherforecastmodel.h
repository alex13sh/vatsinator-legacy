/*
 * weatherforecastmodel.h
 * Copyright (C) 2013  Michał Garapich <michal@garapich.pl>
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

#ifndef WEATHERFORECASTMODEL_H
#define WEATHERFORECASTMODEL_H

#include <QAbstractTableModel>
#include <QByteArray>
#include <QVector>

class WeatherForecastModel : public QAbstractTableModel {
  
  /**
   * This is model for the weather forecast.
   */
  
  Q_OBJECT
  
public:
  
  explicit WeatherForecastModel(const QByteArray&, QObject* = 0);
  
  int rowCount(const QModelIndex& = QModelIndex()) const;
  int columnCount(const QModelIndex& = QModelIndex()) const;
  QVariant data(const QModelIndex&, int = Qt::DisplayRole) const;
  
private:
  
  struct ForecastForDay {
    QString day;
    float   high;
    float   low;
    QString condition;
  };
  
  void __parseJson(const QByteArray&);
  
  QVector<ForecastForDay> __data;
  bool __dataValid;
  
};

#endif // WEATHERFORECASTMODEL_H