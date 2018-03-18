#include "customdial.h"

#include <QPainter>
#include <QColor>
#include <QLabel>
#include <QRectf>
#include <QPen>
#include <QResizeEvent>
#include <QtMath>

#include <cmath>

CustomDial::CustomDial(QWidget* parent)
: QDial(parent),
  arcRect_(new QRectF),
  valueRect_(new QRectF),
  textRect_(new QRectF),
  arcColor_(new QColor),
  arcPen_(new QPen)
{
    QDial::setRange(0.0, 360.0);

    QDial::setCursor(Qt::PointingHandCursor);

    connect(this, &QDial::valueChanged,
            this, &CustomDial::updateValue);

    setMinimumSize(100,100);

    setMaximumAngle(-360);

    setStartAngle(270);

    updateValue();
    setNotchesVisible(true);

    update();
}

CustomDial::CustomDial(const QString& text,
                       QWidget* parent,
                       int minimum,
                       int maximum)
: QDial(parent),
  text_(text),
  arcRect_(new QRectF),
  valueRect_(new QRectF),
  textRect_(new QRectF),
  arcColor_(new QColor),
  arcPen_(new QPen)
{
    QDial::setRange(minimum, maximum);

    QDial::setCursor(Qt::PointingHandCursor);

    connect(this, &QDial::valueChanged,
            this, &CustomDial::updateValue);

    setMinimumSize(100,100);

    setMaximumAngle(-360);

    setStartAngle(270);
    setArcWidth(2.0);

    updateValue();
    setNotchesVisible(true);

    update();


}

void CustomDial::mousePressEvent(QMouseEvent *e)
{
    if (//d->maximum == d->minimum ||
        (e->button() != Qt::LeftButton)  ||
        (e->buttons() ^ e->button())) {
        e->ignore();
        return;
    }
    e->accept();
    int x=valueFromPoint(e->pos());
    qDebug("%d",x);
    setSliderPosition(x);
    // ### This isn't quite right,
    // we should be doing a hit test and only setting this if it's
    // the actual dial thingie (similar to what QSlider does), but we have no
    // subControls for QDial.
    setSliderDown(true);
}

void CustomDial::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // So that we can use the background color
    // Otherwise the background is transparent
    painter.setBackgroundMode(Qt::OpaqueMode);

    // Smooth out the circle
    painter.setRenderHint(QPainter::Antialiasing);

    // Use background color
    painter.setBrush(painter.background());

    // Get current pen before resetting so we have
    // access to the color() method which returns the
    // color from the stylesheet
    QPen textPen = painter.pen();

    // No border
    painter.setPen(QPen(Qt::NoPen));

    // Draw background circle
    painter.drawEllipse(QDial::rect());
    qDebug("%d, %d, %d, %d",QDial::rect().x(),QDial::rect().y(),QDial::rect().width(),QDial::rect().height());

    painter.setPen(textPen);




    painter.setPen(*arcPen_);
    qDebug("%f, %f, %f, %f, (%f -> %f)",arcRect_->x(),arcRect_->y(),arcRect_->width(),arcRect_->height(),startAngle_,angleSpan_);
//    painter.drawArc(*arcRect_, startAngle_, angleSpan_);
    painter.setBrush(Qt::red);
        painter.drawPie(*arcRect_, startAngle_, angleSpan_);

        painter.drawText(*textRect_, Qt::AlignHCenter | Qt::AlignBottom, text_);

        painter.drawText(*valueRect_, Qt::AlignCenter, valueString_);

}

void CustomDial::resizeEvent(QResizeEvent* event)
{
    QDial::setMinimumSize(event->size());

    double width = QDial::width() - (2 * arcWidth_);

    double height = width / 2;

    *textRect_ = QRectF(arcWidth_, arcWidth_, width, height);

    *valueRect_ = QRectF(arcWidth_, height, width, height);

    *arcRect_ = QRectF(arcWidth_ / 2,
                       arcWidth_ / 2,
                       QDial::width() - arcWidth_,
                       QDial::height() - arcWidth_);
}

void CustomDial::updateValue()
{
    double value = QDial::value();

    // Get ratio between current value and maximum to calculate angle
    double ratio = value / QDial::maximum();

    angleSpan_ = maximumAngleSpan_ * ratio;

    valueString_ = QString::number(value);
}

void CustomDial::setArcWidth(double px)
{
    arcWidth_ = px;

    *arcRect_ = QRectF(arcWidth_ / 2,
                       arcWidth_ / 2,
                       QDial::width() - arcWidth_,
                       QDial::height() - arcWidth_);

    arcPen_->setWidth(arcWidth_);
}

void CustomDial::setText(const QString& text)
{
    text_ = text;
}

QString CustomDial::getText() const
{
    return text_;
}

double CustomDial::getArcWidth() const
{
    return arcWidth_;
}

void CustomDial::setMaximumAngle(double angle)
{
    maximumAngleSpan_ = angle * 16;
}

double CustomDial::getMaximumAngle() const
{
    return maximumAngleSpan_ / 16;
}

void CustomDial::setStartAngle(double angle)
{
    startAngle_ = angle * 16;
}

double CustomDial::getStartAngle() const
{
    return startAngle_ / 16;
}

void CustomDial::setArcColor(const QString& color)
{
    arcColor_->setNamedColor(color);

    arcPen_->setColor(*arcColor_);
}

QString CustomDial::getArcColor() const
{
    return arcColor_->name();
}

int CustomDial::valueFromPoint(const QPoint &p)
{
    double yy = height()/2.0 - p.y();
    double xx = p.x() - width()/2.0;
    double a = (xx || yy) ? std::atan2(yy, xx) : 0;

    if (a < M_PI / -2)
        a = a + M_PI * 2;

    int dist = 0;
    int minv = minimum(), maxv = maximum();


    if (minimum() < 0) {
        dist = -minimum();
        minv = 0;
        maxv = maximum() + dist;
    }

    int r = maxv - minv;
    int v;
    if (wrapping())
        v =  (int)(0.5 + minv + r * (M_PI * 3 / 2 - a) / (2 * M_PI));
    else
        v =  (int)(0.5 + minv + r* (M_PI * 4 / 3 - a) / (M_PI * 10 / 6));

    if (dist > 0)
        v -= dist;

    return !invertedAppearance() ? bound(v) : maximum() - bound(v);
}

int CustomDial::bound(int val)
{
    if (wrapping()) {
        if ((val >= minimum()) && (val <= maximum()))
            return val;
        val = minimum() + ((val - minimum()) % (maximum() - minimum()));
        if (val < minimum())
            val += maximum() - minimum();
        return val;
    } else {
        return bound(val);
    }
}
