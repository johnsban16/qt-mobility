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

#ifndef QDECLARATIVEGEOMAPTEXTOBJECT_H
#define QDECLARATIVEGEOMAPTEXTOBJECT_H

#include "qdeclarativegeomapobject_p.h"
#include "qdeclarativecoordinate_p.h"
#include "qgeomaptextobject.h"

#include <QColor>

QTM_BEGIN_NAMESPACE

class QDeclarativeGeoMapTextObject : public QDeclarativeGeoMapObject
{
    Q_OBJECT
    Q_ENUMS(HorizontalAlignment)
    Q_ENUMS(VerticalAlignment)

    Q_PROPERTY(QDeclarativeCoordinate* coordinate READ coordinate WRITE setCoordinate NOTIFY coordinateChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QPoint offset READ offset WRITE setOffset NOTIFY offsetChanged)
    Q_PROPERTY(HorizontalAlignment horizontalAlignment READ horizontalAlignment WRITE setHorizontalAlignment NOTIFY horizontalAlignmentChanged)
    Q_PROPERTY(VerticalAlignment verticalAlignment READ verticalAlignment WRITE setVerticalAlignment NOTIFY verticalAlignmentChanged)

public:
    enum HorizontalAlignment {
        AlignHCenter = Qt::AlignHCenter,
        AlignLeft = Qt::AlignLeft,
        AlignRight = Qt::AlignRight
    };

    enum VerticalAlignment {
        AlignVCenter = Qt::AlignVCenter,
        AlignTop = Qt::AlignTop,
        AlignBottom = Qt::AlignBottom
    };

    QDeclarativeGeoMapTextObject(QDeclarativeItem *parent = 0);
    ~QDeclarativeGeoMapTextObject();

    QDeclarativeCoordinate* coordinate();
    void setCoordinate(QDeclarativeCoordinate *coordinate);

    QString text() const;
    void setText(const QString &text);

    QFont font() const;
    void setFont(const QFont &font);

    QColor color() const;
    void setColor(const QColor &color);

    QPoint offset() const;
    void setOffset(const QPoint &offset);

    HorizontalAlignment horizontalAlignment() const;
    void setHorizontalAlignment(HorizontalAlignment alignment);

    VerticalAlignment verticalAlignment() const;
    void setVerticalAlignment(VerticalAlignment alignment);

Q_SIGNALS:
    void coordinateChanged(const QDeclarativeCoordinate *coordinate);
    void textChanged(const QString &text);
    void fontChanged(const QFont &font);
    void colorChanged(const QColor &color);
    void offsetChanged(const QPoint &offset);
    void horizontalAlignmentChanged(HorizontalAlignment alignment);
    void verticalAlignmentChanged(VerticalAlignment alignment);

private Q_SLOTS:
    void coordinateLatitudeChanged(double latitude);
    void coordinateLongitudeChanged(double longitude);
    void coordinateAltitudeChanged(double altitude);

private:
    QGeoMapTextObject* text_;
    QDeclarativeCoordinate *coordinate_;
    QColor color_;
    HorizontalAlignment hAlignment_;
    VerticalAlignment vAlignment_;
};

QTM_END_NAMESPACE

QML_DECLARE_TYPE(QTM_PREPEND_NAMESPACE(QDeclarativeGeoMapTextObject));

#endif
