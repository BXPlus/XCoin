#ifndef LIVEWINDOW_H
#define LIVEWINDOW_H

#include <QMainWindow>

namespace Ui {
class LiveWindow;
}

class LiveWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LiveWindow(QWidget *parent = nullptr);
    ~LiveWindow();

private:
    Ui::LiveWindow *ui;
};

#endif // LIVEWINDOW_H
