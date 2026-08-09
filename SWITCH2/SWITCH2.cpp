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

#include <math.h>

#include <QPainter>
#include <QPaintEvent>
#include <QGradient>
#include <QPaintDevice>
#include <QTimer>

#include "SWITCH2.h"

SWITCH2::
SWITCH2(QWidget* parent) :
	QAbstractButton(parent)
  , color_(255, 230, 4, 255)
{
	QSizePolicy p = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	p.setHeightForWidth(true);
	setSizePolicy(p);
}

SWITCH2::
~SWITCH2()
{
}

unsigned SWITCH2::
getKey(void) const
{
	return keycode_;
}

void SWITCH2::
setKey(unsigned code)
{
	keycode_ = code;
}

QColor SWITCH2::
color() const
{
	return color_;
}

void SWITCH2::
setColor(const QColor& color)
{
	color_ = color;
	update();
}

void SWITCH2::
paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	QPainter p(this);
	QColor bc(palette().color(QWidget::backgroundRole()));
	QBrush brush(bc,Qt::SolidPattern/*Qt::RadialGradientPattern*/);
	QPen pen(color_);
	QRectF rect(0.0,0.0,width(),height());

	p.fillRect(rect,brush);
	rect.adjust(8.0,6.0,-8.0,-6.0);
	bc.setRed(bc.red() ^ color_.red());
	bc.setAlpha(bc.alpha()>>1);
	bc.setGreen(bc.green() ^ color_.green());
	bc.setBlue(bc.blue() ^ color_.blue());
	QBrush brush2(bc,Qt::Dense4Pattern);
	p.fillRect(rect,brush2);
	rect.setHeight(rect.height() / 2.0);
	if(!isChecked ())
		rect.moveTop(rect.bottom());
	p.setPen(pen);
	QBrush brush3(color_,Qt::DiagCrossPattern);
	p.fillRect(rect,brush3);
    p.drawRect(rect);
}


int SWITCH2::
heightForWidth(int width) const
{
	return width*3;
}

QSize SWITCH2::
sizeHint() const
{
	return minimumSizeHint() ;//QSize(diamX_, diamY_);
}

QSize SWITCH2::
minimumSizeHint() const
{
    return QSize(10, 20);
}

