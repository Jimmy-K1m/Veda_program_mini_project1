#include <QMenuBar>
#include <QAction>
#include <QLineEdit>
#include <QToolBar>
#include <QLineEdit>
#include <QMessageBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QApplication>
#include <QPushButton>

#include "mainwindow.h"
#include "functiondata.h"


MainWindow::MainWindow(QWidget *parent, QVector<Member>& Members)
    : QMainWindow(parent)
{
    qRegisterMetaType<QVector<Member>>("QVector<Member>");

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
    QAction *sendAct = new QAction(QIcon(":/images/send.png"), "&Send", this);
    sendAct->setShortcut(QKeySequence("Ctrl+S"));
    sendAct->setStatusTip("Send");
    connect(sendAct, &QAction::triggered, this, [this, &Members]() {
        this->send(Members);
    });

    QAction *exitAct = new QAction(QIcon(":/images/exit.png"), "&Exit", this);
    exitAct->setShortcut(QKeySequence("Ctrl+E"));
    exitAct->setStatusTip("Exit");
    connect(exitAct, &QAction::triggered, this, [this, &Members]() {
        this->exit(Members);
    });


    Bankingtoolbar->addAction(depositAct);
    Bankingtoolbar->addAction(withdrawAct);
    Bankingtoolbar->addAction(checkAct);
    Bankingtoolbar->addAction(sendAct);
    Bankingtoolbar->addAction(exitAct);


}
    MainWindow::~MainWindow(){
    qDebug() << "~MAinWinow";
}


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
    QWidget *widget = new QWidget(this);
    QFormLayout *formLayout = new QFormLayout(widget);
    QLabel *amountLabel = new QLabel("Amount:", this);
    QLineEdit *inputMoney = new QLineEdit(this);
    inputMoney->setPlaceholderText("Type down how much do you want to deposit");

    QPushButton *okButton = new QPushButton("OK", this);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);



    formLayout->addRow(amountLabel,inputMoney);
    formLayout->addRow(okButton);

    widget->setLayout(formLayout);

    setCentralWidget(widget);

    connect(okButton,&QPushButton::clicked, [=](){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Check", "Are you sure to put the money into the account?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            balance += inputMoney->text().toInt();
            qDebug()<<balance;
            QMessageBox::information(this, "Success", "Complete your work!");
            inputMoney->clear();
            return;
        }
    }
    );


}

void MainWindow::withdraw(){
    qDebug() << "withdraw";
    QWidget *widget = new QWidget(this);
    QFormLayout *formLayout = new QFormLayout(widget);
    QLabel *amountLabel = new QLabel("Amount:", this);
    QLineEdit *withdrawMoney = new QLineEdit(this);
    withdrawMoney->setPlaceholderText("Type down how much do you want to withdraw");

    QPushButton *okButton = new QPushButton("OK", this);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);

    formLayout->addRow(amountLabel, withdrawMoney);
    //formLayout->addRow(withdrawMoney);
    formLayout->addRow(okButton);


    widget->setLayout(formLayout);

    setCentralWidget(widget);

    connect(okButton,&QPushButton::clicked, [=](){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Check", "Are you sure to take the money from account?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if(balance < withdrawMoney->text().toInt())
            {
                QMessageBox::warning(this, "Warning", "Your balance is not enough to withdraw", QMessageBox::Yes );
                withdrawMoney->clear();
                return;
            }
            QMessageBox::information(this, "Success", "Complete your work!");
            balance -= withdrawMoney->text().toInt();
            qDebug()<<balance;
            withdrawMoney->clear();
        }}
        );
}


void MainWindow::check(){
    QWidget *widget = new QWidget(this);
    QFormLayout *formLayout = new QFormLayout(widget);

    QString sentence = "Your balance : " +  QString::number(balance);
    QLabel* check_screen = new QLabel;
    check_screen->setText(sentence);

    formLayout->addRow(check_screen);
    widget->setLayout(formLayout);

    setCentralWidget(widget);
    qDebug() << "check";
    //
}

void MainWindow::send(QVector<Member>& Members){
    qDebug() << "send";
    QLineEdit *sendMoney[2];


    QStringList labels;
    labels << "&Account:" << "&Amount:";
    QWidget* widget = new QWidget(this);
    QFormLayout *formLayout = new QFormLayout(widget);
    for(int i = 0 ; i <2 ;i++){
        sendMoney[i]= new QLineEdit(this);
        formLayout->addRow(labels[i], sendMoney[i]);
    }
    sendMoney[0]->setPlaceholderText("Type down bank account of opponent");
    sendMoney[1]->setPlaceholderText("Type down how much do you want to send");



    QPushButton *okButton = new QPushButton("OK", this);
    /*
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    */
    formLayout->addRow(okButton);

    widget->setLayout(formLayout);

    setCentralWidget(widget);

    connect(okButton,&QPushButton::clicked, [=, &Members]()mutable{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Check", "Are you sure to send the money?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            if(sendMoney[0]->text().isEmpty())
            {
                QMessageBox::warning(this, "Warning", "You should fill account blank", QMessageBox::Yes );
                sendMoney[0]->clear();
                return;
            }
            else if(sendMoney[1]->text().isEmpty())
            {
                QMessageBox::warning(this, "Warning", "You should fill account blank", QMessageBox::Yes );
                sendMoney[1]->clear();
                return;
            }
            else{
                int send_money = sendMoney[1]->text().toInt();
                if(send_money > balance)
                {
                    QMessageBox::warning(this, "Warning", "Your balance is not enough to withdraw", QMessageBox::Yes );
                    sendMoney[1]->clear();
                    return;
                }
                else{
                    QString opponentAccount = sendMoney[0]->text();
                    bool find = false;
                    int i = 0;
                    for(; i <Members.size();i++)
                    {
                        if(opponentAccount == Members[i].get_account())
                        {
                            find = true;
                            break;
                        }
                    }
                    if(find == false)
                    {
                        QMessageBox::warning(this, "Warning", "Can't find account of opponent", QMessageBox::Yes );
                        sendMoney[0]->clear();
                        return;
                    }
                    else{
                        Members[i].modify_balance(send_money, 0);
                        balance -= send_money;
                        sendMoney[0]->clear();
                        sendMoney[1]->clear();
                        QMessageBox::information(this, "Success", "Complete your work!", QMessageBox::Ok);
                        return;
                    }
                }


            }
        }});
}
void MainWindow::exit(QVector<Member>& Members){
    qDebug()<< "exit";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Check", "Are you sure to want to exit?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // update
        int i =0;
        for(; i <Members.size();i++)
        {
            if(account == Members[i].get_account())
            {
                break;
            }
        }
        Members[i].modify_balance(balance ,1);
        save_data(Members);
        QApplication::closeAllWindows();
    }
    // 첫화면
}

void MainWindow::getInformation(QString name, QString ID, QString Password, QString account, int balance)
{
    this->name = name;
    this->ID = ID;
    this->Password = Password;
    this->account = account;
    this->balance = balance;
    QLabel* nothing = new QLabel;
    QLabel* name_screen = new QLabel;
    name_screen->setText("Welcome " + name);
    name_screen->setStyleSheet("QLabel { color : black; font : 18pt; font-family: 'Arial'; font-weight : 'bold'}");

    QLabel* greeting_screen = new QLabel;
    greeting_screen->setText("We are very happy to help you!");
    greeting_screen->setStyleSheet("QLabel { color : black; font : 12pt; font-family: 'Arial';}");

    QLabel* help_screen = new QLabel;
    help_screen->setText("How can I help you?");
    help_screen->setStyleSheet("QLabel { color : black; font : 12pt; font-family: 'Arial';}");



    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow(name_screen);
    formLayout->addRow(nothing);
    formLayout->addRow(greeting_screen);
    formLayout->addRow(nothing);
    formLayout->addRow(help_screen);

    //qDebug()<<name;

    QGroupBox *groupBox = new QGroupBox();
    groupBox->setLayout(formLayout);
    setCentralWidget(groupBox);
}


