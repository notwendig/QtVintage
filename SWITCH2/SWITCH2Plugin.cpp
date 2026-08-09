/*
 * Declaration file for the instruction Z80 opcode emulator.
 * Copyright (C) 2014  Juergen Willi Sievers @notwendiger.
 *                     <notwendig@augenpunkte.de>
 * Includes possible all documented and and undocumented opcodes.
 *
 *
 * This file is part of libZ80 - Zilog's Z80 instruction set emulator.
 *
 * SEL Z80 Trainer simulation
 * libZ80 is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * If you got some questions or find  bugs or parts that could be made better
 * don't hesitate to drop a line by email: <notwendig@augenpunkte.de> or also
 * by Twitter @notwendiger
 *
 * MANY THANKS TO Cristian Dinu thanks a lot your document has inspired me to go this way
 * by developing my own z80 instruction set simulator.
 *
 * An document by Cristian Dinu, compiled by using various sources of information
 * (see the acknowledgements section at http://www.z80.info/decoding.htm).
*/

#include "SWITCH2.h"
#include "SWITCH2Plugin.h"

#include <QtPlugin>

SWITCH2Plugin::
SWITCH2Plugin(QObject* parent) :
    QObject(parent),
    initialized(false)
{
}

QString SWITCH2Plugin::
name() const
{
    return "SWITCH2";
}

QString SWITCH2Plugin::
group() const
{
    return tr("Nadisoft");
}

QString SWITCH2Plugin::
toolTip() const
{
    return tr("An SWITCH2");
}

QString SWITCH2Plugin::
whatsThis() const
{
    return tr("An SWITCH2");
}

QString SWITCH2Plugin::
includeFile() const
{
    return "SWITCH2.h";
}

QIcon SWITCH2Plugin::
icon() const
{
    return QIcon(":/segment/switch2.png");
}

bool SWITCH2Plugin::
isContainer() const
{
    return false;
}

QWidget * SWITCH2Plugin::
createWidget(QWidget *parent)
{
    return new SWITCH2(parent);
}

QString SWITCH2Plugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"SWITCH2\" name=\"shiftsw_\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>100</width>\n"
           "    <height>100</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"styleSheet\">\n"
           "   <string>SWITCH2{ background: #363A38; }</string>\n"
           "  </property>\n"
           "  <property name=\"toolTip\" >\n"
           "   <string>Simple Pushbutton.</string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\" >\n"
           "   <string>An Bushbutton with Label and Sublabel.</string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}
