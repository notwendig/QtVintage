#ifndef _SEG7_H_
#define _SEG7_H_
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

#include <QByteArray>
#include <QColor>
#include <QFrame>
#include <QPolygon>
#include <QRadialGradient>
#include <QRect>
#include <QResizeEvent>
#include <QSize>

class QTimer;

class SEG7 : public QFrame
{
	Q_OBJECT

    Q_PROPERTY(QColor color READ Color WRITE setColor)
    Q_PROPERTY(QColor backr READ Backr WRITE setBackr)
	Q_PROPERTY(bool state READ state WRITE setState)
	Q_PROPERTY(int glowing READ glowing WRITE setGlowing)

public:
	explicit SEG7(QWidget* parent=0);
	~SEG7();

    QColor Color() const;
    QColor Backr() const;
    void setColor(const QColor &color);
    void setBackr(const QColor &color);

	int glowing(void) const;


	bool state() const;

public slots:
    void setState(bool state);
	void toggleState();

	void setsegments(unsigned char data);
	void setdigit(unsigned char data);
	void setGlowing(int glow);

	bool setdecoder(unsigned char first, unsigned char last, const QByteArray &decomap);
	bool setdecoder(const QByteArray &decomap);
	void clrdecoder(void);

protected slots:
	void fade();

public:
	int heightForWidth(int width) const;
	QSize sizeHint() const;
	QSize minimumSizeHint() const;

protected:
	void paintEvent(QPaintEvent* event);
	void resizeEvent ( QResizeEvent * event );

private:
	QColor color_;
    QColor backr_;

	bool state_;

	QPolygon segment_[8]; //! 7 segmente and dot
	QByteArray decoder_;
	bool initialState_;
	QRect segrectf_[8];
	unsigned seglight_[8];
	QTimer *timer_;

	float   border_;
	unsigned char data_;

	//
	// Pixels per mm for x and y...
	//
	int pixX_, pixY_;

	//
	// ScaSEG7 values for x and y diameter.
	//
	int diamX_, diamY_;

	QRadialGradient gradient_;
	int glowing_;
};

#endif
