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

#include "SWITCH.h"

SWITCH::
SWITCH(QWidget* parent) :
	QAbstractButton(parent)
  , color_(255, 230, 4, 255)
{
	QSizePolicy p = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	p.setHeightForWidth(true);
	setSizePolicy(p);
}

SWITCH::
~SWITCH()
{
}

unsigned SWITCH::
getKey(void) const
{
	return keycode_;
}

void SWITCH::
setKey(unsigned code)
{
	keycode_ = code;
}

QColor SWITCH::
color() const
{
	return color_;
}

void SWITCH::
setColor(const QColor& color)
{
	color_ = color;
	update();
}

void SWITCH::
paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	QPainter p(this);
	QBrush brush(palette().color(QWidget::backgroundRole()),Qt::SolidPattern/*Qt::RadialGradientPattern*/);
	QPen pen(color_);
	QRectF rect(0.0,0.0,width(),height());
	QRect fontBoundRect;
	QStringList label(text().split(QChar('\n')));

	p.fillRect(rect,brush);
	rect.adjust(1.0,1.0,-1.0,-1.0);

	float xFactor;
	float yFactor;
	float factor;

	p.setPen(pen);

	if(label.size() == 2)
	{
		QRectF sub(rect.adjusted(0,0,0,-(rect.height() * 3.0 / 5.0)));
		QFont font = p.font();
		font.setBold(true);
		p.setFont(font);
		rect.adjust(0,rect.height() * 2.0 / 5.0,0,0);

		fontBoundRect = p.fontMetrics().boundingRect(sub.toRect(),0, label[0]);

		xFactor = sub.width() / fontBoundRect.width();
		yFactor = sub.height() / fontBoundRect.height();
		factor = xFactor < yFactor ? xFactor : yFactor;
		font = p.font();
		font.setPointSizeF(font.pointSizeF()*factor);
		p.setFont(font);
		p.drawText(sub, Qt::AlignCenter, label[0]);
		label.removeFirst();
	}

	fontBoundRect = p.fontMetrics().boundingRect(rect.toRect(),0, "Ww"/*label[0]*/);

	xFactor = rect.width() / fontBoundRect.width();
	yFactor = rect.height() / fontBoundRect.height();
	factor = xFactor < yFactor ? xFactor : yFactor;
	QFont font = p.font();
	font.setPointSizeF(font.pointSizeF()*factor);
	p.setFont(font);
	p.drawText(rect, Qt::AlignCenter, label[0]);
}


QSize SWITCH::
sizeHint() const
{
    return minimumSizeHint();
}

int SWITCH::heightForWidth(int width) const
{
	return width;
}


