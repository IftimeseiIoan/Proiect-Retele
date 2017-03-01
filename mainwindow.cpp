#include "mainwindow.h"
#include "ui_mainwindow.h"
QLabel *time_aux,*date_aux;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont times_font("Times", 10, QFont::StyleNormal);
    QString directory = qApp->applicationDirPath();
    QString name = "background_login.png";
    QString directory_name=directory+"/images/"+name;
    QPixmap bkgnd(directory_name);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);




    QLabel *usr = new QLabel("Username");
    usr->setFont(times_font);
    QLabel *pswd = new QLabel("Password");
    pswd->setFont(times_font);
    QLineEdit *user_library = new QLineEdit();
    QLineEdit *password_library = new QLineEdit();

    user_library->setMinimumWidth(100);
    user_library->setMaximumWidth(160);
    user_library->setMaxLength(20);
    user_library->setPlaceholderText("max 10 characters");
    password_library->setMinimumWidth(100);
    password_library->setMaximumWidth(160);
    password_library->setEchoMode(QLineEdit::Password);
    password_library->setPlaceholderText("max 20 characters");
    password_library->setMaxLength(20);




    usr->setAlignment(Qt::AlignHCenter);
    user_library->setAlignment(Qt::AlignHCenter);
    pswd->setAlignment(Qt::AlignHCenter);
    password_library->setAlignment(Qt::AlignHCenter);

    user_library->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    QPushButton *login=new QPushButton("Login");
    login->setFont(times_font);
    QPushButton *exit=new QPushButton("Exit");
    exit->setFont(times_font);
    login->setFixedHeight(25);
    login->setFixedWidth(50);
    exit->setFixedHeight(25);
    exit->setFixedWidth(50);



    QGridLayout *login_grid=new QGridLayout;
    login_grid->setAlignment(Qt::AlignCenter);
    login_grid->addWidget(usr,0,0,1,2);
    login_grid->addWidget(user_library,1,0,1,2);
    login_grid->addWidget(pswd,2,0,1,2);
    login_grid->addWidget(password_library,3,0,1,2);
    login_grid->addWidget(login,4,0,1,1);
    login_grid->addWidget(exit,4,1,1,1,Qt::AlignRight);




    //*********************
    QLabel *time_library=new QLabel;
    QLabel *date_library=new QLabel;
    QVBoxLayout *login_layout =new QVBoxLayout;
    login_layout->addLayout(login_grid,Qt::AlignCenter);
    login_layout->addWidget(time_library,Qt::AlignLeft,Qt::AlignBottom);
    login_layout->addWidget(date_library,Qt::AlignLeft,Qt::AlignBottom);
    //********************** ceas+data

   //**************************
   QTimer *timer=new QTimer(this);
   connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
   timer->start();
   time_aux=time_library;
   date_aux=date_library;
   this->setFocus();
   QObject::connect(exit, SIGNAL(clicked()),this, SLOT(clickedSlot_EXIT()));
   QObject::connect(login, SIGNAL(clicked()),this, SLOT(clickedSlot_LOGIN()));
   //*************************** pornire timer



   this->centralWidget()->setLayout(login_layout);
   this->resize(600,400);




QWidget *mama=new QWidget;
mama=(QWidget*)login_grid;
//this->setCentralWidget()->setLayout(login_layout);
//this->setCentralWidget(mama);



   /*QStackedWidget *app_interface=new QStackedWidget;
   // app_interface->insertWidget(0,)

    QWidget *asd=new QWidget;
    asd->



    app_interface->addWidget(time_library);
    app_interface->setCurrentIndex(0);
    this->setCentralWidget(app_interface);
*/

}

void MainWindow::clickedSlot_EXIT()
{
   QApplication::quit();
}

void MainWindow::clickedSlot_LOGIN()
{
this->centralWidget()->hide();

//this->centralWidget()->setVisible(1);
}

void MainWindow::resizeEvent(QResizeEvent *evt)
{
    QString directory = qApp->applicationDirPath();
    QString name = "background_login.png";
    QString directory_name=directory+"/images/"+name;

    QPixmap bkgnd(directory_name);
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);//set scale of pic to match the window
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Background, bkgnd);//set the pic to the background
    setPalette(p);//show the background pic
QMainWindow::resizeEvent(evt); //call base implementation
}

void MainWindow::showTime()
{
    QTime time=QTime::currentTime();
    QDateTime date=QDateTime::currentDateTime();
    QString date_text=date.toString("dd.MM.yyyy");
    QString time_text=time.toString("hh : mm : ss");
    time_aux->setText(time_text);
    date_aux->setText(date_text);
}

MainWindow::~MainWindow()
{
    delete ui;
}
