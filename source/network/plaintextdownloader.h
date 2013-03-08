/*
    plaintextdownloader.h
    Copyright (C) 2012-2013  Michał Garapich michal@garapich.pl

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


#ifndef PLAINTEXTDOWNLOADER_H
#define PLAINTEXTDOWNLOADER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QProgressBar>
#include <QObject>
#include <QQueue>
#include <QUrl>

class PlainTextDownloader : public QObject {
  
  /*
   * Handles http queries. Receives plain text.
   */

  Q_OBJECT

public:

  PlainTextDownloader(QProgressBar* = 0, QObject* = 0);

  void fetchData(const QString&);
  
  inline QProgressBar *
  getProgressBar() { return __progressBar; }
  
  inline const QProgressBar *
  getProgressBar() const { return __progressBar; }
  
  inline void
  setProgressBar(QProgressBar* _pb) { __progressBar = _pb; }
  
  inline bool
  anyTasksLeft() const { return !__urls.isEmpty(); }

private:
  void  __startRequest();

  QProgressBar*   __progressBar;

  QQueue< QUrl >  __urls;

  QString __temp;
  QString __data;

  QNetworkAccessManager __nam;

  QNetworkReply*  __reply;
  
private slots:
  void __readyRead();
  void __finished();
  void __updateProgress(qint64, qint64);
  void __onError(QNetworkReply::NetworkError);

signals:
  void finished(const QString&);
  void fetchError();

};

#endif // PLAINTEXTDOWNLOADERR_H
