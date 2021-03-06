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

#include "qgeotiledmaptextobjectinfo_p.h"

#include "qgeotiledmapdata.h"
#include "qgeotiledmapdata_p.h"

#include "qgeomaptextobject.h"

#include <QFontMetrics>

QTM_BEGIN_NAMESPACE

QGeoTiledMapTextObjectInfo::QGeoTiledMapTextObjectInfo(QGeoTiledMapData *mapData, QGeoMapObject *mapObject)
    : QGeoTiledMapObjectInfo(mapData, mapObject)
{
    text = static_cast<QGeoMapTextObject*>(mapObject);

    connect(text,
            SIGNAL(textChanged(QString)),
            this,
            SLOT(textChanged(QString)));
    connect(text,
            SIGNAL(fontChanged(QFont)),
            this,
            SLOT(fontChanged(QFont)));
    connect(text,
            SIGNAL(penChanged(QPen)),
            this,
            SLOT(penChanged(QPen)));
    connect(text,
            SIGNAL(brushChanged(QBrush)),
            this,
            SLOT(brushChanged(QBrush)));
    connect(text,
            SIGNAL(offsetChanged(QPoint)),
            this,
            SLOT(offsetChanged(QPoint)));
    connect(text,
            SIGNAL(alignmentChanged(Qt::Alignment)),
            this,
            SLOT(alignmentChanged(Qt::Alignment)));

    textItem = new QGraphicsSimpleTextItem();
    graphicsItem = textItem;

    penChanged(text->pen());
    brushChanged(text->brush());
    originChanged(text->origin());
    fontChanged(text->font());
    textChanged(text->text());
}

QGeoTiledMapTextObjectInfo::~QGeoTiledMapTextObjectInfo() {}

void QGeoTiledMapTextObjectInfo::textChanged(const QString &/*text*/)
{
    textItem->setText(text->text());
    doAlignment();
    updateItem();
}

void QGeoTiledMapTextObjectInfo::fontChanged(const QFont &/*font*/)
{
    textItem->setFont(text->font());
    doAlignment();
    updateItem();
}

void QGeoTiledMapTextObjectInfo::offsetChanged(const QPoint &/*offset*/)
{
    doAlignment();
    updateItem();
}

void QGeoTiledMapTextObjectInfo::alignmentChanged(Qt::Alignment /*alignment*/)
{
    doAlignment();
    updateItem();
}

void QGeoTiledMapTextObjectInfo::penChanged(const QPen &/*pen*/)
{
    textItem->setPen(text->pen());
    doAlignment();
    updateItem();
}

void QGeoTiledMapTextObjectInfo::brushChanged(const QBrush &/*brush*/)
{
    if (textItem) {
        textItem->setBrush(text->brush());
        doAlignment();
        updateItem();
    }
}

void QGeoTiledMapTextObjectInfo::doAlignment()
{
    Qt::Alignment align = text->alignment();
    QTransform trans;
    textItem->setTransform(trans);

    QRectF rect = textItem->boundingRect();
    QPointF center = rect.center();

    if (align & Qt::AlignVCenter) {
        trans.translate(0, -1 * center.y());
    } else if (align & Qt::AlignTop) {
        trans.translate(0, -1 * rect.top());
    } else if (align & Qt::AlignBottom) {
        trans.translate(0, -1 * rect.bottom());
    }
    if (align & Qt::AlignHCenter) {
        trans.translate(-1 * center.x(), 0);
    } else if (align & Qt::AlignLeft) {
        trans.translate(-1 * rect.left(), 0);
    } else if (align & Qt::AlignRight) {
        trans.translate(-1 * rect.right(), 0);
    }

    QPoint offset = text->offset();
    trans.translate(offset.x(), offset.y());
    textItem->setTransform(trans);
}

#include "moc_qgeotiledmaptextobjectinfo_p.cpp"

QTM_END_NAMESPACE

