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

#ifndef QTM_NETWORKCONFIGURATIONMANAGER_H
#define QTM_NETWORKCONFIGURATIONMANAGER_H

#include "qmobilityglobal.h"

#include <QtCore/qobject.h>
#include "qnetworkconfiguration.h"

QT_BEGIN_HEADER

QTM_BEGIN_NAMESPACE

class QNetworkConfigurationManagerPrivate;
class Q_BEARER_EXPORT QNetworkConfigurationManager : public QObject
{
    Q_OBJECT

public:
    
    enum Capability {
         CanStartAndStopInterfaces  = 0x00000001,
         DirectConnectionRouting = 0x00000002,
         SystemSessionSupport = 0x00000004,
         ApplicationLevelRoaming = 0x00000008,
         ForcedRoaming = 0x00000010,
         DataStatistics = 0x00000020,
         NetworkSessionRequired = 0x00000040
    };

    Q_DECLARE_FLAGS(Capabilities, Capability)

    QNetworkConfigurationManager( QObject* parent = 0 );
    virtual ~QNetworkConfigurationManager();

    
    QNetworkConfigurationManager::Capabilities capabilities() const;

    QNetworkConfiguration defaultConfiguration() const; 
    QList<QNetworkConfiguration> allConfigurations(QNetworkConfiguration::StateFlags flags = 0) const;
    QNetworkConfiguration configurationFromIdentifier(const QString& identifier) const;
    void updateConfigurations();

    bool isOnline() const;

Q_SIGNALS:
    void configurationAdded(const QNetworkConfiguration& config);
    void configurationRemoved(const QNetworkConfiguration& config);
    void configurationChanged(const QNetworkConfiguration& config);
    void onlineStateChanged(bool isOnline);
    void updateCompleted();

};

Q_DECLARE_OPERATORS_FOR_FLAGS(QNetworkConfigurationManager::Capabilities)

QTM_END_NAMESPACE

QT_END_HEADER

#endif //QTM_NETWORKCONFIGURATIONMANAGER_H

