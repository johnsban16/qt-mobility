/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef QCONTACTTRACKERBACKEND_P_H
#define QCONTACTTRACKERBACKEND_P_H

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

#include <QSharedData>
#include <QtTracker/Tracker>
#include <QtTracker/ontologies/nco.h>
#include <QtTracker/QLive>

using namespace SopranoLive;
#include "qcontact.h"
#include "qcontactname.h"
#include "qcontactphonenumber.h"
#include "qcontactmanager.h"
#include "qcontactmanagerenginefactory.h"
#include "qtrackercontactasyncrequest.h"

class QContactAbstractRequest;
class QContactChangeSet;

class QContactTrackerEngineData : public QSharedData
{
public:
    QContactTrackerEngineData()
        : QSharedData(), m_refCount(QAtomicInt(1))
    {
    }

    QContactTrackerEngineData(const QContactTrackerEngineData& other)
        : QSharedData(other), m_refCount(QAtomicInt(1)),
        m_lastUsedId(other.m_lastUsedId),
        m_definitions(other.m_definitions)
    {
    }

    void init();

    ~QContactTrackerEngineData() {}

    QAtomicInt m_refCount;
    mutable QContactLocalId m_lastUsedId;
    mutable QMap<QString, QContactDetailDefinition> m_definitions;
    mutable QMap<QContactAbstractRequest*, QTrackerContactAsyncRequest*> m_requests;
};

class QTCONTACTS_EXPORT QContactTrackerEngine : public QContactManagerEngine
{
Q_OBJECT

public:
    QContactTrackerEngine(const QMap<QString, QString>& parameters);
    QContactTrackerEngine(const QContactTrackerEngine& other);
    ~QContactTrackerEngine();
    QContactTrackerEngine& operator=(const QContactTrackerEngine& other);
    QContactManagerEngine* clone();
    void deref();

    /* Filtering */
    QList<QContactLocalId> contacts(const QContactFilter& filter, const QList<QContactSortOrder>& sortOrders, QContactManager::Error& error) const;

    /* Contacts - Accessors and Mutators */
    QList<QContactLocalId> contacts(const QList<QContactSortOrder>& sortOrders, QContactManager::Error& error) const;
    QContact contact(const QContactLocalId& contactId, QContactManager::Error& error) const;

    bool saveContact(QContact* contact, QContactManager::Error& error);

    QList<QContactManager::Error> saveContacts(QList<QContact>* contacts, QContactManager::Error& error);

    bool removeContact(const QContactLocalId& contactId, QContactManager::Error& error);
    QList<QContactManager::Error> removeContacts(QList<QContactLocalId>* contactIds, QContactManager::Error& error);

    /* Definitions - Accessors and Mutators */
    QMap<QString, QContactDetailDefinition> detailDefinitions(QContactManager::Error& error) const;
    QContactDetailDefinition detailDefinition(const QString& definitionId, QContactManager::Error& error) const;
    bool saveDetailDefinition(const QContactDetailDefinition& def, QContactManager::Error& error);
    bool removeDetailDefinition(const QContactDetailDefinition& def, QContactManager::Error& error);

    /* Asynchronous Request Support */
    void requestDestroyed(QContactAbstractRequest* req);
    bool startRequest(QContactAbstractRequest* req);
    bool waitForRequestFinished(QContactAbstractRequest* req, int msecs);

    /* Capabilities reporting */
    bool hasFeature(QContactManagerInfo::ManagerFeature feature) const;
    bool filterSupported(const QContactFilter& filter) const;
    QList<QVariant::Type> supportedDataTypes() const;


private:
    //called from both constructors, connecting to all contact NodeList changes signals
    void connectToSignals();
    RDFVariable contactDetail2Rdf(const RDFVariable& rdfContact, const QString& definitionName, const QString& fieldName) const;
    QContact contact_impl(const QContactLocalId& contactId, QContactManager::Error& error) const;
private:
    QSharedDataPointer<QContactTrackerEngineData> d;
    const QString contactArchiveFile;
    const QString contactArchiveDir;
    friend class ut_qtcontacts_trackerplugin;
};

class Q_DECL_EXPORT ContactTrackerFactory : public QObject, public QContactManagerEngineFactory
{
    Q_OBJECT
    Q_INTERFACES(QContactManagerEngineFactory)
    public:
        QContactManagerEngine* engine(const QMap<QString, QString>& parameters, QContactManager::Error&);
        QString managerName() const;
};

#endif