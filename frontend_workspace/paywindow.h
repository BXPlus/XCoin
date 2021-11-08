#ifndef PAYWINDOW_H
#define PAYWINDOW_H

#include <QMainWindow>

namespace Ui {
class PayWindow;
}

class PayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PayWindow(QWidget *parent = nullptr);
    ~PayWindow();

private:
    Ui::PayWindow *ui;
};

#endif // PAYWINDOW_H
