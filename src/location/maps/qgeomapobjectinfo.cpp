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

#include "qgeomapobjectinfo.h"
#include "qgeomapobjectinfo_p.h"

#include "qgeomapdata.h"
#include "qgeomapdata_p.h"
#include "qgeomapobject.h"
#include "qgeomapobject_p.h"
#include "qgeoboundingbox.h"

QTM_BEGIN_NAMESPACE

/*!
    \class QGeoMapObjectInfo
    \brief The QGeoMapObjectInfo class is the base class used to define the
    parts of QGeoMapObject and its subclasses that are specific to a
    particular QGeoMapData subclass.

    \inmodule QtLocation
    \since 1.1

    \ingroup maps-impl

    Most of the mapping functionality is provided by a QGeoMapData subclass,
    including the rendering of the map itself.

    This means that QGeoMapData subclasses need to be able to render each of
    the QGeoMapObject instances and instances of the QGeoMapObject subclasses.

    Furthermore, the need to be able to create and manipulate map objects
    independently from the QGeoMapData instance precludes the use of a set of
    factory methods for creating QGeoMapData specific map objects.

    The QGeoMapObjectInfo class is used to provide the QGeoMapData subclass
    specific behaviours for the map objects in a way which fulfils this need,
    as the QGeoMapObjectInfo instances are only created at the point when a
    map object becomes associated with a QGeoMapData subclass - which is most
    commonly when the object is added to a QGraphicsGeoMap.
*/

/*!
    Constructs a new object info instance which will provide the behaviours of
    \a mapObject which are specific to \a mapData.
*/
QGeoMapObjectInfo::QGeoMapObjectInfo(QGeoMapData *mapData, QGeoMapObject *mapObject)
    : QObject(mapObject),
      d_ptr(new QGeoMapObjectInfoPrivate(mapData, mapObject)) {}

/*!
    Destroys this info object.
*/
QGeoMapObjectInfo::~QGeoMapObjectInfo()
{
    delete d_ptr;
}

/*!
    This function is run after the constructor.

    The default implementation does nothing.
    \since 1.1
*/
void QGeoMapObjectInfo::init() {}

/*!
    This function is called when the window size of the map changes to
    \a windowSize.

    The default implementation does nothing.
    \since 1.1
*/
void QGeoMapObjectInfo::windowSizeChanged(const QSizeF &windowSize)
{
    Q_UNUSED(windowSize)
}

/*!
    This function is called when the zoom level of the map changes to
    \a zoomLevel.

    The default implementation does nothing.
    \since 1.1
*/
void QGeoMapObjectInfo::zoomLevelChanged(qreal zoomLevel)
{
    Q_UNUSED(zoomLevel)
}

/*!
    This function is called when the center of the map changes to
    \a coordinate.

    The default implementation does nothing.
    \since 1.1
*/
void QGeoMapObjectInfo::centerChanged(const QGeoCoordinate &coordinate)
{
    Q_UNUSED(coordinate)
}

/*!
    This function is run when the z value of the object changes to \a zValue.

    The default implementation does nothing.
    \since 1.1
*/
void QGeoMapObjectInfo::zValueChanged(int zValue)
{
    Q_UNUSED(zValue)
}

/*!
    This function is run when the visible state of the object changes to
    \a visible.

    The default implementation does nothing.
    \since 1.1
*/
void QGeoMapObjectInfo::visibleChanged(bool visible)
{
    Q_UNUSED(visible)
}

/*!
    This function is run when the selected state of the object changes to
    \a selected.

    The default implementation does nothing.
    \since 1.1
*/
void QGeoMapObjectInfo::selectedChanged(bool selected)
{
    Q_UNUSED(selected)
}

/*!
    This function is run when the origin of the object changes to
    \a origin.

    The default implementation does nothing.
    \since 1.2
*/
void QGeoMapObjectInfo::originChanged(const QGeoCoordinate &origin)
{
    Q_UNUSED(origin);
}

/*!
    This function is run when the coordinate units of the object changes to
    \a units.

    The default implementation does nothing.
    \since 1.2
*/
void QGeoMapObjectInfo::unitsChanged(QGeoMapObject::CoordinateUnit units)
{
    Q_UNUSED(units);
}

/*!
    This function is run when the transform type of the object changes to
    \a transformType.

    The default implementation does nothing.
    \since 1.2
*/
void QGeoMapObjectInfo::transformTypeChanged(QGeoMapObject::TransformType transformType)
{
    Q_UNUSED(transformType);
}

/*!
    Returns a bounding box which contains this map object.

    The default implementation returns an invalid bounding box.
    \since 1.1
*/
QGeoBoundingBox QGeoMapObjectInfo::boundingBox() const
{
    return QGeoBoundingBox();
}

/*!
    Returns whether \a coordinate is contained with the boundary of this
    map object.

    The default implementation returns false.
    \since 1.1
*/
bool QGeoMapObjectInfo::contains(const QGeoCoordinate &coordinate) const
{
    Q_UNUSED(coordinate)
    return false;
}

/*!
    Returns the QGeoMapData instance associated with this info object.
    \since 1.1
*/
QGeoMapData* QGeoMapObjectInfo::mapData()
{
    return d_ptr->mapData;
}

// Need to keep this for BC, otherwise would probably replace with const
// version
/*!
    Returns the QGeoMapObject instance associated with this info object.
    \since 1.1
*/
QGeoMapObject* QGeoMapObjectInfo::mapObject()
{
    return d_ptr->mapObject;
}

/*!
    Returns the QGeoMapObject instance associated with this info object.
    \since 1.2
*/
QGeoMapObject* QGeoMapObjectInfo::mapObject() const
{
    return d_ptr->mapObject;
}

/*******************************************************************************
*******************************************************************************/

QGeoMapObjectInfoPrivate::QGeoMapObjectInfoPrivate(QGeoMapData *mapData, QGeoMapObject *mapObject)
    : mapData(mapData),
      mapObject(mapObject) {}

QGeoMapObjectInfoPrivate::~QGeoMapObjectInfoPrivate() {}

/*******************************************************************************
*******************************************************************************/

#include "moc_qgeomapobjectinfo.cpp"

QTM_END_NAMESPACE
