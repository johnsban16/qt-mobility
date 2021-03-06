/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QLANDMARKFILEHANDLER_LMX_P_H
#define QLANDMARKFILEHANDLER_LMX_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <qlandmark.h>
#include <qlandmarkmanager.h>
#include <qlandmarkcategoryid.h>

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class QIODevice;

bool isURIAbsolute(const QString &uri);
QTM_USE_NAMESPACE

class QLandmarkFileHandlerLmx : public QObject
{
    Q_OBJECT

public:
    QLandmarkFileHandlerLmx(volatile const bool *cancel=0);
    ~QLandmarkFileHandlerLmx();

    QList<QLandmark> landmarks() const;
    void setLandmarks(const QList<QLandmark> &landmarks);

    void setCategoryIdNameHash(const QHash<QString,QString> &categoryIdNameHash);
    QList<QStringList> landmarkCategoryNames();

    void setTransferOption(QLandmarkManager::TransferOption option);

    bool importData(QIODevice *device);
    bool exportData(QIODevice *device, const QString &nsPrefix = QString());

    QString errorString() const;
    QLandmarkManager::Error errorCode() const;

//TODO: remove obsolete signals
signals:
    void error(const QString &error);
    void finishedImport();
    void finishedExport();

private:
    bool readLmx();
    bool readLandmarkCollection(QList<QLandmark> &landmarkCollection);
    bool readLandmark(QLandmark &landmark);
    bool readCoordinates(QLandmark &landmark);
    bool readAddressInfo(QLandmark &landmark);
    bool readMediaLink(QLandmark &landmark);
    bool readCategory(QString &name);

    bool writeLmx();
    bool writeLandmarkCollection(const QList<QLandmark> &landmarkCollection);
    bool writeLandmark(const QLandmark &landmark);
    bool writeCoordinates(const QLandmark &landmark);
    bool writeAddressInfo(const QLandmark &landmark);
    bool writeMediaLink(const QLandmark &landmark);
    bool writeCategory(const QLandmarkCategoryId &categoryId);

    QString m_ns;
    QString m_nsPrefix;

    QList<QLandmark> m_landmarks;

    QXmlStreamReader *m_reader;
    QXmlStreamWriter *m_writer;

    QLandmarkManager::TransferOption m_option;
    QString m_error;
    QLandmarkManager::Error m_errorCode;
    volatile const bool *m_cancel;
    QList<QStringList> m_landmarkCategoryNames;//list of category names belonging to each landmark

    QHash<QString, QString> m_categoryIdNameHash;//category id to name hash
};

#endif // #ifndef QLANDMARKFILEHANDLER_LMX_P_H
