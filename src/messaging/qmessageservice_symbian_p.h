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

#ifndef QMESSAGESERVICE_SYMBIAN_P_H
#define QMESSAGESERVICE_SYMBIAN_P_H

#include "qmessageservice.h"

QTM_BEGIN_NAMESPACE

class QMessageServicePrivate : public QObject
{
	Q_OBJECT
    Q_DECLARE_PUBLIC(QMessageService)

public:
    QMessageServicePrivate(QMessageService* parent);
    ~QMessageServicePrivate();

	bool sendSMS(QMessage &message);
	bool sendMMS(QMessage &message);
	bool sendEmail(QMessage &message);
	bool show(const QMessageId& id);
	bool compose(const QMessage &message);
	bool retrieve(const QMessageId &messageId, const QMessageContentContainerId &id);
	bool retrieveBody(const QMessageId& id);
	bool retrieveHeader(const QMessageId& id);
	bool synchronize(const QMessageAccountId &id);
	
    bool queryMessages(const QMessageFilter &filter, const QMessageSortOrder &sortOrder, uint limit, uint offset) const;
    bool queryMessages(const QMessageFilter &filter, const QString &body, QMessageDataComparator::MatchFlags matchFlags, const QMessageSortOrder &sortOrder, uint limit, uint offset) const;
    
    bool countMessages(const QMessageFilter &filter);
    bool moveMessages(const QMessageIdList &messageIds, const QMessageFolderId &toFolderId);
    
    void setFinished(bool successful);
    
    void messagesFound(const QMessageIdList &ids, bool isFiltered, bool isSorted);
    void messagesCounted(int count);
    
    void cancel();

signals:
	void stateChanged(QMessageService::State);
	void messagesFound(const QMessageIdList&);
    //void messagesCounted(int count);
	void progressChanged(uint, uint);

private:	
    QMessageService *q_ptr;
    QMessageService::State _state;
    QMessageManager::Error _error;
    int _actionId;
    int _count;
    mutable bool _active;
    mutable int _pendingRequestCount;
    QMessageIdList _ids;
    mutable bool _sorted;
    mutable bool _filtered;

    mutable QMessageFilter _filter;
    mutable QMessageSortOrder _sortOrder;
    mutable int _limit;
    mutable int _offset;

    
    friend class CMTMEngine;
    friend class CFSEngine;
};

QTM_END_NAMESPACE

#endif // QMESSAGESERVICE_SYMBIAN_P_H
