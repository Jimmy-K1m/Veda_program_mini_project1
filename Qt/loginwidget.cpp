
#include <QLineEdit>
#include <QFormLayout>
#include <QWidget>
#include <QGroupBox>
#include <QVector>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>

#include "loginwidget.h"
#include "functiondata.h"

/**
 *
 * initial window which can connect to both sign up window and main banking system
 *
 */


LoginWidget::LoginWidget(){}
LoginWidget::LoginWidget(QWidget *parent, MainWindow* window, MainWindow_1* window_1)
    : QWidget(parent)
{
    read_data(Members);

    this->setWindowTitle("SignIn Window");

    // QVector<QString> answer_ID = {"test", "test1"};
    // QVector<QString> answer_password = {"1234", "1345"};
    QStringList labels;
    labels << "&ID" << "&PASSWORD";
    QLineEdit* lineEdit[2];
    QFormLayout *formLayout = new QFormLayout;
    for(int i = 0 ; i < 2; i++)
    {
        lineEdit[i] = new QLineEdit(this);
        lineEdit[i]->setMaxLength(10);
        if(i == 1)
            lineEdit[i]->setEchoMode(QLineEdit::Password);
        formLayout->addRow(labels.at(i), lineEdit[i]);
    }


    QGroupBox *groupBox = new QGroupBox("&Banking System", this);
    groupBox->setLayout(formLayout);

    resize(groupBox->sizeHint().width()+10, groupBox->sizeHint().height()+10);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(groupBox);

    // Set the main layout to the LoginWidget
    this->setLayout(mainLayout);
    QPushButton *loginButton = new QPushButton("Login", this);
    QPushButton *assignButton = new QPushButton("Sign Up", this);

    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(assignButton);
    //connect(lineEdit[0], &QLineEdit::textChanged, [=]()mutable{cout << string(lineEdit[0]->text());});
    QObject::connect(loginButton, &QPushButton::clicked, [=]()mutable{
        int i = 0, j = 0;
        for(; i < Members.size(); i++)
        {
            if(Members[i].get_ID() == lineEdit[0]->text())
                break;
        }

        if(i != Members.size())
        {
            if(Members[i].get_Password() == lineEdit[1]->text())
            {
                qDebug()<< "Complete";
                QMessageBox::information(this, "Assgin", "Are you sure you want to login?", QMessageBox::Ok);
                //getInformation(QString name, QString ID, QString Password, QString account, int balance)
                window->getInformation(Members[i].get_name(),Members[i].get_ID(),Members[i].get_Password(),Members[i].get_account(),Members[i].get_balance());
                window->setVisible(true);
                this->setVisible(false);
            }
            else
            {
                QMessageBox::warning(this, "Error", "Wrong ID or Password", QMessageBox::Ok);
                lineEdit[0]->clear();
                lineEdit[1]->clear();
                qDebug()<< "Fail login";
            }
        }
        else {

            QMessageBox::warning(this, "Error", "Wrong ID or Password", QMessageBox::Ok);
            lineEdit[0]->clear();
            lineEdit[1]->clear();
        }
    });

    QObject::connect(assignButton, &QPushButton::clicked, [=](){
        bool ok;
        QMessageBox::information(this, "Assign", "Do you want to join us?", QMessageBox::Ok);
        window_1->setVisible(true);
    });
    // 확인 창 만들기
}

LoginWidget::~LoginWidget() {
    qDebug() << "~LoginWidget";

}


