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

#include "cntsimcontactremoverequest.h"
#include "cntsymbiansimengine.h"
#include "cntsimstore.h"
#include <qcontactremoverequest.h>
#include <QDebug>

CntSimContactRemoveRequest::CntSimContactRemoveRequest(CntSymbianSimEngine *engine, QContactRemoveRequest *req)
    :CntAbstractSimRequest(engine, req)
{
    connect( simStore(), SIGNAL(removeComplete(QContactManager::Error)),
        this, SLOT(removeComplete(QContactManager::Error)), Qt::QueuedConnection );
    
    connect( simStore(), SIGNAL(getReservedSlotsComplete(QList<int>, QContactManager::Error)),
        this, SLOT(getReservedSlotsComplete(QList<int>, QContactManager::Error)), Qt::QueuedConnection );
}

CntSimContactRemoveRequest::~CntSimContactRemoveRequest()
{
    cancel();
}

void CntSimContactRemoveRequest::run()
{
    QContactRemoveRequest *r = req<QContactRemoveRequest>();
    
    if (!r->isActive())
        return;
       
    m_contactIds = r->contactIds();
    m_errorMap.clear();
    m_index = 0;
#ifdef SYMBIANSIM_BACKEND_CHECK_BEFORE_REMOVE
    m_reservedSlots.clear();
    getReservedSlots();    
#else
    removeNext();
#endif
}

void CntSimContactRemoveRequest::removeComplete(QContactManager::Error error)
{
    if (!req()->isActive())
        return;
    
    if (error)
        m_errorMap.insert(m_index, error);
    
    m_index++;
    singleShotTimer(KRequestDelay, this, SLOT(removeNext()));
}

void CntSimContactRemoveRequest::removeNext()
{
    QContactRemoveRequest *r = req<QContactRemoveRequest>();
    
    if (!r->isActive())
        return;
    
    if (r->contactIds().count() == 0) {
        QContactManagerEngine::updateContactRemoveRequest(r, QContactManager::BadArgumentError, m_errorMap, QContactAbstractRequest::FinishedState);
        return;
    }        
    
    // All contacts removed?
    if (m_index >= m_contactIds.count())
    {
        // Take first error from errormap (if any)
        QContactManager::Error error = QContactManager::NoError;
        if (m_errorMap.count())
            error = m_errorMap.begin().value();

        QContactManagerEngine::updateContactRemoveRequest(r, error, m_errorMap, QContactAbstractRequest::FinishedState);
        return;
    }

    // Remove next contact
    QContactLocalId contactId = m_contactIds.at(m_index);
    QContactManager::Error error = QContactManager::NoError;
    
#ifdef SYMBIANSIM_BACKEND_CHECK_BEFORE_REMOVE
    if (m_reservedSlots.contains(contactId))
        simStore()->remove(contactId, &error);
    else
        error = QContactManager::DoesNotExistError;
#else
    simStore()->remove(contactId, &error);
#endif

    if (error) {
        m_errorMap.insert(m_index, error);
        m_index++;
        singleShotTimer(KRequestDelay, this, SLOT(removeNext()));
    }
}

void CntSimContactRemoveRequest::getReservedSlotsComplete(QList<int> reservedSlots, QContactManager::Error error)
{
    QContactRemoveRequest *r = req<QContactRemoveRequest>();
    
    if (!r->isActive())
        return;
    
    if (error != QContactManager::NoError && error != QContactManager::DoesNotExistError) {
        QContactManagerEngine::updateContactRemoveRequest(r, error, m_errorMap, QContactAbstractRequest::FinishedState);
        return;
    }

    m_reservedSlots = reservedSlots;
    singleShotTimer(KRequestDelay, this, SLOT(removeNext()));
}

void CntSimContactRemoveRequest::getReservedSlots()
{
    QContactRemoveRequest *r = req<QContactRemoveRequest>();
    
    if (!r->isActive())
        return;
    
    QContactManager::Error error = QContactManager::NoError;
    if (!simStore()->getReservedSlots(&error)) {
        QContactManagerEngine::updateContactRemoveRequest(r, error, m_errorMap, QContactAbstractRequest::FinishedState);
    }
}
