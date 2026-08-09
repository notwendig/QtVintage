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

#include "SWITCH.h"
#include "SWITCHPlugin.h"

#include <QtPlugin>

SWITCHPlugin::
SWITCHPlugin(QObject* parent) :
    QObject(parent),
    initialized(false)
{
}

QString SWITCHPlugin::
name() const
{
    return "SWITCH";
}

QString SWITCHPlugin::
group() const
{
    return tr("Nadisoft");
}

QString SWITCHPlugin::
toolTip() const
{
    return tr("An SWITCH");
}

QString SWITCHPlugin::
whatsThis() const
{
    return tr("An SWITCH");
}

QString SWITCHPlugin::
includeFile() const
{
    return "SWITCH.h";
}

QIcon SWITCHPlugin::
icon() const
{
    return QIcon(":/segment/switch.png");
}

bool SWITCHPlugin::
isContainer() const
{
    return false;
}

QWidget * SWITCHPlugin::
createWidget(QWidget *parent)
{
    return new SWITCH(parent);
}

QString SWITCHPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"SWITCH\" name=\"switch_\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>100</width>\n"
           "    <height>100</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"styleSheet\">\n"
           "   <string>SWITCH{ background: #363A38; }</string>\n"
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
