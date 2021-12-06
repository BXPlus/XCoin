#ifndef TOGGLEBTN_H
#define TOGGLEBTN_H

#include <QtWidgets/QAbstractButton>


class QPropertyAnimation;

class ToggleBtn :public QAbstractButton
{
    Q_OBJECT
        Q_PROPERTY(int mOffset READ offset WRITE setOffset);
public:
    explicit ToggleBtn(int trackRadius, int thumbRadius, QWidget* parent = nullptr);
    ~ToggleBtn();

    QSize sizeHint() const override;
    void setOffset(int value);

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent*) override;
    void mouseReleaseEvent(QMouseEvent  *) override;
    void enterEvent(QEvent *event) override;
    void setChecked(bool checked);

    int offset();

private:
    qreal mOffset;
    qreal mBaseOffset;
    qreal mMargin;
    qreal mTrackRadius;
    qreal mThumbRadius;
    qreal mOpacity;
    QPropertyAnimation* mAnimation;

    QHash<bool, qreal> mEndOffset;
    QHash<bool, QBrush> mTrackColor;
    QHash<bool, QBrush> mThumbColor;
    QHash<bool, QColor> mTextColor;
    QHash<bool, QString> mThumbText;

};

#endif // TOGGLEBTN_H
