/*
    filedownloader.cpp
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
#include <QtNetwork>

#include "vatsinatorapplication.h"

#include "filedownloader.h"
#include "defines.h"

FileDownloader::FileDownloader(QProgressBar* _pb, QObject* _parent) :
    QObject(_parent),
    __pb(_pb), 
    __reply(NULL) {}

void
FileDownloader::fetch(const QUrl& _url) {
  if (!anyTasksLeft()) {
    __urls.enqueue(_url);
    __startRequest();
  } else {
    __urls.enqueue(_url);
  }
}

QString
FileDownloader::fileNameForUrl(const QUrl& _url) {
  QString baseName = QFileInfo(_url.path()).fileName();
  
  Q_ASSERT(!baseName.isEmpty());
  
  if (!QDir(QDir::tempPath()).isReadable()) {
    emit error(tr("Temporary directory (%1) is not readable!").arg(QDir::tempPath()));
    VatsinatorApplication::log("Temporary directory %s is not accessible!",
                               qPrintable(QDir::tempPath()));
    return QString();
  }
  
  QString absPath = QDir::fromNativeSeparators(QDir::tempPath()) %
                    "/" % baseName;
  
  VatsinatorApplication::log("Absolute downloaded file path: %s", qPrintable(absPath));
  
  if (QFile::exists(absPath))
    QFile(absPath).remove();
  
  return absPath;
}

void
FileDownloader::__startRequest() {
  if (!anyTasksLeft())
    return;
  
  QUrl url = __urls.dequeue();
  QString fileName = fileNameForUrl(url);
  
  if (fileName.isEmpty()) {
    __startRequest();
    return;
  }
  
  __output.setFileName(fileName);
  if (!__output.open(QIODevice::WriteOnly)) {
    emit error(tr("Could not open file (%1) for writing!").arg(__output.fileName()));
    VatsinatorApplication::log("Could not open file (%1) for writing!",
                               qPrintable(__output.fileName()));
    __startRequest();
    return;
  }
  
  __reply = __nam.get(QNetworkRequest(url));
  
  connect(__reply,      SIGNAL(finished()),
          this,         SLOT(__finished()));
  connect(__reply,      SIGNAL(readyRead()),
          this,         SLOT(__readyRead()));
  
  if (__pb) {
    connect(__reply,    SIGNAL(downloadProgress(qint64,qint64)),
            this,       SLOT(__updateProgress(qint64, qint64)));
    __pb->setEnabled(true);
  }
}

void
FileDownloader::__readyRead() {
  __output.write(__reply->readAll());
}

void
FileDownloader::__finished() {
  __reply->deleteLater();
  __output.close();
  
  if (__pb) {
    __pb->reset();
    __pb->setEnabled(false);
  }
  
  if (__reply->error()) {
    emit error(tr("Error downloading file: %1").arg(__reply->errorString()));
    VatsinatorApplication::log("Error downloading file: %s",
                               qPrintable(__reply->errorString()));
  } else {
    emit finished(QString(__output.fileName()));
    VatsinatorApplication::log("File %s downloaded, size: %i",
                               qPrintable(__output.fileName()),
                               __output.size());
  }
  
  __startRequest();
}

void
FileDownloader::__updateProgress(qint64 _read, qint64 _total) {
  __pb->setMaximum(_total);
  __pb->setValue(_read);
}