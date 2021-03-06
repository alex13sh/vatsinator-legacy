/*
 * componentsqmlplugin.h
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

#ifndef IMPORTS_COMPONENTSQMLPLUGIN_H
#define IMPORTS_COMPONENTSQMLPLUGIN_H

#include <QQmlExtensionPlugin>

namespace Vatsinator { namespace Imports {

/**
 * \internal
 */
class ComponentsQmlPlugin : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    /**
     * \copydoc QQmlExtensionPlugin::registerTypes()
     */
    void registerTypes(const char* uri) override;
    
};

}} /* namespace Vatsinator::Imports */

#endif // IMPORTS_COMPONENTSQMLPLUGIN_H
