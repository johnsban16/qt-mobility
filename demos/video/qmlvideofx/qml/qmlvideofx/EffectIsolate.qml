/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

// Based on http://kodemongki.blogspot.com/2011/06/kameraku-custom-shader-effects-example.html

import QtQuick 1.0

Effect {
    // Constant properties which must be supported by every effect
    property int numParameters: 2
    property bool supportsDivider: true

    property real param1Value: 0.5
    property real param2Value: 0.5
    property real dividerValue: 0.5

    property real targetHue: 360.0 * param1Value
    property real windowWidth: 60.0 * param2Value

    fragmentShader: fragmentShaderCommon + "
        uniform float targetHue;
        uniform float windowWidth;
        uniform float dividerValue;

        uniform sampler2D source;
        uniform lowp float qt_Opacity;
        varying vec2 qt_TexCoord0;

        void rgb2hsl(vec3 rgb, out float h, out float s, float l)
        {
            float maxval = max(rgb.r, max(rgb.g, rgb.b));
            float minval = min(rgb.r, min(rgb.g, rgb.b));
            float delta = maxval - minval;
            l = (minval + maxval) / 2.0;
            s = 0.0;
            if (l > 0.0 && l < 1.0)
                s = delta / (l < 0.5 ? 2.0 * l : 2.0 - 2.0 * l);
            h = 0.0;
            if (delta > 0.0)
            {
                if (rgb.r == maxval && rgb.g != maxval)
                    h += (rgb.g - rgb.b ) / delta;
                if (rgb.g == maxval && rgb.b != maxval)
                    h += 2.0  + (rgb.b - rgb.r) / delta;
                if (rgb.b == maxval && rgb.r != maxval)
                    h += 4.0 + (rgb.r - rgb.g) / delta;
                h *= 60.0;
            }
        }

        void main()
        {
            vec2 uv = qt_TexCoord0.xy;
            vec3 col = texture2D(source, uv).rgb;
            float h, s, l;
            rgb2hsl(col, h, s, l);
            float h2 = (h > targetHue) ? h - 360.0 : h + 360.0;
            float y = 0.3 * col.r + 0.59 * col.g + 0.11 * col.b;
            vec3 result;
            if (uv.x > dividerValue || (abs(h - targetHue) < windowWidth) || (abs(h2 - targetHue) < windowWidth))
                result = col;
            else
                result = vec3(y, y, y);
            gl_FragColor = qt_Opacity * vec4(result, 1.0);
        }"
}