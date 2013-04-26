/*
    viewpage.cpp
    Copyright (C) 2013  Michał Garapich michal@garapich.pl

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

#include <QtGui>

#include "viewpage.h"
#include "defines.h"

namespace DefaultSettings {
  static const bool PILOTS_CHECKBOX           = true;
  static const bool AIRPORTS_CHECKBOX         = true;
  static const bool STAFFED_FIRS_CHECKBOX     = true;
  static const bool UNSTAFFED_FIRS_CHECKBOX   = true;
  static const bool DISPLAY_AIRPORT_LABELS    = true;
  static const bool EMPTY_AIRPORTS_CHECKBOX   = false;

  static const bool ALWAYS_CHECKBOX           = true;
  static const bool WHEN_HOVERED_CHECKBOX     = true;
  static const bool AIRPORT_RELATED_CHECKBOX  = true;
  
  static const bool AIRPORT_LABELS            = true;
}



ViewPage::ViewPage(QWidget* _parent) :
    AbstractSettingsPage(_parent) {
  setupUi(this);
  
  connect(ShowPilotsLabelsAlwaysCheckBox, SIGNAL(stateChanged(int)),
          this,                           SLOT(__handleAlwaysCheckBox(int)));
  __handleAlwaysCheckBox(ShowPilotsLabelsAlwaysCheckBox->checkState());
}

QString
ViewPage::listElement() const {
  return tr("View");
}

QString
ViewPage::listIcon() const {
  return ":/settings/preferences-view.png";
}

QVariant
ViewPage::get(const QString& _s) const {
  _S(pilots_layer,                 PilotsCheckBox->isChecked());
  _S(airports_layer,               AirportsCheckBox->isChecked());
  _S(staffed_firs,                 StaffedFirsCheckBox->isChecked());
  _S(unstaffed_firs,               UnstaffedFirsCheckBox->isChecked());
  _S(empty_airports,               InactiveAirportsCheckBox->isChecked());
  _S(pilot_labels.always,          ShowPilotsLabelsAlwaysCheckBox->isChecked());
  _S(pilot_labels.when_hovered,    ShowPilotsLabelsWhenHoveredCheckBox->isChecked());
  _S(pilot_labels.airport_related, ShowPilotsLabelsAirportRelatedCheckBox->isChecked());
  _S(airport_labels,               AlwaysRadioButton->isChecked());
  
  _S_END;
}

void
ViewPage::__restore(QSettings& _s) {
  PilotsCheckBox->setChecked(
    _s.value("pilots_layer", DefaultSettings::PILOTS_CHECKBOX).toBool());
  AirportsCheckBox->setChecked(
    _s.value("airports_layer", DefaultSettings::AIRPORTS_CHECKBOX).toBool());
  StaffedFirsCheckBox->setChecked(
    _s.value("staffed_firs", DefaultSettings::STAFFED_FIRS_CHECKBOX).toBool());
  UnstaffedFirsCheckBox->setChecked(
    _s.value("unstaffed_firs", DefaultSettings::UNSTAFFED_FIRS_CHECKBOX).toBool());
  InactiveAirportsCheckBox->setChecked(
    _s.value("empty_airports", DefaultSettings::EMPTY_AIRPORTS_CHECKBOX).toBool());
  ShowPilotsLabelsAlwaysCheckBox->setChecked(
    _s.value("pilot_labels.always", DefaultSettings::ALWAYS_CHECKBOX).toBool());
  ShowPilotsLabelsWhenHoveredCheckBox->setChecked(
    _s.value("pilot_labels.when_hovered", DefaultSettings::WHEN_HOVERED_CHECKBOX).toBool());
  ShowPilotsLabelsAirportRelatedCheckBox->setChecked(
    _s.value("pilot_labels.airport_labels", DefaultSettings::AIRPORT_RELATED_CHECKBOX).toBool());
  AlwaysRadioButton->setChecked(
    _s.value("airport_labels", DefaultSettings::AIRPORT_LABELS).toBool());
}

void
ViewPage::__save(QSettings& _s) {
  _s.setValue("pilots_layer", PilotsCheckBox->isChecked());
  _s.setValue("airports_layer", AirportsCheckBox->isChecked());
  _s.setValue("staffed_firs", StaffedFirsCheckBox->isChecked());
  _s.setValue("unstaffed_firs", UnstaffedFirsCheckBox->isChecked());
  _s.setValue("empty_airports", InactiveAirportsCheckBox->isChecked());
  _s.setValue("pilot_labels.always", ShowPilotsLabelsAlwaysCheckBox->isChecked());
  _s.setValue("pilot_labels.when_hovered", ShowPilotsLabelsWhenHoveredCheckBox->isChecked());
  _s.setValue("pilot_labels.airport_related", ShowPilotsLabelsAirportRelatedCheckBox->isChecked());
  _s.setValue("airport_labels", AirportsCheckBox->isChecked());
}

void
ViewPage::__handleAlwaysCheckBox(int _state) {
  if (_state == Qt::Checked) {
    ShowPilotsLabelsAlwaysCheckBox->setCheckState(Qt::Checked);
    ShowPilotsLabelsWhenHoveredCheckBox->setCheckState(Qt::Checked);
    ShowPilotsLabelsAirportRelatedCheckBox->setCheckState(Qt::Checked);

    ShowPilotsLabelsWhenHoveredCheckBox->setEnabled(false);
    ShowPilotsLabelsAirportRelatedCheckBox->setEnabled(false);
  } else {
    ShowPilotsLabelsAlwaysCheckBox->setCheckState(Qt::Unchecked);

    ShowPilotsLabelsWhenHoveredCheckBox->setEnabled(true);
    ShowPilotsLabelsAirportRelatedCheckBox->setEnabled(true);
  }
}
