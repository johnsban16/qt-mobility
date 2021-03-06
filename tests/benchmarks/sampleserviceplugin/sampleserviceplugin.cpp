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
#include "sampleserviceplugin.h"

#include <qservicecontext.h>
#include <qabstractsecuritysession.h>

#include <QtPlugin>
#include <QSettings>

SampleServicePlugin::~SampleServicePlugin()
{
}

QObject* SampleServicePlugin::createInstance(const QServiceInterfaceDescriptor& descriptor, QServiceContext* context, QAbstractSecuritySession* session)
{
    if ( descriptor.interfaceName() == "com.nokia.qt.bm.TestInterfaceA" ) {
        return new SampleServicePluginClass(descriptor, context, session);
    } else if (descriptor.interfaceName() == "com.nokia.qt.bm.TestInterfaceB") {
        return new DerivedSampleServicePluginClass(descriptor, context, session);
    }

    //As per service xml this plugin supports com.nokia.qt.TestInterfaceC as
    //well but we deliberately return 0 to test behavior on null pointers
    return 0;
}

void SampleServicePlugin::installService()
{
    QSettings settings("com.nokia.qt.bm.serviceframework.tests", "SampleServicePlugin");
    settings.setValue("installed", true);
}

void SampleServicePlugin::uninstallService()
{
    QSettings settings("com.nokia.qt.bm.serviceframework.tests", "SampleServicePlugin");
    settings.setValue("installed", false);
}


SampleServicePluginClass::SampleServicePluginClass(const QServiceInterfaceDescriptor& descriptor, QServiceContext* context, QAbstractSecuritySession* session)
    : m_descriptor(descriptor),
      m_context(context),
      m_security(session)
{
}

void SampleServicePluginClass::testSlotOne()
{
    //do something that accesses the internal data
    m_descriptor.interfaceName();
}

DerivedSampleServicePluginClass::DerivedSampleServicePluginClass(const QServiceInterfaceDescriptor& descriptor, QServiceContext* context, QAbstractSecuritySession* session)
    : SampleServicePluginClass(descriptor,context,session)
{
}

void DerivedSampleServicePluginClass::testSlotOne()
{
    //do something that accesses the internal data
    m_descriptor.serviceName();
}


QServiceInterfaceDescriptor SampleServicePluginClass::descriptor() const 
{ 
    return m_descriptor;
}

Q_EXPORT_PLUGIN2(sfw_sampleserviceplugin, SampleServicePlugin)
