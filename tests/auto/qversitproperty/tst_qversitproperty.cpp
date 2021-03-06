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

//TESTED_COMPONENT=src/versit

#include "tst_qversitproperty.h"
#include "qversitproperty.h"
#include "qversitproperty_p.h"
#include "qversitdocument.h"
#include <QtTest/QtTest>

QTM_USE_NAMESPACE

void tst_QVersitProperty::init()
{
    mVersitProperty = new QVersitProperty();
    QVERIFY(mVersitProperty);
}

void tst_QVersitProperty::cleanup()
{
   delete mVersitProperty;
}

void tst_QVersitProperty::testGroup()
{
    // One group
    QStringList group(QLatin1String("GROUP_NAME"));
    mVersitProperty->setGroups(group);
    QCOMPARE(mVersitProperty->groups(), group);

    // Several groups
    QStringList groupList;
    groupList.append(QLatin1String("GROUP1"));
    groupList.append(QLatin1String("Group2"));
    groupList.append(QLatin1String("group3"));
    mVersitProperty->setGroups(groupList);
    QCOMPARE(mVersitProperty->groups(), groupList);
}

void tst_QVersitProperty::testName()
{
    // Name in upper case
    QString name(QLatin1String("TEL"));
    mVersitProperty->setName(name);
    QCOMPARE(mVersitProperty->name(), name);

    // Name in lower case, converted automatically to upper case
    mVersitProperty->setName(QLatin1String("tel"));
    QCOMPARE(mVersitProperty->name(), name);
}

void tst_QVersitProperty::testParameters()
{
    QString typeParameterName(QLatin1String("TYPE"));

    QString name(QLatin1String("type"));
    QString value1(QLatin1String("home"));
    mVersitProperty->insertParameter(name,value1);
    QMultiHash<QString,QString> parameters = mVersitProperty->parameters();
    QCOMPARE(parameters.count(), 1);
    QVERIFY(parameters.contains(typeParameterName,QLatin1String("home")));

    QString value2(QLatin1String("voice"));
    mVersitProperty->insertParameter(name,value2);
    parameters = mVersitProperty->parameters();
    QCOMPARE(parameters.count(), 2);
    QVERIFY(parameters.contains(typeParameterName,QLatin1String("home")));
    QVERIFY(parameters.contains(typeParameterName,QLatin1String("voice")));

    mVersitProperty->removeParameter(name,value1);
    QCOMPARE(mVersitProperty->parameters().count(), 1);
    QVERIFY(parameters.contains(typeParameterName,QLatin1String("home")));

    mVersitProperty->removeParameter(name,value2);
    QCOMPARE(mVersitProperty->parameters().count(), 0);

    mVersitProperty->insertParameter(name, value1);
    mVersitProperty->insertParameter(name, value2);
    QCOMPARE(mVersitProperty->parameters().count(), 2);
    mVersitProperty->removeParameters(name);
    QCOMPARE(mVersitProperty->parameters().count(), 0);
}

void tst_QVersitProperty::testValue()
{
    QString value(QLatin1String("050484747"));
    mVersitProperty->setValue(value);
    QCOMPARE(mVersitProperty->value(), value);
}

void tst_QVersitProperty::testEmbeddedDocument()
{
    QVersitDocument document;
    QVersitProperty property;
    property.setName(QLatin1String("X-tension"));
    document.addProperty(property);
    mVersitProperty->setValue(QVariant::fromValue(document));
    QList<QVersitProperty> embeddedDocumentProperties =
        mVersitProperty->value<QVersitDocument>().properties();
    QCOMPARE(embeddedDocumentProperties.count(),1);
    QCOMPARE(embeddedDocumentProperties[0].name(),QLatin1String("X-TENSION"));
}

void tst_QVersitProperty::testEquality()
{
    QVersitProperty property1;
    QVersitProperty property2;
    QVERIFY(property1.isEmpty());
    QVERIFY(property1 == property2);
    QVERIFY(!(property1 != property2));
    property2.setName(QLatin1String("FN"));
    property2.setValue(QLatin1String("John Citizen"));
    QVERIFY(!(property1 == property2));
    QVERIFY(property1 != property2);
    QVERIFY(!property2.isEmpty());

    property1.setName(QLatin1String("FN"));
    property1.setValue(QLatin1String("John Citizen"));
    QVERIFY(property1 == property2);
    QVERIFY(!(property1 != property2));

    property2.clear();
    QVERIFY(property2.isEmpty());

    property1.clear();
    QVERIFY(property1 == property2);
    QVERIFY(!(property1 != property2));
}

void tst_QVersitProperty::testHash()
{
    QVersitProperty property1;
    property1.setGroups(QStringList() << QLatin1String("group1") << QLatin1String("group2"));
    property1.setName(QLatin1String("name"));
    property1.setValue(QLatin1String("value"));
    property1.insertParameter(QLatin1String("param"), QLatin1String("value"));
    QVersitProperty property2;
    property2.setGroups(QStringList() << QLatin1String("group1") << QLatin1String("group2"));
    property2.setName(QLatin1String("name"));
    property2.setValue(QLatin1String("value"));
    property2.insertParameter(QLatin1String("param"), QLatin1String("value"));
    QVersitProperty property3; // no groups
    property3.setName(QLatin1String("name"));
    property3.setValue(QLatin1String("value"));
    property3.insertParameter(QLatin1String("param"), QLatin1String("value"));
    QVersitProperty property4; // no params
    property4.setGroups(QStringList() << QLatin1String("group1") << QLatin1String("group2"));
    property4.setName(QLatin1String("name"));
    property4.setValue(QLatin1String("value"));

    QVERIFY(qHash(property1) == qHash(property2));
    QVERIFY(qHash(property1) != qHash(property3));
    QVERIFY(qHash(property1) != qHash(property4));
    QVERIFY(qHash(property3) != qHash(property4));
    QSet<QVersitProperty> set;
    set.insert(property1);
    set.insert(property2);
    set.insert(property3);
    set.insert(property4);
    QCOMPARE(set.size(), 3);
}

QTEST_MAIN(tst_QVersitProperty)

