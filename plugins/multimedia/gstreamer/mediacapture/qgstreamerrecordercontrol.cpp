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

#include "qgstreamerrecordercontrol.h"
#include <QtCore/QDebug>

QGstreamerRecorderControl::QGstreamerRecorderControl(QGstreamerCaptureSession *session)
    :QMediaRecorderControl(session), m_session(session), m_state(QMediaRecorder::StoppedState)
{
    connect(m_session, SIGNAL(stateChanged(QGstreamerCaptureSession::State)), SLOT(updateState()));
    connect(m_session, SIGNAL(error(int,QString)), SIGNAL(error(int,QString)));
    connect(m_session, SIGNAL(durationChanged(qint64)), SIGNAL(durationChanged(qint64)));
}

QGstreamerRecorderControl::~QGstreamerRecorderControl()
{
}

QUrl QGstreamerRecorderControl::outputLocation() const
{
    return m_session->outputLocation();
}

bool QGstreamerRecorderControl::setOutputLocation(const QUrl &sink)
{
    m_session->setOutputLocation(sink);
    return true;
}


QMediaRecorder::State QGstreamerRecorderControl::state() const
{
    switch ( m_session->state() ) {
        case QGstreamerCaptureSession::RecordingState:
            return QMediaRecorder::RecordingState;
        case QGstreamerCaptureSession::PausedState:
            return QMediaRecorder::PausedState;
        case QGstreamerCaptureSession::PreviewState:
        case QGstreamerCaptureSession::StoppedState:
            return QMediaRecorder::StoppedState;
    }

    return QMediaRecorder::StoppedState;

}

void QGstreamerRecorderControl::updateState()
{
    QMediaRecorder::State newState = state();
    if (m_state != newState) {
        m_state = newState;
        emit stateChanged(m_state);
    }
}

qint64 QGstreamerRecorderControl::duration() const
{
    return m_session->duration();
}

void QGstreamerRecorderControl::record()
{
    m_session->dumpGraph("before-record");
    if (m_session->state() != QGstreamerCaptureSession::StoppedState)
        m_session->setState(QGstreamerCaptureSession::RecordingState);
    else
        emit error(QMediaRecorder::ResourceError, tr("Service has not been started"));

    m_session->dumpGraph("after-record");
}

void QGstreamerRecorderControl::pause()
{
    m_session->dumpGraph("before-pause");
    if (m_session->state() != QGstreamerCaptureSession::StoppedState)
        m_session->setState(QGstreamerCaptureSession::PausedState);
    else
        emit error(QMediaRecorder::ResourceError, tr("Service has not been started"));
}

void QGstreamerRecorderControl::stop()
{
    if (m_session->state() != QGstreamerCaptureSession::StoppedState)
        m_session->setState(QGstreamerCaptureSession::PreviewState);
    else
        emit error(QMediaRecorder::ResourceError, tr("Service has not been started"));
}