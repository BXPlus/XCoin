#include "togglebtn.h"
#include <QtCore/QEvent>
#include <QtCore/QCoreApplication>
#include <QtCore/QPropertyAnimation>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

ToggleBtn::ToggleBtn(int trackRadius, int thumbRadius, QWidget* parent)
    : QAbstractButton(parent)
{
    setCheckable(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed));
    mTrackRadius = trackRadius;
    mThumbRadius = thumbRadius;
    mAnimation = new QPropertyAnimation(this);
    mAnimation->setTargetObject(this);

    mMargin = 0 > (mThumbRadius - mTrackRadius) ? 0 : (mThumbRadius - mTrackRadius);
    mBaseOffset = mThumbRadius > mTrackRadius ? mThumbRadius : mTrackRadius;
    mEndOffset.insert(true, 4 * mTrackRadius + 2 * mMargin - mBaseOffset); // width - offset
    mEndOffset.insert(false, mBaseOffset);
    mOffset = mBaseOffset;
    QPalette palette = this->palette();

    mTrackColor.insert(true, palette.highlight());
    mTrackColor.insert(false, palette.dark());
    mThumbColor.insert(true, palette.highlight());
    mThumbColor.insert(false, palette.light());
    mTextColor.insert(true, palette.highlightedText().color());
    mTextColor.insert(false, palette.dark().color());
    mThumbText.insert(true, "");
    mThumbText.insert(false, "");
    mOpacity = 0.5;
}


ToggleBtn::~ToggleBtn()
{
    delete mAnimation;
}

QSize ToggleBtn::sizeHint() const
{
    int w = 4 * mTrackRadius + 2 * mMargin;
    int h = 2 * mTrackRadius + 2 * mMargin;

    return QSize(w, h);
}

void ToggleBtn::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPainter::RenderHints m_paintFlags = QPainter::RenderHints(QPainter::Antialiasing |
        QPainter::TextAntialiasing);

    p.setRenderHints(m_paintFlags, true);
    p.setPen(Qt::NoPen);
    bool check = isChecked();
    qreal trackOpacity = mOpacity;
    qreal textOpacity = 1.0;
    qreal thumbOpacity = 1.0;
    QBrush trackBrush;
    QBrush thumbBrush;
    QColor textColor;

    if (this->isEnabled())
    {

        trackBrush = mTrackColor[check];
        thumbBrush = mThumbColor[check];
        textColor = mTextColor[check];
    }
    else
    {
        trackOpacity *= 0.8;
        trackBrush = this->palette().shadow();
        thumbBrush = this->palette().mid();
        textColor = this->palette().shadow().color();
    }

    p.setBrush(trackBrush);
    p.setOpacity(trackOpacity);
    p.drawRoundedRect(mMargin, mMargin, width() - 2 * mMargin, height() - 2 * mMargin, mTrackRadius, mTrackRadius);

    p.setBrush(thumbBrush);
    p.setOpacity(thumbOpacity);
    p.drawEllipse(mOffset - mThumbRadius, mBaseOffset - mThumbRadius, 2 * mThumbRadius, 2 * mThumbRadius);

    p.setPen(textColor);
    p.setOpacity(textOpacity);
    QFont font = p.font();
    font.setPixelSize(1.5*mThumbRadius);
    p.setFont(font);

    QPainterPath textPath;
    qreal pixelOffset = (qreal)mThumbRadius * (1 - 1 / 1.414);
    textPath.addText(mOffset - mThumbRadius + pixelOffset, mBaseOffset + mThumbRadius - pixelOffset, font, mThumbText.value(check));
    p.drawPath(textPath);
}

void ToggleBtn::resizeEvent(QResizeEvent* e)
{
    QAbstractButton::resizeEvent(e);
    mOffset = mEndOffset.value(isChecked());
}

void ToggleBtn::mouseReleaseEvent(QMouseEvent  *e)
{
    QAbstractButton::mouseReleaseEvent(e);
    if (e->button() == Qt::LeftButton)
    {
        mAnimation->setDuration(120);
        mAnimation->setPropertyName("mOffset");
        mAnimation->setStartValue(mOffset);
        mAnimation->setEndValue(mEndOffset[isChecked()]);
        mAnimation->start();
    }
}

void ToggleBtn::enterEvent(QEvent * event)
{
    setCursor(Qt::PointingHandCursor);
    QAbstractButton::enterEvent(event);
}

void ToggleBtn::setChecked(bool checked)
{
    QAbstractButton::setChecked(checked);
    mOffset = mEndOffset.value(checked);
}



int ToggleBtn::offset()
{
    return mOffset;
}

void ToggleBtn::setOffset(int value)
{
    mOffset = value;
    update();
}
