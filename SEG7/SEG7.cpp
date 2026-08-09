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

#include <algorithm>

#include <QPainter>
#include <QGradient>
#include <QPaintDevice>
#include <QTimer>
#include <QStyleOption>
#include <QSizePolicy>

#include "SEG7.h"

SEG7::
SEG7(QWidget* parent)
  : QFrame(parent)
  , state_(true)
  , segment_{QPolygon(4),QPolygon(4),QPolygon(4),QPolygon(4),QPolygon(4),QPolygon(4),QPolygon(6),QPolygon(4)}
  , decoder_(0x100,0)
  , initialState_(true)
  , seglight_{100,100,100,100,100,100,100,100}
  , data_(0)
  , glowing_(16)
{
	QSizePolicy p = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	p.setHeightForWidth(true);
	setSizePolicy(p);

	clrdecoder();
	timer_ = new QTimer(this);
	connect(timer_, SIGNAL(timeout()), this, SLOT(fade()));

	setAutoFillBackground(true);
}

SEG7::
~SEG7()
{
}

void SEG7::clrdecoder(void)
{
	static const char bin2hex[16] {
				// pgfedcba
		0x3F,   // 00111111b 0;
		0x06,   // 00000110b 1;
		0x5B,   // 01011011b 2;
		0x4F,   // 01001111b 3;
		0x66,   // 01100110b 4;
		0x6D,   // 01101101b 5;
		0x7D,   // 01111101b 6;
		0x07,   // 00000111b 7;
		0x7F,   // 01111111b 8;
		0x6F,   // 01101111b 9;
		0x77,   // 01110111b A;
		0x7C,   // 01111100b B;
		0x58,   // 01011000b C;
		0x5E,   // 01011110b D;
		0x79,   // 01111001b E;
		0x71    // 01110001b F;
	};

	for(int i = 0x10; i < 0x100; i++)
		decoder_[i] = i;
	decoder_.replace ( 0, 0x10,bin2hex);

}

void SEG7::setsegments(unsigned char data)
{
	unsigned char tmp = data_ ^ data;

	if(!tmp)
		return;

	data_ = data;

	for(int s = 0; tmp ; s++)
        if(tmp & (1 << s))
		{
            tmp &= ~(1 << s);
            seglight_[s] = 255;
            update(segrectf_[s]);
        }

	if(!timer_->isActive())
        timer_->start(10);
}

void SEG7::setdigit(unsigned char data)
{
	setsegments(decoder_[data & 0xF] | ((data << 3) & 0x80));
	//qDebug() << hex << (unsigned) data_;
}


QColor SEG7:: Color() const
{
	return color_;
}

void SEG7:: setColor(const QColor &color)
{
    color_ = color;
}

QColor SEG7:: Backr() const
{
    return backr_;
}

void SEG7:: setBackr(const QColor &color)
{
    backr_ = color;
}

int SEG7::
glowing(void) const
{
	return glowing_;
}

void SEG7::
setGlowing(int glow)
{
	glowing_ = glow;
}


void SEG7::
setState(bool state)
{
	state_ = state;
	update();
}

void SEG7::
toggleState()
{
	state_ = !state_;
	update();
}

int SEG7::
heightForWidth(int width) const
{
	return width*3/2;
}

QSize SEG7::
sizeHint() const
{
	return QSize(diamX_, diamY_);
}

QSize SEG7::
minimumSizeHint() const
{
	return QSize(20,30);
}

void SEG7::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
	QPainter painter(this);
	int s;

	painter.setRenderHint(QPainter::Antialiasing, true);

    if(state_)
        for( s = 0; s < 8; s++)
        {
            if(seglight_[s] && segrectf_[s].intersects(event->rect()))
            {
                QColor fgc(Color());
                QColor brc(Backr());

                if( s != 7)
                    brc.setAlpha(seglight_[s] >> 1);
                QPen pen(brc, border_);
                painter.setPen(pen);
                fgc.setAlpha(seglight_[s]);
                painter.setBrush(QBrush(fgc));
                painter.drawPolygon(segment_[s]);
            }
        }
}

bool SEG7::
state() const
{
	return state_;
}

void SEG7::resizeEvent ( QResizeEvent * event )
{
	if( event->oldSize() != event->size() &&
			!event->oldSize().isNull() &&
			!event->size().isNull())
	{
		float border = (event->size().width() + event->size().height()) / 20.0;
		QRectF   rectf(border,border,event->size().width()-2*border, event->size().height()-2*border);
		float linex = rectf.width() / 5.0;
		float liney = rectf.height() / 7.0;
		float lines = (linex + liney ) / 2.0;
		float lines2 = lines / 2;
		border_ = lines2 / 2;
		// a
		segment_[0].setPoint ( 0, rectf.left(), rectf.top());
		segment_[0].setPoint ( 1, rectf.right(), rectf.top());
		segment_[0].setPoint ( 2, rectf.right()-lines, rectf.top()+lines);
		segment_[0].setPoint ( 3, rectf.left()+lines, rectf.top()+lines);

		// b
		segment_[1].setPoint ( 0, rectf.right(), rectf.top());
		segment_[1].setPoint ( 1, rectf.right(), rectf.top()+rectf.height()/2);
		segment_[1].setPoint ( 2, rectf.right()-lines, rectf.top()+rectf.height()/2-lines2);
		segment_[1].setPoint ( 3, rectf.right()-lines, rectf.top()+lines);

		// c
		segment_[2].setPoint ( 0, rectf.right(), rectf.top()+rectf.height()/2);
		segment_[2].setPoint ( 1, rectf.right(), rectf.bottom());
		segment_[2].setPoint ( 2, rectf.right()-lines, rectf.bottom()-lines);
		segment_[2].setPoint ( 3, rectf.right()-lines, rectf.top()+rectf.height()/2+lines2);

		// d
		segment_[3].setPoint ( 0, rectf.left(), rectf.bottom());
		segment_[3].setPoint ( 1, rectf.right(), rectf.bottom());
		segment_[3].setPoint ( 2, rectf.right()-lines, rectf.bottom()-lines);
		segment_[3].setPoint ( 3, rectf.left()+lines, rectf.bottom()-lines);

		// e
		segment_[4].setPoint ( 0, rectf.left(), rectf.top()+rectf.height()/2);
		segment_[4].setPoint ( 1, rectf.left(), rectf.bottom());
		segment_[4].setPoint ( 2, rectf.left()+lines, rectf.bottom()-lines);
		segment_[4].setPoint ( 3, rectf.left()+lines, rectf.top()+rectf.height()/2+lines2);

		// f
		segment_[5].setPoint ( 0, rectf.left(), rectf.top());
		segment_[5].setPoint ( 1, rectf.left(), rectf.top()+rectf.height()/2);
		segment_[5].setPoint ( 2, rectf.left()+lines, rectf.top()+rectf.height()/2-lines2);
		segment_[5].setPoint ( 3, rectf.left()+lines, rectf.top()+lines);

		// g
		segment_[6].setPoint ( 0, rectf.left(), rectf.top()+rectf.height()/2);
		segment_[6].setPoint ( 1, rectf.left()+lines, rectf.top()+rectf.height()/2-lines2);
		segment_[6].setPoint ( 2, rectf.right()-lines, rectf.top()+rectf.height()/2-lines2);
		segment_[6].setPoint ( 3, rectf.right(), rectf.top()+rectf.height()/2);
		segment_[6].setPoint ( 4, rectf.right()-lines, rectf.top()+rectf.height()/2+lines2);
		segment_[6].setPoint ( 5, rectf.left()+lines, rectf.top()+rectf.height()/2+lines2);

		// dot
		float dotm = border-2;
		float dots= 1;
		segment_[7].setPoint ( 0, rectf.right()+dotm, rectf.bottom()+dotm);
		segment_[7].setPoint ( 1, rectf.right()+dots, rectf.bottom()+dotm);
		segment_[7].setPoint ( 2, rectf.right()+dots, rectf.bottom()+dots);
		segment_[7].setPoint ( 3, rectf.right()+dotm, rectf.bottom()+dots);

		for(int s = 0; s < 8; s++)
			segrectf_[s] = segment_[s].boundingRect().adjusted(-border_,-border_,border_,border_);
	}
}

void SEG7::fade()
{
	int tim = 0;
	for(int s = 0; s < 8; s++)
		if(!(data_ & (1 << s)) && seglight_[s])
		{
			if(glowing_)
                seglight_[s] -= std::min((unsigned)glowing_, seglight_[s]);
			else
				seglight_[s] = 0;

			update(segrectf_[s]);
			tim |=1;
		}
	  if(tim)
		  timer_->start(10);
}

bool SEG7::setdecoder(unsigned char first, unsigned char last, const QByteArray &decomap)
{
	if(last < first)
		return false;
	decoder_.replace ( first, last - first +1, decomap);
	return true;
}

bool SEG7::setdecoder(const QByteArray &decomap)
{
	return setdecoder(0, 0xFF, decomap);
}
