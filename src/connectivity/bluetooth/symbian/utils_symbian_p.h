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

#ifndef UTILS_SYMBIAN_P_H
#define UTILS_SYMBIAN_P_H

#include <bttypes.h>
#include <bt_sock.h>

QT_BEGIN_HEADER

QTM_BEGIN_NAMESPACE

inline QBluetoothAddress qTBTDevAddrToQBluetoothAddress(const TBTDevAddr &address)
{
    return QBluetoothAddress(QString(QByteArray((const char *)address.Des().Ptr(), 6).toHex().toUpper()));
}
inline quint32 qTPackSymbianDeviceClass(const TInquirySockAddr &address)
{
    TUint8 minorClass = address.MinorClassOfDevice();
    TUint8 majorClass = address.MajorClassOfDevice();
    TUint16 serviceClass = address.MajorServiceClass();
    quint32 deviceClass = (0 << 2) | (minorClass << 6 ) | (majorClass <<5) | serviceClass;
    return deviceClass;
}
inline QString s60DescToQString(const TDesC &desc)
{
    return QString::fromUtf16(desc.Ptr(), desc.Length());
}
inline QByteArray s60Desc8ToQByteArray(const TDesC8 &desc)
{
    return QByteArray((const char*)desc.Ptr(), desc.Length());
}

QTM_END_NAMESPACE

QT_END_HEADER

#endif
