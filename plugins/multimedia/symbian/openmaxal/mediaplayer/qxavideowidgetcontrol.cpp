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

#include "qxavideowidgetcontrol.h"
#include "qxacommon.h"
#include "qxawidget.h"
#include <QEvent>

QXAVideoWidgetControl::QXAVideoWidgetControl(QXAPlaySession *session, QObject *parent)
    : QVideoWidgetControl(parent), mSession(session)
{
    QT_TRACE_FUNCTION_ENTRY;
    mWidget = new QXAWidget;
    if (mWidget)
        mWidget->installEventFilter(this);
    QT_TRACE_FUNCTION_EXIT;
}

QXAVideoWidgetControl::~QXAVideoWidgetControl()
{
    QT_TRACE_FUNCTION_ENTRY;
    delete mWidget;
    QT_TRACE_FUNCTION_EXIT;
}

QWidget* QXAVideoWidgetControl::videoWidget()
{
    QT_TRACE_FUNCTION_ENTRY_EXIT;
    return mWidget;
}

Qt::AspectRatioMode QXAVideoWidgetControl::aspectRatioMode() const
{
    QT_TRACE_FUNCTION_ENTRY;
    RET_s_IF_p_IS_NULL(mSession, Qt::IgnoreAspectRatio);
    QT_TRACE_FUNCTION_EXIT;
    return mSession->getAspectRatioMode();
}

void QXAVideoWidgetControl::setAspectRatioMode(Qt::AspectRatioMode mode)
{
    QT_TRACE_FUNCTION_ENTRY;
    RET_IF_p_IS_NULL(mSession);
    mSession->setAspectRatioMode(mode);
    QT_TRACE_FUNCTION_EXIT;
}

bool QXAVideoWidgetControl::isFullScreen() const
{
    QT_TRACE_FUNCTION_ENTRY;
    bool retVal = false;
    RET_s_IF_p_IS_NULL(mWidget, retVal);
    retVal = mWidget->isFullScreen();
    QT_TRACE_FUNCTION_EXIT;
    return retVal;
}

void QXAVideoWidgetControl::setFullScreen(bool fullScreen)
{
    QT_TRACE_FUNCTION_ENTRY;
    RET_IF_p_IS_NULL(mWidget);
    if (fullScreen == mWidget->isFullScreen())
        return;
    else if (fullScreen)
        mWidget->showFullScreen();
    else
        mWidget->showNormal();
    
    emit fullScreenChanged(fullScreen);
    
    QT_TRACE_FUNCTION_EXIT;
}

int QXAVideoWidgetControl::brightness() const
{
    QT_TRACE_FUNCTION_ENTRY_EXIT;
    return 0;
}

void QXAVideoWidgetControl::setBrightness(int brightness)
{
    QT_TRACE_FUNCTION_ENTRY_EXIT;
    Q_UNUSED(brightness);
}

int QXAVideoWidgetControl::contrast() const
{
    QT_TRACE_FUNCTION_ENTRY_EXIT;
    return 0;
}

void QXAVideoWidgetControl::setContrast(int contrast)
{
    QT_TRACE_FUNCTION_ENTRY_EXIT;
    Q_UNUSED(contrast);
}

int QXAVideoWidgetControl::hue() const
{
    QT_TRACE_FUNCTION_ENTRY_EXIT;
    return 0;
}

void QXAVideoWidgetControl::setHue(int hue)
{
    QT_TRACE_FUNCTION_ENTRY_EXIT;
    Q_UNUSED(hue);
}

int QXAVideoWidgetControl::saturation() const
{
    QT_TRACE_FUNCTION_ENTRY_EXIT;
    return 0;
}

void QXAVideoWidgetControl::setSaturation(int saturation)
{
    QT_TRACE_FUNCTION_ENTRY_EXIT;
    Q_UNUSED(saturation);
}

bool QXAVideoWidgetControl::eventFilter(QObject *object, QEvent *event)
{
    if (object == mWidget) {
        if (   event->type() == QEvent::Resize 
            || event->type() == QEvent::Move 
            || event->type() == QEvent::WinIdChange
            || event->type() == QEvent::ParentChange 
            || event->type() == QEvent::Show) {
        emit widgetUpdated();
        }
    }    
    return false;
}

WId QXAVideoWidgetControl::videoWidgetWId()
{
    if (mWidget->internalWinId())
        return mWidget->internalWinId();
    else if (mWidget->effectiveWinId())
        return mWidget->effectiveWinId();

    return NULL;
}
