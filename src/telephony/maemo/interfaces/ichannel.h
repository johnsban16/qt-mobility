/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef ICHANNEL_H
#define ICHANNEL_H

#include <QtCore/QtGlobal>
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

#include "maemo/interfaces/itypes.h"
#include "maemo/interfaces/iabstract.h"
#include "maemo/dbusproxy.h"

namespace DBus
{
    namespace Interfaces
    {
        class IChannel : public DBus::IAbstract
        {
            Q_OBJECT

        public:
            static inline const char *staticInterfaceName()
            {
                return "org.freedesktop.Telepathy.Channel";
            }

            IChannel(
                const QString& busName,
                const QString& objectPath,
                QObject* parent = 0
            );
            IChannel(
                const QDBusConnection& connection,
                const QString& busName,
                const QString& objectPath,
                QObject* parent = 0
            );
            IChannel(DBus::DBusProxy *proxy);

            Q_PROPERTY(QString ChannelType READ ChannelType)
            inline QString ChannelType() const
            {
                return qvariant_cast<QString>(internalPropGet("ChannelType"));
            }

            Q_PROPERTY(QStringList Interfaces READ Interfaces)
            inline QStringList Interfaces() const
            {
                return qvariant_cast<QStringList>(internalPropGet("Interfaces"));
            }

            Q_PROPERTY(uint TargetHandle READ TargetHandle)
            inline uint TargetHandle() const
            {
                return qvariant_cast<uint>(internalPropGet("TargetHandle"));
            }

            Q_PROPERTY(QString TargetID READ TargetID)
            inline QString TargetID() const
            {
                return qvariant_cast<QString>(internalPropGet("TargetID"));
            }

            Q_PROPERTY(uint TargetHandleType READ TargetHandleType)
            inline uint TargetHandleType() const
            {
                return qvariant_cast<uint>(internalPropGet("TargetHandleType"));
            }

            Q_PROPERTY(bool Requested READ Requested)
            inline bool Requested() const
            {
                return qvariant_cast<bool>(internalPropGet("Requested"));
            }

            Q_PROPERTY(uint InitiatorHandle READ InitiatorHandle)
            inline uint InitiatorHandle() const
            {
                return qvariant_cast<uint>(internalPropGet("InitiatorHandle"));
            }

            Q_PROPERTY(QString InitiatorID READ InitiatorID)
            inline QString InitiatorID() const
            {
                return qvariant_cast<QString>(internalPropGet("InitiatorID"));
            }

        public Q_SLOTS:
            inline QDBusPendingReply<> Close()
            {
                if (!invalidationReason().isEmpty()) {
                    return QDBusPendingReply<>(QDBusMessage::createError(
                        invalidationReason(),
                        invalidationMessage()
                    ));
                }
                return asyncCall(QLatin1String("Close"));
            }
            inline QDBusPendingReply<QString> GetChannelType()
            {
                if (!invalidationReason().isEmpty()) {
                    return QDBusPendingReply<QString>(QDBusMessage::createError(
                        invalidationReason(),
                        invalidationMessage()
                    ));
                }
                return asyncCall(QLatin1String("GetChannelType"));
            }
            inline QDBusPendingReply<uint, uint> GetHandle()
            {
                if (!invalidationReason().isEmpty()) {
                    return QDBusPendingReply<uint, uint>(QDBusMessage::createError(
                        invalidationReason(),
                        invalidationMessage()
                    ));
                }
                return asyncCall(QLatin1String("GetHandle"));
            }
            inline QDBusPendingReply<QStringList> GetInterfaces()
            {
                if (!invalidationReason().isEmpty()) {
                    return QDBusPendingReply<QStringList>(QDBusMessage::createError(
                        invalidationReason(),
                        invalidationMessage()
                    ));
                }
                return asyncCall(QLatin1String("GetInterfaces"));
            }

        Q_SIGNALS:
            void Closed();

        protected:
            virtual void invalidate(DBus::DBusProxy *, const QString &, const QString &);
        };
    }
}
Q_DECLARE_METATYPE(DBus::Interfaces::IChannel*)

#endif //ICHANNEL_H