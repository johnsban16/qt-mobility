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

#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <qsysteminfo.h>

#ifdef QTM_EXAMPLES_PREFER_LANDSCAPE
#include "ui_dialog_landscape.h"
#else //QTM_EXAMPLES_PREFER_LANDSCAPE
#ifdef Q_OS_SYMBIAN
#include "ui_dialog_s60.h"
#else //Q_OS_SYMBIAN
#include "ui_dialog.h"
#endif //Q_OS_SYMBIAN
#endif //QTM_EXAMPLES_PREFER_LANDSCAPE
QTM_USE_NAMESPACE

class Dialog : public QWidget, public Ui_Dialog
{
    Q_OBJECT
public:
    Dialog();
    ~Dialog();

protected:
    void changeEvent(QEvent *e);

private:
    void setupGeneral();
    void setupDevice();
    void setupDisplay();
    void setupStorage();
    void setupNetwork();
    void setupSaver();

    QSystemScreenSaver *saver;
    QSystemInfo *systemInfo;
    QSystemDeviceInfo *di;
    QSystemNetworkInfo *ni;

private slots:
    void tabChanged(int index);
    void getVersion(int index);
    void getFeature(int index);
    void setSaverEnabled(bool b);
    void updateDeviceLockedState();

    void netStatusComboActivated(int);
    void updateBatteryStatus(int);
    void updatePowerState(QSystemDeviceInfo::PowerState);
    void displayBatteryStatus(QSystemDeviceInfo::BatteryStatus);
    void updateProfile(QSystemDeviceInfo::Profile profile);
    void updateSimStatus();
    void updateProfile();

     void displayNetworkStatus(QSystemNetworkInfo::NetworkStatus);
     void networkStatusChanged(QSystemNetworkInfo::NetworkMode, QSystemNetworkInfo::NetworkStatus);
     void networkSignalStrengthChanged(QSystemNetworkInfo::NetworkMode, int);
     void networkNameChanged(QSystemNetworkInfo::NetworkMode,const QString &);
     void networkModeChanged(QSystemNetworkInfo::NetworkMode);

};

#endif // DIALOG_H
