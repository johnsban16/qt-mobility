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


#ifndef QTRACKERCONTACTSLIVE_H
#define QTRACKERCONTACTSLIVE_H

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

#include <qcontact.h>
#include <qcontactdetail.h>
#include <qcontactphonenumber.h>
#include <qcontactname.h>
#include <qcontactnickname.h>

#include <QtTracker/Tracker>
#include <QtTracker/QLive>
#include <QtTracker/ontologies/nco.h>

using namespace SopranoLive;

namespace ContactContext {
    typedef enum Location {
        Unknown = 0,
        Home,
        Work
    };
}

/**
 * This class will abstact and hide how contact information is saved to Tracker
 * by using Live node.
 */
class QTrackerContactsLive
{
public:
    QTrackerContactsLive();

    /**
     * Set the QContact object that we are editing.
     *
     * \param qc The QContact object that is used for reading the data that
     *           will be stored in Tracker.
     */
    void setQContact(const QContact& qc);

    /**
     * Give the Live node object that is used for this transaction. This
     * object will be used internally by this object and will contain the data
     * that will be stored into Tracker.
     *
     * \param lc A Live node object representing a contact. See NCO ontology
     *           for details.
     */
    void setLiveContact(const Live<nco::PersonContact>& lc);

    /**
     * Return a service pointer that is used for this transaction. The Live
     * node in setLiveContact() is retrieved from this service.
     */
    RDFServicePtr service();

    /**
     * When all data is saved, we need to call this method to send the data to
     * tracker in one batch.
     */
    void commit();

    /**
     * Worker method that is doing the saving of the name properties. This method
     * will use the objects given by setQContact() and setLiveContact() to determine
     * what will be stored into Tracker.
     */
    void saveName();

private:
    /**
     * \deprecated. soon to be removed. \sa method implementation comment
     * Return a nco::Contact that is either a nco::Affiliation or
     * nco::PersonContact depending on the context (work or home) for the given contact detail.
     *
     * \param det The contact detail that we are currently interested in and which
     *            context we are examining.
     * \param ncoContact The nco::PersonContact that we want to store the contact
     *                    detail for.
     * \return Returns a nco::Affiliation is the QContactDetail context is
     *         work. Otherwise returns nco::PersonContact.
     */
    // TODO: We need to make these private once all savings are done using this class.
    Live<nco::Role> contactByContext(const QContactDetail&, const Live<nco::PersonContact>&);


    /**
     * \deprecated. soon to be removed. \sa method implementation comment
     *
     * This will look at the context of the QContactDetail and return the data if this is
     * home or work context.
     *
     * \param det The QContactDetail to investigate.
     * \return ContactContext::Home for home QContactDetail context.
     *         ContactContext::Work for work QContactDetail context.
     */
    // TODO: We need to make these private once all savings are done using this class.
    ContactContext::Location locationContext(const QContactDetail& det) const;

private:
    QContact editedContact_;
    Live<nco::PersonContact> liveContact_;

    RDFServicePtr service_;
    RDFTransactionPtr transaction_;
};

#endif // QTRACKERCONTACTSLIVE_H