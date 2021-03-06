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
#ifndef QMESSAGEADDRESS_H
#define QMESSAGEADDRESS_H
#include <QString>
#include <QList>
#include <qmessageglobal.h>

QTM_BEGIN_NAMESPACE

class QMessageAddressPrivate;

class Q_MESSAGING_EXPORT QMessageAddress
{
    friend class QMessageAddressPrivate;

public:
    enum Type {
        System = 1,
        Phone,
        Email,
        InstantMessage
        // Extensible
    };

    QMessageAddress();
    QMessageAddress(Type type, const QString &addressee);
    QMessageAddress(const QMessageAddress &other);

    virtual ~QMessageAddress();

    QMessageAddress& operator=(const QMessageAddress &other);

    bool operator==(const QMessageAddress &other) const;
    bool operator!=(const QMessageAddress &other) const;

    Type type() const;
    void setType(Type type);

    QString addressee() const;
    void setAddressee(const QString &addressee);

    static void parseEmailAddress(const QString& emailAddress, QString *name, QString *address, QString *suffix = 0, bool *startDelimeterFound = 0, bool *endDelimeterFound = 0);

private:
    QMessageAddressPrivate *d_ptr;
};

typedef QList<QMessageAddress> QMessageAddressList;

QTM_END_NAMESPACE

#endif
