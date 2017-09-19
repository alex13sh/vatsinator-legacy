/*
 * worldviewport.h
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

#ifndef GUI_WORLDVIEWPORT_H
#define GUI_WORLDVIEWPORT_H

#include "gui/v8rgui_export.h"
#include <QtCore/QRectF>
#include <QtCore/QList>

namespace Vatsinator { namespace Gui {

/**
 * \ingroup Gui
 * @{
 */
class V8RGUI_EXPORT WorldViewport {
public:
    explicit WorldViewport(const QRectF& screen);

    const QList<QRectF>& rectangles() const { return m_rectangles; }

private:
    QList<QRectF> m_rectangles;

}; /** @} */

}} /* namespace Vatsinator::Gui */

#endif // GUI_WORLDVIEWPORT_H
