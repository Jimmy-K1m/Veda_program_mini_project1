#include "mainwindow.h"
#include <QMenuBar>
#include <QAction>
#include <QLineEdit>
#include <QToolBar>
#include <QLineEdit>
#include <QMessageBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent, QVector<Member>& Members)
    : QMainWindow(parent)
{
    this->resize(300,200); // width, height
    QToolBar *Bankingtoolbar = addToolBar("&Banking");
        //setMenuBar(menubar);
    Bankingtoolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QAction *depositAct = makeAction(":/images/deposit.png", "&Deposit", "Ctrl+D", \
                                     "Deposit", this, SLOT(deposit( )));
    QAction *withdrawAct = makeAction(":/images/withdraw.png", "&Withdraw", "Ctrl+W", \
                                      "Withdraw", this, SLOT(withdraw( )));
    QAction *checkAct = makeAction(":/images/check.png", "&Check", "Ctrl+C", \
                                   "Check", this, SLOT(check( )));
    QAction *sendAct = makeAction(":/images/send.png", "&Send", "Ctrl+S", \
                                  "Send", this, SLOT(send( )));
    QAction *exitAct = makeAction(":/images/exit.png", "&Exit", "Ctrl+E", \
                                  "Exit", this, SLOT(exit( )));




    Bankingtoolbar->addAction(depositAct);
    Bankingtoolbar->addAction(withdrawAct);
    Bankingtoolbar->addAction(checkAct);
    Bankingtoolbar->addAction(sendAct);
    Bankingtoolbar->addAction(exitAct);


}

MainWindow::~MainWindow() {}


QAction *MainWindow::makeAction(QString icon, QString name, \
                                QString shortCut, QString toolTip, \
                                QObject* recv, const char* slot)
{
    QAction *act = new QAction(name, this);
    if(icon.length( ))
        act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered( )), recv, slot);
    return act;
}



void MainWindow::deposit(){
    qDebug() << "deposit";
    QLineEdit *inputMoney = new QLineEdit(this);
    inputMoney->setPlaceholderText("Type down how much do you want to deposit");
    setCentralWidget(inputMoney);
    connect(inputMoney,&QLineEdit::editingFinished, [=](){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Check", "Are you sure to put the money into the account?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            balance += inputMoney->text().toInt();
            qDebug()<<balance;
        }}
            );


}

void MainWindow::withdraw(){
    qDebug() << "withdraw";
    QLineEdit *withdrawMoney = new QLineEdit(this);
    withdrawMoney->setPlaceholderText("Type down how much do you want to withdraw");
    setCentralWidget(withdrawMoney);
    connect(withdrawMoney,&QLineEdit::editingFinished, [=](){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Check", "Are you sure to take the money from account?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // 금액부족시 다시 입력시키기
            balance -= withdrawMoney->text().toInt();
            qDebug()<<balance;

        }}
            );
}


void MainWindow::check(){
    QString sentence = "Your balance ->" +  QString::number(balance);
    QLabel* check_screen = new QLabel;
    check_screen->setText(sentence);
    setCentralWidget(check_screen);
    qDebug() << "check";
    //
}

void MainWindow::send(){
    qDebug() << "send";
    QLineEdit *sendMoney[2];


    QStringList labels;
    labels << "&ACCOUNT" << "&AMOUNT";

    QFormLayout *formLayout = new QFormLayout;
    for(int i = 0 ; i <2 ;i++){
        sendMoney[i]= new QLineEdit(this);
        formLayout->addRow(labels[i], sendMoney[i]);
    }
    sendMoney[0]->setPlaceholderText("Type down bank account of opponent");
    sendMoney[1]->setPlaceholderText("Type down how much do you want to send");

    QGroupBox *groupBox = new QGroupBox();
    groupBox->setLayout(formLayout);

    setCentralWidget(groupBox);
    connect(sendMoney[1],&QLineEdit::editingFinished, [=](){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Check", "Are you sure to send the money?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            balance -= sendMoney[1]->text().toInt();
            qDebug()<<balance;
            /*
            타 계정 돈 + 시키기
            */
        }}
            );
}
void MainWindow::exit(){
    qDebug()<< "exit";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "", "Are you sure to want to exit?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        //MainWindow::~MainWindow();

        //파일에 모두 저장시키는
        QApplication::closeAllWindows();
    }
    // 첫화면
}

void MainWindow::getInformation(QString name, int balance){
    this->name = name;
    this->balance = balance;
    QLabel* initial_screen = new QLabel;
    //qDebug()<<name;
    initial_screen->setText("Welcome " + name + "\n" + "How can I help you?");
    setCentralWidget(initial_screen);
}
