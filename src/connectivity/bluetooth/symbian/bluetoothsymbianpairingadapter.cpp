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

// INCLUDE FILES
#include "bluetoothsymbianpairingadapter.h"
#include "qbluetoothaddress.h"
#include "qbluetoothdeviceinfo.h"
#include "qbluetoothlocaldevice.h"
#include <qstring.h>
#include <btdevice.h>
#include "utils_symbian_p.h"
#include "bluetoothsymbianregistryadapter.h"
#include <QDebug>

QTM_BEGIN_NAMESPACE

/*Dedicated bonding attempt failure when the remote device responds with No-Bonding */
const static TInt BTKErrRemoteDeviceIndicatedNoBonding = KLinkManagerErrBase-4;
/*! \internal
    \class BluetoothSymbianPairingAdapter
    \brief The BluetoothSymbianPairingAdapter class is an adapter for bluetooth pairing functionality.

    The BluetoothSymbianPairingAdapter is constructed to use for a one QBluetoothAddress.
    It uses following Symbian class CBTEngConnMan for native operations.

    \ingroup connectivity-bluetooth
    \inmodule QtConnectivity
    \internal
*/

BluetoothSymbianPairingAdapter::BluetoothSymbianPairingAdapter(const QBluetoothAddress &address, QObject *parent)
    : QObject(parent)
    , m_pairingEngine(0)
    , m_address(address)
    , m_pairingOngoing(false)
    , m_errorCode(0)
    , m_pairingErrorString()
{
}

BluetoothSymbianPairingAdapter::~BluetoothSymbianPairingAdapter()
{
    delete m_pairingEngine;
}

int BluetoothSymbianPairingAdapter::errorCode() const
{
    return m_errorCode;
}

QString BluetoothSymbianPairingAdapter::pairingErrorString() const
{
    return m_pairingErrorString;
}

void BluetoothSymbianPairingAdapter::startPairing(QBluetoothLocalDevice::Pairing pairing)
{
    TBTDevAddr btAddress(m_address.toUInt64());

    if (!m_pairingEngine) {
        TRAPD(result, m_pairingEngine = CBTEngConnMan::NewL(this))
        if (result != KErrNone) {
            PairingComplete(btAddress, result);
            return;
        }
    }

    // start async pairing process
    m_pairingOngoing = true;
    int error = KErrBadHandle;

    if (m_pairingEngine) {
        error = KErrNone;
        error = m_pairingEngine->PairDevice(btAddress);
    }

    if (error != KErrNone) {
        PairingComplete(btAddress, error);
    }
}

void BluetoothSymbianPairingAdapter::ConnectComplete( TBTDevAddr& aAddr, TInt aErr,
                                       RBTDevAddrArray* aConflicts )
{
    Q_UNUSED(aAddr);
    Q_UNUSED(aErr);
    Q_UNUSED(aConflicts);
}

void BluetoothSymbianPairingAdapter::DisconnectComplete( TBTDevAddr& aAddr, TInt aErr )
{
    Q_UNUSED(aAddr);
    Q_UNUSED(aErr);
}

void BluetoothSymbianPairingAdapter::PairingComplete( TBTDevAddr& aAddr, TInt aErr )
{
    m_pairingErrorString.clear();
    m_pairingOngoing = false;

    switch (aErr) {
        case KErrNone: {
                // need to figure out if authorized or not
                QBluetoothLocalDevice::Pairing pairingStatus = QBluetoothLocalDevice::Paired; 
                BluetoothSymbianRegistryAdapter *registryAdapter = new BluetoothSymbianRegistryAdapter(
                        qTBTDevAddrToQBluetoothAddress(aAddr),NULL);
                if (registryAdapter) {
                    pairingStatus = registryAdapter->pairingStatus();
                    delete registryAdapter;
                }
                qDebug() << "pairingStatus = " << static_cast<int>(pairingStatus);
                emit pairingFinished(qTBTDevAddrToQBluetoothAddress(aAddr),pairingStatus);
            }   
            break;
        case BTKErrRemoteDeviceIndicatedNoBonding:
            m_pairingErrorString.append("Dedicated bonding attempt failure when the remote device responds with No-Bonding");
            break;
        default:
            m_pairingErrorString.append("Symbian pairing error=") + aErr;
            break;
    }
    if (aErr != KErrNone)
        emit pairingError(aErr);

}

#include "moc_bluetoothsymbianpairingadapter.cpp"

QTM_END_NAMESPACE
