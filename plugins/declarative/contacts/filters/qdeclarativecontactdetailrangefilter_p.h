/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef QDECLARATIVECONTACTDETAILRANGEFILTER_H
#define QDECLARATIVECONTACTDETAILRANGEFILTER_H

#include "qdeclarativecontactfilter_p.h"
#include "qcontactdetailrangefilter.h"

class QDeclarativeContactDetailRangeFilter : public QDeclarativeContactFilter
{
    Q_OBJECT
    Q_PROPERTY(QString detail READ detailDefinitionName WRITE setDetailDefinitionName NOTIFY valueChanged)
    Q_PROPERTY(QString field READ fieldName WRITE setFieldName NOTIFY valueChanged)
    Q_PROPERTY(QVariant min READ minValue WRITE setMinValue NOTIFY valueChanged)
    Q_PROPERTY(QVariant max READ maxValue WRITE setMaxValue NOTIFY valueChanged)
    Q_PROPERTY(MatchFlags matchFlags READ matchFlags WRITE setMatchFlags NOTIFY valueChanged)
    Q_PROPERTY(RangeFlags rangeFlags READ rangeFlags WRITE setRangeFlags NOTIFY valueChanged)
    Q_FLAGS(RangeFlags)
public:
    enum RangeFlag {
        IncludeLower = 0, // [
        IncludeUpper = 1, // ]
        ExcludeLower = 2, // (
        ExcludeUpper = 0  // ) - Default is [)
    };
    Q_DECLARE_FLAGS(RangeFlags, RangeFlag)

    QDeclarativeContactDetailRangeFilter(QObject* parent = 0)
        :QDeclarativeContactFilter(parent)
    {
    }


    QString detailDefinitionName() const
    {
        return d.detailDefinitionName();
    }
    void setDetailDefinitionName(const QString& definition)
    {
        d.setDetailDefinitionName(definition, d.detailFieldName());
    }

    QString fieldName() const
    {
        return d.detailFieldName();
    }
    void setFieldName(const QString& field)
    {
        d.setDetailDefinitionName(d.detailDefinitionName(), field);
    }

    QDeclarativeContactFilter::MatchFlags matchFlags() const
    {
        QDeclarativeContactFilter::MatchFlags matchFlags;
        matchFlags &= 0xFFFFFFFF;
        matchFlags &= (int)d.matchFlags();
        return matchFlags;
    }
    void setMatchFlags(QDeclarativeContactFilter::MatchFlags flags)
    {
        QContactFilter::MatchFlags matchFlags;
        matchFlags &= 0xFFFFFFFF;
        matchFlags &= (int)flags;
        d.setMatchFlags(matchFlags);
    }

    QDeclarativeContactDetailRangeFilter::RangeFlags rangeFlags() const
    {
        QDeclarativeContactDetailRangeFilter::RangeFlags flags;
        flags &= 0xFFFFFFFF;
        flags &= (int)d.rangeFlags();
        return flags;
    }
    void setRangeFlags(QDeclarativeContactDetailRangeFilter::RangeFlags flags)
    {
        QContactDetailRangeFilter::RangeFlags rangeFlags;
        rangeFlags &= 0xFFFFFFFF;
        rangeFlags &= (int)flags;
        d.setRange(d.minValue(), d.maxValue(), rangeFlags);
    }

    QVariant minValue() const
    {
        return d.minValue();
    }
    void setMinValue(const QVariant& value)
    {
        d.setRange(value, d.maxValue(), d.rangeFlags());
    }

    QVariant maxValue() const
    {
        return d.maxValue();
    }
    void setMaxValue(const QVariant& value)
    {
        d.setRange(d.minValue(), value, d.rangeFlags());
    }

    QContactFilter filter() const
    {
        return d;
    }
signals:
    void valueChanged();


private:
    QContactDetailRangeFilter d;
};

QML_DECLARE_TYPE(QDeclarativeContactDetailRangeFilter)

#endif