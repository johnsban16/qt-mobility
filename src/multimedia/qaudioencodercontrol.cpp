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

#include <qaudioencodercontrol.h>
#include <QtCore/qstringlist.h>


/*!
    \class QAudioEncoderControl
    \ingroup multimedia
    \ingroup multimedia-serv

    \preliminary
    
    \brief The QAudioEncoderControl class provides access to the settings of a media service that
    performs audio encoding.

    If a QMediaService supports encoding audio data it will implement QAudioEncoderControl.  This
    control provides information about the limits of restricted audio encoder options and allows
    the selection of a set of audio encoder settings as specificed in a QAudioEncoderSettings
    object.

    The functionality provided by this control is exposed to application code through the
    QMediaRecorder class.

    The interface name of QAudioEncoderControl is \c com.nokia.Qt.QAudioEncoderControl/1.0 as
    defined in QAudioEncoderControl_iid.

    \sa QMediaService::control(), QMediaRecorder
*/

/*!
    \macro QAudioEncoderControl_iid

    \c com.nokia.Qt.AudioEncoderControl/1.0

    Defines the interface name of the QAudioEncoderControl class.

    \relates QAudioEncoderControl
*/

/*!
  Create a new audio encode control object with the given \a parent.
*/
QAudioEncoderControl::QAudioEncoderControl(QObject *parent)
    :QMediaControl(parent)
{
}

/*!
  Destroys the audio encode control.
*/
QAudioEncoderControl::~QAudioEncoderControl()
{
}

/*!
  \fn QAudioEncoderControl::supportedAudioCodecs() const

  Returns the list of supported audio codec names.
*/

/*!
  \fn QAudioEncoderControl::codecDescription(const QString &codec) const

  Returns description of audio \a codec.
*/

/*!
  \fn QAudioEncoderControl::supportedSampleRates() const

  Returns the list of supported audio sample rates, if known.
*/

/*!
    \fn QAudioEncoderControl::supportedEncodingOptions(const QString &codec) const

    Returns the list of \a codec specific audio encoding options.
*/

/*!
    \fn QAudioEncoderControl::encodingOption(const QString &codec, const QString &option) const

    Returns the value of audio encoding \a option for \a codec.
*/

/*!
    \fn QAudioEncoderControl::setEncodingOption(const QString &codec, const QString &option, const QVariant &value)

    Set the \a codec specific \a option to \a value.
*/

/*!
    \fn QAudioEncoderControl::audioSettings() const

    Returns the selected audio settings.
*/

/*!
    \fn QAudioEncoderControl::setAudioSettings(const QAudioEncoderSettings &settings)

    Sets the selected audio \a settings.
*/