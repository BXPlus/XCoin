#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("XCoin App");

    mainwidget = new QWidget(this);
    m_vLayout = new QVBoxLayout(this);

    mainwidget->setLayout(m_vLayout);

    for (int i=0; i<6; i++){
        if (i == 0){
            HomeButton* btn = new HomeButton(mainwidget);
            //listbtn.append(btn);
            btn->move(0, i*30);
            m_vLayout->addWidget(btn);
            m_vLayout->addSpacing(18);
        }
        if (i == 1){
            BalanceButton* btn = new BalanceButton(mainwidget);
            //listbtn.append(btn);
            btn->move(0, i*30);
            m_vLayout->addWidget(btn);
        }
        if (i == 2){
            PayButton* btn = new PayButton(mainwidget);
            //listbtn.append(btn);
            btn->move(0, i*30);
            m_vLayout->addWidget(btn);
        }
        if (i == 3){
            ContactButton* btn = new ContactButton(mainwidget);
            //listbtn.append(btn);
            btn->move(0, i*30);
            m_vLayout->addWidget(btn);
        }
        if (i == 4){
            GraphButton* btn = new GraphButton(mainwidget);
            //listbtn.append(btn);
            btn->move(0, i*30);
            m_vLayout->addWidget(btn);
        }
        if (i == 5){
            LiveButton* btn = new LiveButton(mainwidget);
            //listbtn.append(btn);
            btn->move(0, i*30);
            m_vLayout->addWidget(btn);
        }
}
    setCentralWidget(mainwidget);
};

MainWindow::~MainWindow()
{
}

