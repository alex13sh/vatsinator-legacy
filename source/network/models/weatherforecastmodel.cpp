/*
 * weatherforecastmodel.cpp
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

#include <QtGui>
#include <qjson/parser.h>

#include "vatsinatorapplication.h"

#include "weatherforecastmodel.h"
#include "defines.h"

WeatherForecastModel::WeatherForecastModel(const QByteArray& _json, QObject* _parent) :
    QAbstractTableModel(_parent),
    __status(Progress) {
  __parseJson(_json);
}

WeatherForecastModel::WeatherForecastModel(QObject* _parent) :
    QAbstractTableModel(_parent),
    __status(Progress) {}

int
WeatherForecastModel::rowCount(const QModelIndex&) const {
  return __status == Fetched ? 2 : 1;
}

int
WeatherForecastModel::columnCount(const QModelIndex&) const {
  return __status == Fetched ? __data.size() : 1;
}

QVariant
WeatherForecastModel::data(const QModelIndex& _index, int _role) const {
  if (!_index.isValid() || _index.row() >= rowCount() || _index.column() >= columnCount())
    return QVariant();
  
  switch (_role) {
    
    case Qt::DisplayRole:
      switch (__status) {
        case Fetched:
          switch (_index.row()) {
            case 0:
              return __data.at(_index.column()).day;
            case 1:
              return QVariant();
          }
        case Error:
          return tr("Data not accessible");
        case Progress:
          return tr("Fetching data...");
      }
    
    case Qt::DecorationRole:
      switch (__status) {
        case Fetched:
          if (_index.row() == 1)
            return QPixmap(__iconForCondition(__data.at(_index.column()).iconNum));
        default:
          return QVariant();
      }
    
    case Qt::ToolTipRole:
      switch (__status) {
        case Fetched:
          return __data.at(_index.column()).condition;
        default:
          return QVariant();
      }
    
    case Qt::SizeHintRole:
      switch (__status) {
        case Fetched:
          Q_ASSERT(__data.size());
          if (_index.row() == 1)
            return QSize(67, 64);
          else
            return QSize(67, 30);
        case Error:
        case Progress:
          return QSize(469, 30);
      }
    
    case Qt::FontRole:
      if (__status == Fetched && _index.row() == 0)
        return VatsinatorApplication::boldFont();
      else
        return QFont();
  }
  
  return QVariant();
}

void
WeatherForecastModel::__parseJson(const QByteArray& _json) {
  QJson::Parser parser;
  bool ok;
  
  QVariant content = parser.parse(_json, &ok);
  if (!ok) {
    VatsinatorApplication::log("WeatherForecastModel: error parsing response");
    __status = Error;
    return;
  }
  
  for (QVariant day: content.toList()) {
    QVariantMap dayData = day.toMap();
    
    ForecastForDay forecast;
    forecast.day = dayData["day_of_week"].toString();
    forecast.high = dayData["high"].toFloat();
    forecast.low = dayData["low"].toFloat();
    forecast.condition = dayData["condition"].toString();
    forecast.iconNum = dayData["icon_num"].toInt();
    
    __data << forecast;
  }
  
  __status = Fetched;
}

QString
WeatherForecastModel::__iconForCondition(int _condition) const {
  switch (_condition) {
    case 0: return ":/weather/weather-clear.png";
    case 1: return ":/weather/weather-few-clouds.png";
    case 2: return ":/weather/weather-clouds.png";
    case 3: return ":/weather/weather-overcast.png";
    case 4: return ":/weather/weather-drizzle.png";
    case 5: return ":/weather/weather-light-rain.png";
    case 6: return ":/weather/weather-light-snow.png";
    case 7: return ":/weather/weather-snow.png";
    case 8: return ":/weather/weather-heavy-snow.png";
    case 9: return ":/weather/weather-foggy.png";
    case 10: return ":/weather/weather-breezy.png";
    case 11: return ":/weather/weather-windy.png";
    case 12: return ":/weather/weather-rain.png";
    case 13: return ":/weather/weather-rain-windy.png";
      
    default:
      return ":/weather/weather-clear.png";
  }
}
