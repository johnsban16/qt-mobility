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

#ifndef ORIENTATIONSENSORSYM_H
#define ORIENTATIONSENSORSYM_H

// QT Mobility Sensor API headers
#include <qsensorbackend.h>
#include <qorientationsensor.h>

// Internal Headers
#include "sensorbackendsym.h"

// Sensor client headers
// Orientation Sensor specific header
#include <sensrvorientationsensor.h>

QTM_USE_NAMESPACE

class COrientationSensorSym: public CSensorBackendSym
    {
public:
    /**
     * Factory function, this is used to create the orientation sensor object
     * @return COrientationSensorSym if successful, leaves on failure
     */
    static COrientationSensorSym* NewL(QSensor *sensor);

    /**
     * Destructor
     * Closes the backend resources
     */
    ~COrientationSensorSym();

private:
    /**
     * Default constructor
     */
    COrientationSensorSym(QSensor *sensor);

    /*
     * DataReceived is used to retrieve the sensor reading from sensor server
     * It is implemented here to handle orientation sensor specific
     * reading data and provides conversion and utility code
     */
    void DataReceived(CSensrvChannel &aChannel, TInt aCount, TInt aDataLost);
    void ProcessReading();

    /**
     * Second phase constructor
     * Initialize the backend resources
     */
    void ConstructL();

public:
    /**
     * Holds the id of the orientation sensor
     */
    static char const * const id;

private:
    QOrientationReading iReading;
    TSensrvOrientationData iData;
    };

#endif //ORIENTATIONSENSORSYM_H
