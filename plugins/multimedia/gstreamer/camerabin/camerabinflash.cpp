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

#include "camerabinflash.h"
#include "camerabinsession.h"
#include <gst/interfaces/photography.h>

#include <QDebug>

CameraBinFlash::CameraBinFlash(CameraBinSession *session)
    :QCameraFlashControl(session),
     m_session(session)
{
}

CameraBinFlash::~CameraBinFlash()
{
}

QCameraExposure::FlashModes CameraBinFlash::flashMode() const
{
    GstFlashMode flashMode;
    gst_photography_get_flash_mode(m_session->photography(), &flashMode);

    QCameraExposure::FlashModes modes;
    switch (flashMode) {
    case GST_PHOTOGRAPHY_FLASH_MODE_AUTO: modes |= QCameraExposure::FlashAuto; break;
    case GST_PHOTOGRAPHY_FLASH_MODE_OFF: modes |= QCameraExposure::FlashOff; break;
    case GST_PHOTOGRAPHY_FLASH_MODE_ON: modes |= QCameraExposure::FlashOn; break;
    case GST_PHOTOGRAPHY_FLASH_MODE_FILL_IN: modes |= QCameraExposure::FlashFill; break;
    case GST_PHOTOGRAPHY_FLASH_MODE_RED_EYE: modes |= QCameraExposure::FlashRedEyeReduction; break;
    default:
        modes |= QCameraExposure::FlashAuto;
        break;
    }

#ifdef Q_WS_MAEMO_6
    gboolean torchEnabled = false;
    g_object_get(G_OBJECT(m_session->cameraSourceElement()), "video-torch", &torchEnabled, NULL);
    if (torchEnabled)
        modes |= QCameraExposure::FlashTorch;
#endif

    return modes;
}

void CameraBinFlash::setFlashMode(QCameraExposure::FlashModes mode)
{
    GstFlashMode flashMode;
    gst_photography_get_flash_mode(m_session->photography(), &flashMode);

    if (mode.testFlag(QCameraExposure::FlashAuto)) flashMode = GST_PHOTOGRAPHY_FLASH_MODE_AUTO;
    else if (mode.testFlag(QCameraExposure::FlashOff)) flashMode = GST_PHOTOGRAPHY_FLASH_MODE_OFF;
    else if (mode.testFlag(QCameraExposure::FlashOn)) flashMode = GST_PHOTOGRAPHY_FLASH_MODE_ON;
    else if (mode.testFlag(QCameraExposure::FlashFill)) flashMode = GST_PHOTOGRAPHY_FLASH_MODE_FILL_IN;
    else if (mode.testFlag(QCameraExposure::FlashRedEyeReduction)) flashMode = GST_PHOTOGRAPHY_FLASH_MODE_RED_EYE;

    gst_photography_set_flash_mode(m_session->photography(), flashMode);

#ifdef Q_WS_MAEMO_6
    gboolean torchEnabled = false;
    g_object_get(G_OBJECT(m_session->cameraSourceElement()), "video-torch", &torchEnabled, NULL);

    gboolean enableTorch = mode.testFlag(QCameraExposure::FlashTorch);

    if (bool(enableTorch) != bool(torchEnabled)) {
        g_object_set(G_OBJECT(m_session->cameraSourceElement()), "video-torch", enableTorch, NULL);

        //it's necessary to restart source element to toggle torch
        if (m_session->captureMode() == QCamera::CaptureVideo)
            emit torchModeChanged(bool(torchEnabled));
    }
#endif
}

bool CameraBinFlash::isFlashModeSupported(QCameraExposure::FlashModes mode) const
{

#ifdef Q_WS_MAEMO_6
    //torch light is allowed only in video capture mode
    if (m_session->captureMode() == QCamera::CaptureVideo) {
        if (mode == QCameraExposure::FlashTorch ||
            mode == QCameraExposure::FlashTorch | QCameraExposure::FlashOff)
            return true;
    }
#endif

    return  mode == QCameraExposure::FlashOff ||
            mode == QCameraExposure::FlashOn ||
            mode == QCameraExposure::FlashAuto ||
            mode == QCameraExposure::FlashRedEyeReduction ||
            mode == QCameraExposure::FlashFill;
}

bool CameraBinFlash::isFlashReady() const
{
    return true;
}

