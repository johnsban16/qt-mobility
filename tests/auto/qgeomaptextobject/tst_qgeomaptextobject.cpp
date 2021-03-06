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

#include "testhelper.h"
#include <QtTest/QtTest>
#include "qgeomaptextobject.h"
#include "qgeocoordinate.h"
#include "qgraphicsgeomap.h"
#include "qgeoboundingbox.h"

QTM_USE_NAMESPACE

Q_DECLARE_METATYPE(Qt::Alignment)
Q_DECLARE_METATYPE(Qt::AlignmentFlag)
Q_DECLARE_METATYPE(QGeoCoordinate)
Q_DECLARE_METATYPE(QBrush)
Q_DECLARE_METATYPE(QPoint)

class tst_QGeoMapTextObject: public QObject
{
Q_OBJECT

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void qgeomaptextobject_data();
    void qgeomaptextobject();

    void alignment_data();
    void alignment();
    void brush_data();
    void brush();
    void coordinate_data();
    void coordinate();
    void geometry_data();
    void geometry();
    void offset_data();
    void offset();
    void pen_data();
    void pen();
    void text_data();
    void text();
    void zvalue_data();
    void zvalue();
    void boundingBox();
    void contains_data();
    void contains();
    void isSelected();
    void isVisible();

private:
    TestHelper *m_helper;
};

// This will be called before the first test function is executed.
// It is only called once.
void tst_QGeoMapTextObject::initTestCase()
{
    qRegisterMetaType<QGeoCoordinate> ();
    qRegisterMetaType<Qt::Alignment> ();
}

// This will be called after the last test function is executed.
// It is only called once.
void tst_QGeoMapTextObject::cleanupTestCase()
{
}

// This will be called before each test function is executed.
void tst_QGeoMapTextObject::init()
{
    m_helper = new TestHelper();
    QGraphicsGeoMap* map = m_helper->map();

    if (!map)
        QFAIL("Could not create map!");
}

// This will be called after every test function.
void tst_QGeoMapTextObject::cleanup()
{
    delete (m_helper);
    m_helper = 0;
}

void tst_QGeoMapTextObject::qgeomaptextobject_data()
{
}

void tst_QGeoMapTextObject::qgeomaptextobject()
{
    QGeoMapTextObject* object = new QGeoMapTextObject();

    QCOMPARE(object->type(), QGeoMapObject::TextType);

    QCOMPARE(object->alignment(), Qt::AlignCenter);
    QCOMPARE(object->brush(), QBrush());
    QCOMPARE(object->coordinate(), QGeoCoordinate());
    QCOMPARE(object->font(), QFont());
    QCOMPARE(object->offset(), QPoint());
    QPen pen(Qt::black);
    pen.setCosmetic(true);
    QCOMPARE(object->text(), QString());
    QCOMPARE(object->zValue(), 0);
    QCOMPARE(object->isSelected(),false);
    QCOMPARE(object->isVisible(),true);
    QCOMPARE(object->boundingBox(),QGeoBoundingBox());
    QCOMPARE(object->contains(QGeoCoordinate()),false);

    //check if can be added to map

    QGraphicsGeoMap* map = m_helper->map();

    map->addMapObject(object);

    QList<QGeoMapObject *> list = map->mapObjects();

    QVERIFY(list.at(0)==object);

    QVERIFY2(object->mapData(),"no map data set");

    map->removeMapObject(object);

    QVERIFY2(!object->mapData(),"no map data still set");

    delete (object);

}

void tst_QGeoMapTextObject::alignment_data()
{

    QTest::addColumn<Qt::AlignmentFlag>("alignment");
    QTest::newRow("AlignLeft") << Qt::AlignLeft;
    QTest::newRow("AlignRight") << Qt::AlignRight;
    QTest::newRow("AlignTop") << Qt::AlignTop;
    QTest::newRow("AlignBottom") << Qt::AlignBottom;

}

// public Qt::Alignment alignment() const
void tst_QGeoMapTextObject::alignment()
{
    QFETCH(Qt::AlignmentFlag, alignment);

    QGeoCoordinate center(50, 50, 0);

    QGeoMapTextObject* object = new QGeoMapTextObject();

    object->setCoordinate(center);

    object->setText("AAAAA");

    QGraphicsGeoMap* map = m_helper->map();

    map->addMapObject(object);

    QList<QGeoMapObject *> list = map->mapObjects();

    QVERIFY(list.at(0)==object);

    QSignalSpy spy0(object, SIGNAL(alignmentChanged(Qt::Alignment)));
    QSignalSpy spy1(object, SIGNAL(brushChanged(QBrush const&)));
    QSignalSpy spy2(object, SIGNAL(coordinateChanged(QGeoCoordinate const&)));
    QSignalSpy spy3(object, SIGNAL(fontChanged(QFont const&)));
    QSignalSpy spy4(object, SIGNAL(offsetChanged(QPoint const&)));
    QSignalSpy spy5(object, SIGNAL(penChanged(QPen const&)));
    QSignalSpy spy6(object, SIGNAL(textChanged(QString const&)));

    //check if rectangle is not there

    map->setCenter(center);

    QFontMetrics metrics(object->font());

    QRect bounds = metrics.boundingRect(object->text());

    QPointF point = map->coordinateToScreenPosition(center);

    //check if text is there

    point = map->coordinateToScreenPosition(center);

    QPoint diff(bounds.width() - 1, bounds.height() - 1);

    if (alignment & Qt::AlignLeft) {
        diff.setY(0);
        point -= diff / 2;
    }
    else if (alignment & Qt::AlignRight) {
        diff.setY(0);
        point += diff / 2;
    }
    else if (alignment & Qt::AlignTop) {
        diff.setX(0);
        point -= diff / 2;
    }
    else if (alignment & Qt::AlignBottom) {
        diff.setX(0);
        point += diff / 2;
    }

    QCOMPARE(map->mapObjectsAtScreenPosition(point).size(),1);

    object->setAlignment(alignment);

    QCOMPARE(object->alignment(), alignment);

    QCOMPARE(map->mapObjectsAtScreenPosition(point).size(),0);

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);

}

void tst_QGeoMapTextObject::brush_data()
{

    QTest::addColumn<QBrush>("brush");
    QTest::newRow("white") << QBrush(Qt::white);
    QTest::newRow("blue") << QBrush(Qt::blue);

}

// public QBrush brush() const
void tst_QGeoMapTextObject::brush()
{
    QFETCH(QBrush, brush);

    QGeoCoordinate center(50, 50, 0);

    QGeoMapTextObject* object = new QGeoMapTextObject();

    object->setCoordinate(center);

    object->setText("AAAAA");

    QGraphicsGeoMap* map = m_helper->map();

    map->addMapObject(object);

    QList<QGeoMapObject *> list = map->mapObjects();

    QVERIFY(list.at(0)==object);

    QSignalSpy spy0(object, SIGNAL(alignmentChanged(Qt::Alignment)));
    QSignalSpy spy1(object, SIGNAL(brushChanged(QBrush const&)));
    QSignalSpy spy2(object, SIGNAL(coordinateChanged(QGeoCoordinate const&)));
    QSignalSpy spy3(object, SIGNAL(fontChanged(QFont const&)));
    QSignalSpy spy4(object, SIGNAL(offsetChanged(QPoint const&)));
    QSignalSpy spy5(object, SIGNAL(penChanged(QPen const&)));
    QSignalSpy spy6(object, SIGNAL(textChanged(QString const&)));

    object->setBrush(brush);

    QCOMPARE(object->brush(), brush);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);;
}

void tst_QGeoMapTextObject::coordinate_data()
{

    QTest::addColumn<QGeoCoordinate>("coordinate");
    QTest::newRow("52.5, 13.0, 0") << QGeoCoordinate(52.5, 13.0, 0);
    QTest::newRow("-52.5, 13.0, 0") << QGeoCoordinate(-52.5, 13.0, 0);
    QTest::newRow("52.5, -13.0, 0") << QGeoCoordinate(52.5, -13.0, 0);
    QTest::newRow("-52.5, -13.0, 0") << QGeoCoordinate(-52.5, -13.0, 0);

}

// public QGeoCoordinate coordinate() const
void tst_QGeoMapTextObject::coordinate()
{
    QFETCH(QGeoCoordinate, coordinate);

    QGeoCoordinate center(50, 50, 0);

    QGeoMapTextObject* object = new QGeoMapTextObject();

    object->setCoordinate(center);

    object->setText("AAAAA");

    QGraphicsGeoMap* map = m_helper->map();

    map->addMapObject(object);

    QList<QGeoMapObject *> list = map->mapObjects();

    QVERIFY(list.at(0)==object);

    QSignalSpy spy0(object, SIGNAL(alignmentChanged(Qt::Alignment)));
    QSignalSpy spy1(object, SIGNAL(brushChanged(QBrush const&)));
    QSignalSpy spy2(object, SIGNAL(coordinateChanged(QGeoCoordinate const&)));
    QSignalSpy spy3(object, SIGNAL(fontChanged(QFont const&)));
    QSignalSpy spy4(object, SIGNAL(offsetChanged(QPoint const&)));
    QSignalSpy spy5(object, SIGNAL(penChanged(QPen const&)));
    QSignalSpy spy6(object, SIGNAL(textChanged(QString const&)));

    //check if object is not there

    map->setCenter(coordinate);

    QPointF point = map->coordinateToScreenPosition(coordinate);

    QCOMPARE(map->mapObjectsAtScreenPosition(point).size(),0);

    object->setCoordinate(coordinate);

    QCOMPARE(object->coordinate(), coordinate);

    //check if object is there

    QCOMPARE(map->mapObjectsAtScreenPosition(point).size(),1);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 1);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);

}

void tst_QGeoMapTextObject::geometry_data()
{
    QTest::addColumn<int>("size");
    QTest::addColumn<int>("offsetX");
    QTest::addColumn<int>("offsetY");

    QTest::newRow("5, -50,-50") << 5 << -50 << -50;
    QTest::newRow("5, -50,0") << 5 << -50 << 0;
    QTest::newRow("5, -50,50") << 5 << -50 << 50;
    QTest::newRow("5, 0,-50") << 5 << 0 << -50;
    QTest::newRow("5, 0,0") << 5 << 0 << 0;
    QTest::newRow("5, 0,50") << 5 << 0 << 50;
    QTest::newRow("5, 50,-50") << 5 << 50 << -50;
    QTest::newRow("5, 50,0") << 5 << 50 << 0;
    QTest::newRow("5, 50,50") << 5 << 50 << 50;

    QTest::newRow("15, -50,-50") << 15 << -50 << -50;
    QTest::newRow("15, -50,0") << 15 << -50 << 0;
    QTest::newRow("15, -50,50") << 15 << -50 << 50;
    QTest::newRow("15, 0,-50") << 15 << 0 << -50;
    QTest::newRow("15, 0,0") << 15 << 0 << 0;
    QTest::newRow("15, 0,50") << 15 << 0 << 50;
    QTest::newRow("15, 50,-50") << 15 << 50 << -50;
    QTest::newRow("15, 50,0") << 15 << 50 << 0;
    QTest::newRow("15, 50,50") << 15 << 50 << 50;
}

// public QFont font() const
void tst_QGeoMapTextObject::geometry()
{
    QFETCH(int, size);
    QFETCH(int, offsetX);
    QFETCH(int, offsetY);

    QFont font = QFont();
    font.setPointSize(size);
    QPoint offset(offsetX, offsetY);
    QGeoCoordinate center(50, 50, 0);

    QGeoMapTextObject* object = new QGeoMapTextObject();

    object->setCoordinate(center);
    object->setText("AAAAA");
    object->setBrush(Qt::black);
    object->setFont(font);
    object->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    object->setOffset(offset);

    QFontMetrics metrics(object->font());
    QRect bounds = metrics.boundingRect(object->text());

    int width = bounds.width();
    int height = bounds.height();

    QGraphicsGeoMap* map = m_helper->map();

    map->setCenter(center);

    map->addMapObject(object);

    QList<QGeoMapObject *> list = map->mapObjects();

    QVERIFY(list.at(0)==object);

    QPointF point = map->coordinateToScreenPosition(center);
    QPointF topLeft = point + offset;

    QRectF inner = QRectF(topLeft.x() + width / 4.0,
                         topLeft.y() + height / 4.0,
                         width / 2.0,
                         height / 2.0);

    QRectF innerTop = QRectF(topLeft.x(),
                             topLeft.y(),
                             width,
                             height / 4.0);
    QRectF innerBottom = QRectF(topLeft.x(),
                                topLeft.y() + 3.0 * height / 4.0,
                                width,
                                height / 4.0);
    QRectF innerLeft = QRectF(topLeft.x(),
                              topLeft.y() + height / 4.0,
                              width / 4.0,
                              height / 2.0);
    QRectF innerRight = QRectF(topLeft.x() + 3.0 * width / 4.0,
                               topLeft.y() + height / 4.0,
                               width / 4.0,
                               height / 2.0);

    QRectF outer = QRectF(topLeft.x() - width / 4.0,
                         topLeft.y() - height / 4.0,
                         3.0 * width / 2.0,
                         3.0 * height / 2.0);

    QRectF outerTop = QRectF(topLeft.x() - width / 4.0,
                             topLeft.y() - height / 4.0,
                             3.0 * width / 2.0,
                             height / 8.0);
    QRectF outerBottom = QRectF(topLeft.x() - width / 4.0,
                                topLeft.y() + 9.0 * height / 8.0,
                                3.0 * width / 2.0,
                                height / 8.0);
    QRectF outerLeft = QRectF(topLeft.x() - width / 4.0,
                              topLeft.y(),
                              width / 8.0,
                              height);
    QRectF outerRight = QRectF(topLeft.x() + 9.0 * width / 8.0,
                               topLeft.y(),
                               width / 8.0,
                               height);

    QCOMPARE(map->mapObjectsInScreenRect(inner).size(), 1);

    QCOMPARE(map->mapObjectsInScreenRect(innerTop).size(), 1);
    QCOMPARE(map->mapObjectsInScreenRect(innerBottom).size(), 1);
    QCOMPARE(map->mapObjectsInScreenRect(innerLeft).size(), 1);
    QCOMPARE(map->mapObjectsInScreenRect(innerRight).size(), 1);

    QCOMPARE(map->mapObjectsInScreenRect(outer).size(), 1);

    QCOMPARE(map->mapObjectsInScreenRect(outerTop).size(), 0);
    QCOMPARE(map->mapObjectsInScreenRect(outerBottom).size(), 0);
    QCOMPARE(map->mapObjectsInScreenRect(outerLeft).size(), 0);
    QCOMPARE(map->mapObjectsInScreenRect(outerRight).size(), 0);
}

void tst_QGeoMapTextObject::offset_data()
{

    QTest::addColumn<QPoint>("offset");
    QTest::newRow("10,10") << QPoint(10, 10);
    QTest::newRow("-10,10") << QPoint(-10, 10);
    QTest::newRow("10,-10") << QPoint(10, -10);
    QTest::newRow("-10,-10") << QPoint(-10, -10);

}

// public QPoint offset() const
void tst_QGeoMapTextObject::offset()
{
    QFETCH(QPoint, offset);

    QGeoCoordinate center(50, 50, 0);

    QGeoMapTextObject* object = new QGeoMapTextObject();

    object->setCoordinate(center);

    object->setText("AAAAA");

    QGraphicsGeoMap* map = m_helper->map();

    map->addMapObject(object);

    QList<QGeoMapObject *> list = map->mapObjects();

    QVERIFY(list.at(0)==object);

    QSignalSpy spy0(object, SIGNAL(alignmentChanged(Qt::Alignment)));
    QSignalSpy spy1(object, SIGNAL(brushChanged(QBrush const&)));
    QSignalSpy spy2(object, SIGNAL(coordinateChanged(QGeoCoordinate const&)));
    QSignalSpy spy3(object, SIGNAL(fontChanged(QFont const&)));
    QSignalSpy spy4(object, SIGNAL(offsetChanged(QPoint const&)));
    QSignalSpy spy5(object, SIGNAL(penChanged(QPen const&)));
    QSignalSpy spy6(object, SIGNAL(textChanged(QString const&)));

    map->setCenter(center);

    QPointF point = map->coordinateToScreenPosition(center);

    point += offset;

    QCOMPARE(map->mapObjectsAtScreenPosition(point).size(),0);

    object->setOffset(offset);

    QCOMPARE(object->offset(), offset);

    QCOMPARE(map->mapObjectsAtScreenPosition(point).size(),1);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 1);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);

}

Q_DECLARE_METATYPE(QPen)
void tst_QGeoMapTextObject::pen_data()
{
    QTest::addColumn<QPen>("pen");
    QTest::newRow("blue") << QPen(Qt::blue);
    QTest::newRow("white") << QPen(Qt::white);
}

// public QPen pen() const
void tst_QGeoMapTextObject::pen()
{
    QFETCH(QPen, pen);

    QGeoMapTextObject* object = new QGeoMapTextObject();

    QGraphicsGeoMap* map = m_helper->map();

    map->addMapObject(object);

    QList<QGeoMapObject *> list = map->mapObjects();

    QVERIFY(list.at(0)==object);

    QSignalSpy spy0(object, SIGNAL(alignmentChanged(Qt::Alignment)));
    QSignalSpy spy1(object, SIGNAL(brushChanged(QBrush const&)));
    QSignalSpy spy2(object, SIGNAL(coordinateChanged(QGeoCoordinate const&)));
    QSignalSpy spy3(object, SIGNAL(fontChanged(QFont const&)));
    QSignalSpy spy4(object, SIGNAL(offsetChanged(QPoint const&)));
    QSignalSpy spy5(object, SIGNAL(penChanged(QPen const&)));
    QSignalSpy spy6(object, SIGNAL(textChanged(QString const&)));

    object->setPen(pen);

    pen.setCosmetic(true);

    //according to specs it should be cosmetic
    QCOMPARE(object->pen(), pen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 1);
    QCOMPARE(spy6.count(), 0);

}

void tst_QGeoMapTextObject::text_data()
{
    QTest::addColumn<QString>("text");
    QTest::newRow("AAAAAAAAAA") << QString("AAAAAAAAAA");
    QTest::newRow("AAAAAAAAAAAAAA") << QString("AAAAAAAAAAAAAA");
    QTest::newRow("AAAAAAAAAAAAAAAAAAAAAA") << QString("AAAAAAAAAAAAAAAAAAAAAA");
}

// public QString text() const
void tst_QGeoMapTextObject::text()
{
    QFETCH(QString, text);

    QGeoCoordinate center(50, 50, 0);

    QGeoMapTextObject* object = new QGeoMapTextObject();

    object->setCoordinate(center);

    object->setText("AAA");

    object->setAlignment(Qt::AlignLeft);

    object->setBrush(Qt::black);

    QGraphicsGeoMap* map = m_helper->map();

    map->addMapObject(object);

    QList<QGeoMapObject *> list = map->mapObjects();

    QVERIFY(list.at(0)==object);

    QSignalSpy spy0(object, SIGNAL(alignmentChanged(Qt::Alignment)));
    QSignalSpy spy1(object, SIGNAL(brushChanged(QBrush const&)));
    QSignalSpy spy2(object, SIGNAL(coordinateChanged(QGeoCoordinate const&)));
    QSignalSpy spy3(object, SIGNAL(fontChanged(QFont const&)));
    QSignalSpy spy4(object, SIGNAL(offsetChanged(QPoint const&)));
    QSignalSpy spy5(object, SIGNAL(penChanged(QPen const&)));
    QSignalSpy spy6(object, SIGNAL(textChanged(QString const&)));

    map->setCenter(center);

    QFontMetrics metrics(object->font());

    QRect bounds = metrics.boundingRect(object->text());

    QPointF point = map->coordinateToScreenPosition(center);

    QPoint diff(bounds.width() * 3 / 2, bounds.height() / 2);

    point += diff;

    QCOMPARE(map->mapObjectsAtScreenPosition(point).size(),0);

    object->setText(text);

    QCOMPARE(object->text(), text);

    QCOMPARE(map->mapObjectsAtScreenPosition(point).size(),1);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 1);

}


void tst_QGeoMapTextObject::zvalue_data()
{
    QTest::addColumn<int>("zValue1");
    QTest::addColumn<int>("zValue2");
    QTest::addColumn<int>("zValue3");
    QTest::newRow("1,2,3") << 1 << 2 << 3;
    QTest::newRow("3,2,1") << 3 << 2 << 1;
    QTest::newRow("2,1,3") << 2 << 1 << 3;
}

// public int zValue() const
void tst_QGeoMapTextObject::zvalue()
{

    QFETCH(int, zValue1);
    QFETCH(int, zValue2);
    QFETCH(int, zValue3);

    QGeoCoordinate center(1.0, 1.0, 0);

    QGeoMapTextObject* object1 = new QGeoMapTextObject(center, "AAAAAA");
    QGeoMapTextObject* object2 = new QGeoMapTextObject(center, "AAAAAA");
    QGeoMapTextObject* object3 = new QGeoMapTextObject(center, "AAAAAA");

    QGraphicsGeoMap* map = m_helper->map();

    map->addMapObject(object1);
    map->addMapObject(object2);
    map->addMapObject(object3);

    QList<QGeoMapObject *> list = map->mapObjects();

    QCOMPARE(list.count(),3);

    QVERIFY(list.at(0)==object1);
    QVERIFY(list.at(1)==object2);
    QVERIFY(list.at(2)==object3);

    QSignalSpy spy0(object1, SIGNAL(selectedChanged(bool)));
    QSignalSpy spy1(object1, SIGNAL(visibleChanged(bool)));
    QSignalSpy spy2(object1, SIGNAL(zValueChanged(int)));

    map->setCenter(center);

    QPointF point = map->coordinateToScreenPosition(center);

    QCOMPARE(map->mapObjectsAtScreenPosition(point).size(),3);

    QVERIFY(map->mapObjectsAtScreenPosition(point).at(0)==object1);
    QVERIFY(map->mapObjectsAtScreenPosition(point).at(1)==object2);
    QVERIFY(map->mapObjectsAtScreenPosition(point).at(2)==object3);

    object1->setZValue(zValue1);
    object2->setZValue(zValue2);
    object3->setZValue(zValue3);

    QCOMPARE(object1->zValue(), zValue1);
    QCOMPARE(object2->zValue(), zValue2);
    QCOMPARE(object3->zValue(), zValue3);
    //check if object is there

    QCOMPARE(map->mapObjectsAtScreenPosition(point).size(),3);

    QVERIFY(map->mapObjectsAtScreenPosition(point).at(zValue1-1)==object1);
    QVERIFY(map->mapObjectsAtScreenPosition(point).at(zValue2-1)==object2);
    QVERIFY(map->mapObjectsAtScreenPosition(point).at(zValue3-1)==object3);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 1);

}

// public bool isVisible() const
void tst_QGeoMapTextObject::isVisible()
{

    QGeoCoordinate center(1.0, 1.0, 0);

    QGeoMapTextObject* object = new QGeoMapTextObject(center, "AAAAAA");

    QGraphicsGeoMap* map = m_helper->map();

    map->addMapObject(object);

    QList<QGeoMapObject *> list = map->mapObjects();

    QVERIFY(list.at(0)==object);

    QSignalSpy spy0(object, SIGNAL(selectedChanged(bool)));
    QSignalSpy spy1(object, SIGNAL(visibleChanged(bool)));
    QSignalSpy spy2(object, SIGNAL(zValueChanged(int)));

    map->setCenter(center);

    QPointF point = map->coordinateToScreenPosition(center);

    QCOMPARE(map->mapObjectsAtScreenPosition(point).size(),1);

    object->setVisible(false);

    QCOMPARE(object->isVisible(), false);

    QCOMPARE(map->mapObjectsAtScreenPosition(point).size(),0);

    object->setVisible(true);

    QCOMPARE(object->isVisible(), true);

    QCOMPARE(map->mapObjectsAtScreenPosition(point).size(),1);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 2);
    QCOMPARE(spy2.count(), 0);

}

// public bool isSelected() const
void tst_QGeoMapTextObject::isSelected()
{
#if 0

    QSignalSpy spy0(object, SIGNAL(selectedChanged(bool)));
    QSignalSpy spy1(object, SIGNAL(visibleChanged(bool)));
    QSignalSpy spy2(object, SIGNAL(zValueChanged(int)));

    QCOMPARE(object->isSelected(), isSelected);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
#endif
    QSKIP("Test is not implemented.", SkipAll);
}

void tst_QGeoMapTextObject::contains_data()
{

    QTest::addColumn<QGeoCoordinate>("coordinate");
    QTest::newRow("5,5") << QGeoCoordinate(5, 5, 0);
    QTest::newRow("1,1") << QGeoCoordinate(1, 1, 0);
    QTest::newRow("0,0") << QGeoCoordinate(0, 0, 0);

}

// public bool contains(QGeoCoordinate const& coordinate) const
void tst_QGeoMapTextObject::contains()
{
    QFETCH(QGeoCoordinate, coordinate);

    QGeoCoordinate center(0, 0, 0);

    QGeoMapTextObject* object = new QGeoMapTextObject(center, "AAAAAA");

    QGraphicsGeoMap* map = m_helper->map();

    map->addMapObject(object);

    QList<QGeoMapObject *> list = map->mapObjects();

    QVERIFY(list.at(0)==object);

    QSignalSpy spy0(object, SIGNAL(selectedChanged(bool)));
    QSignalSpy spy1(object, SIGNAL(visibleChanged(bool)));
    QSignalSpy spy2(object, SIGNAL(zValueChanged(int)));

    map->setCenter(coordinate);

    QPointF point = map->coordinateToScreenPosition(coordinate);

    bool contains = map->mapObjectsAtScreenPosition(point).size() == 1;

    QCOMPARE(object->contains(coordinate), contains);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);

}

// public QGeoBoundingBox boundingBox() const
void tst_QGeoMapTextObject::boundingBox()
{
    QGeoCoordinate center(0, 0, 0);

    QGeoMapTextObject* object = new QGeoMapTextObject(center,"AAAAAA");

    QVERIFY2(object->boundingBox().width()!=0,"no bounding box");
    QVERIFY2(object->boundingBox().height()!=0,"no bounding box");

    QGraphicsGeoMap* map = m_helper->map();

    map->addMapObject(object);

    QList<QGeoMapObject *> list = map->mapObjects();

    QVERIFY(list.at(0)==object);

    QVERIFY2(object->boundingBox().width()!=0,"no bounding box");
    QVERIFY2(object->boundingBox().height()!=0,"no bounding box");

    double width = object->boundingBox().width();
    double height = object->boundingBox().height();

    double top = object->boundingBox().topLeft().latitude();
    double bottom = object->boundingBox().bottomRight().latitude();

    QVERIFY(object->boundingBox().topLeft().longitude() < object->boundingBox().bottomRight().longitude());

    QGeoCoordinate dateline(0.0, 180.0, 0.0);

    object->setCoordinate(dateline);

    QVERIFY2(object->boundingBox().width()!=0,"no bounding box");
    QVERIFY2(object->boundingBox().height()!=0,"no bounding box");

    QVERIFY(qreal(object->boundingBox().width()) == qreal(width));
    QVERIFY(object->boundingBox().height() == height);

    QVERIFY(object->boundingBox().topLeft().latitude() == top);
    QVERIFY(object->boundingBox().bottomRight().latitude() == bottom);

    QVERIFY(object->boundingBox().topLeft().longitude() > object->boundingBox().bottomRight().longitude());
}

QTEST_MAIN(tst_QGeoMapTextObject)
#include "tst_qgeomaptextobject.moc"

