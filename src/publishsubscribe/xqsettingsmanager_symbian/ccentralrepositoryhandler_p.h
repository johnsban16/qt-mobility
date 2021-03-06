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

#ifndef CENTRALREPOSITORYHANDLER_H
#define CENTRALREPOSITORYHANDLER_H

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

#include <e32base.h>
#include <centralrepository.h>

#include "settingshandlerbase_p.h"
#include "cenrepmonitor_p.h"

class XQSettingsKey;
class CRepository;

class CCentralRepositoryHandler : public CBase, public SettingsHandlerBase
{
public:
    static CCentralRepositoryHandler* NewL(TUid aUid);
    ~CCentralRepositoryHandler();

    TInt createKey(unsigned long key, const TInt& value);
    TInt createKey(unsigned long key, const TReal& value);
    TInt createKey(unsigned long key, const TDesC8& value);
    TInt createKey(unsigned long key, const TDesC16& value);

    TInt deleteKey(unsigned long key);

    TInt resetKey(unsigned long key);
    TInt resetRepository();

    TInt findKeyL(unsigned long partialKey, TUint32 mask, RArray<TUint32>& aFoundKeys);
    TInt findKeyL(unsigned long partialKey, TUint32 mask, const TInt& value, bool negative, RArray<TUint32>& aFoundKeys);
    TInt findKeyL(unsigned long partialKey, TUint32 mask, const TReal& value, bool negative, RArray<TUint32>& aFoundKeys);
    TInt findKeyL(unsigned long partialKey, TUint32 mask, const TDesC8& value, bool negative, RArray<TUint32>& aFoundKeys);
    TInt findKeyL(unsigned long partialKey, TUint32 mask, const TDesC16& value, bool negative, RArray<TUint32>& aFoundKeys);

    TInt startTransaction(CRepository::TTransactionMode transactionMode);
    TInt commitTransaction();
    void cancelTransaction();
    void failTransaction();
    TInt transactionState() const;

private:
    CCentralRepositoryHandler(TUid aUid);
    void ConstructL();

protected:  //From SettingsHandlerBase
    void setObserver(MSettingsHandlerObserver* observer);
    bool handleStartMonitoring(const XQSettingsKey& key, XQSettingsManager::Type type, MSettingsHandlerObserver& observer, TInt& error);
    bool handleStopMonitoring(const XQSettingsKey& key, TInt& error);

    TInt getValue(unsigned long key, TInt& value);
    TInt getValue(unsigned long key, TReal& value);
    void getValueL(unsigned long key, RBuf8& value);
    void getValueL(unsigned long key, RBuf16& value);

    TInt setValue(unsigned long key, const TInt& value);
    TInt setValue(unsigned long key, const TReal& value);
    TInt setValue(unsigned long key, const TDesC8& value);
    TInt setValue(unsigned long key, const TDesC16& value);

private:
    TUid m_uid;
    CRepository* iRepository;
    MSettingsHandlerObserver* m_observer;
    QHash<unsigned long int, CCenRepMonitor*> m_monitors;
};

#endif //CENTRALREPOSITORYHANDLER_H
