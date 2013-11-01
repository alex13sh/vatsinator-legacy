/*
 * networkpage.h
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

#ifndef NETWORKPAGE_H
#define NETWORKPAGE_H

#include "ui/ui_networkpage.h"
#include "ui/pages/abstractsettingspage.h"

class NetworkPage :
    public AbstractSettingsPage,
    private Ui::NetworkPage {
  
  Q_OBJECT
  DECLARE_SETTINGS_PAGE(Network)

public:
  NetworkPage(QWidget* = 0);
  
  QString listElement() const;
  QString listIcon() const;
  QString pageName() const;
  
  /**
   * @variables
   * refresh_rate:      int
   * prompt_on_error:   bool
   * refresh_metars:    bool
   * cache_enabled:     bool
   * version_check:     bool
   */
  void updateFromUi() const;
  
protected:
  void restore(QSettings&);
  void save(QSettings&);

};

#endif // NETWORKPAGE_H
