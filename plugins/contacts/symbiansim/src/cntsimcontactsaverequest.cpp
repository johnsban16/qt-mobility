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

#include "cntsimcontactsaverequest.h"
#include "cntsymbiansimengine.h"
#include "cntsimstore.h"
#include <qcontactsaverequest.h>

CntSimContactSaveRequest::CntSimContactSaveRequest(CntSymbianSimEngine *engine, QContactSaveRequest *req)
    :CntAbstractSimRequest(engine, req)
{
    connect( simStore(), SIGNAL(writeComplete(QContact, QContactManager::Error)),
        this, SLOT(writeComplete(QContact, QContactManager::Error)), Qt::QueuedConnection );
}

CntSimContactSaveRequest::~CntSimContactSaveRequest()
{
    cancel();
}

void CntSimContactSaveRequest::run()
{
    QContactSaveRequest *r = req<QContactSaveRequest>();
    
    if (!r->isActive())
        return;
    
    m_contacts = r->contacts();
    m_errorMap.clear();
    m_index = 0;
    
    writeNext();
}

void CntSimContactSaveRequest::writeComplete(QContact contact, QContactManager::Error error)
{
    if (!req()->isActive())
        return;
    
    if (error)
        m_errorMap.insert(m_index, error);
    engine()->updateDisplayLabel(contact);
    m_contacts[m_index] = contact;
    m_index++;
    singleShotTimer(KRequestDelay, this, SLOT(writeNext()));
}

void CntSimContactSaveRequest::writeNext()
{
    QContactSaveRequest *r = req<QContactSaveRequest>();
    
    if (!r->isActive())
        return;
    
    if (r->contacts().count() == 0) {
        QContactManagerEngine::updateContactSaveRequest(r, QList<QContact>(), QContactManager::BadArgumentError, m_errorMap, QContactAbstractRequest::FinishedState);
        return;
    }    
    
    // All contacts written?
    if (m_index >= m_contacts.count())
    {
        // Take first error from errormap (if any)
        QContactManager::Error error = QContactManager::NoError;
        if (m_errorMap.count())
            error = m_errorMap.begin().value();
        
        QContactManagerEngine::updateContactSaveRequest(r, m_contacts, error, m_errorMap, QContactAbstractRequest::FinishedState);
        return;
    }

    // Get next contact
    QContact contact = m_contacts.at(m_index);
    
    // Validate & write contact 
    QContactManager::Error error = QContactManager::NoError;
    if (engine()->validateContact(contact, &error))
        simStore()->write(contact, &error);

    if (error) {
        m_errorMap.insert(m_index, error);
        m_index++;
        singleShotTimer(KRequestDelay, this, SLOT(writeNext()));
    }
}
