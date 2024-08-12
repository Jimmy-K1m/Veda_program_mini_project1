#include <QVector>
#include <QGroupBox>
#include <QPushButton>
#include <QMessageBox>
#include <random>

#include "mainwindow_1.h"
#include "functiondata.h"


MainWindow_1::MainWindow_1(){}

MainWindow_1::MainWindow_1(QWidget *parent, QVector<Member>& Members)
    : QWidget(parent) {

    this->setWindowTitle("Sign Up Window");

    //Member::Member(QString ID, QString password, QString name, QString account)

    QLineEdit* lineEdit[3];
    QStringList labels;
    labels << "&NAME" << "&ID" << "&PASSWORD";
    QFormLayout *formLayout = new QFormLayout;


    lineEdit[0] = MakeLineEdit( 10, 0);
    lineEdit[1] = MakeLineEdit( 10, 0);
    lineEdit[2] = MakeLineEdit( 10, 1);
    QLabel* nameStatusLabel = new QLabel("Name should be English");
    QLabel* idStatusLabel = new QLabel("ID shouldn't be existed");
    QLabel* passwordStatusLabel = new QLabel("PW must contain special letters.");

    // nameStatusLabel->setWordWrap(true);
    // idStatusLabel->setWordWrap(true);
    // passwordStatusLabel->setWordWrap(true);

    formLayout->addRow(labels.at(0), lineEdit[0]);
    formLayout->addRow( nameStatusLabel);
    formLayout->addRow(labels.at(1), lineEdit[1]);
    formLayout->addRow(idStatusLabel);
    formLayout->addRow(labels.at(2), lineEdit[2]);
    formLayout->addRow( passwordStatusLabel);



    QPushButton* check = new QPushButton("&Complete");
    formLayout->addRow(check);


    QGroupBox *groupBox = new QGroupBox("&Assign", this);
    groupBox->move(5,5);
    groupBox->setLayout(formLayout);

    resize(groupBox->sizeHint().width()+10, groupBox->sizeHint().height()+10);


    connect(lineEdit[0], &QLineEdit::textChanged, [=](){
        int i = 0;
        for(; i <lineEdit[0]->text().size();i++)
        {
            if(lineEdit[0]->text().at(i).isLetter())
                continue;
            else
                break;
        }
        if(i < lineEdit[0]->text().size())
        {
            nameStatusLabel->setText("Name should be English");
            nameStatusLabel->setStyleSheet("QLabel { color : red; }");
        }
        else if(lineEdit[0]->text().isEmpty())
        {
            nameStatusLabel->setText("Name should be English");
            nameStatusLabel->setStyleSheet("QLabel { color : black; }");
        }
        else
        {
            nameStatusLabel->setText("Possible Name");
            nameStatusLabel->setStyleSheet("QLabel { color : green; }");
        }
    });


    connect(lineEdit[1], &QLineEdit::textChanged, [=](){
        int i = 0, j = 0;
        //for(; i < answer_ID.size(); i++)
        for(; i < Members.size(); i++)
        {
            //if(answer_ID[i] == lineEdit[0]->text())
            if((Members[i].get_ID()) == (lineEdit[1]->text()))
                break;
        }
        if(i!=Members.size())
        {
            //qDebug()<< "Impossible ID";
            idStatusLabel->setText("ID already taken");
            idStatusLabel->setStyleSheet("QLabel { color : red; }");
        }
        else if(lineEdit[1]->text().isEmpty())
        {
            idStatusLabel->setText("ID shouldn't be existed");
            idStatusLabel->setStyleSheet("QLabel { color : black; }");
        }
        else
        {
            qDebug()<< "Possible ID";
            idStatusLabel->setText("ID available");
            idStatusLabel->setStyleSheet("QLabel { color : green; }");
        }

    });

    connect(lineEdit[2], &QLineEdit::textChanged, [=](){
    QString specialCharacters = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/`~\\";
    bool containsSpecial = false;
    for(int i = 0; i <lineEdit[2]->text().size();i++)
    {
        if (specialCharacters.contains(lineEdit[2]->text().at(i))) {
            containsSpecial = true;
            break;
        }
    }
    if (containsSpecial) {
        passwordStatusLabel->setText("PW is strong.");
        passwordStatusLabel->setStyleSheet("QLabel { color : green; }");
    }
    else if(lineEdit[2]->text().isEmpty())
    {
        passwordStatusLabel->setText("PW must contain special letters.");
        passwordStatusLabel->setStyleSheet("QLabel { color : black; }");
    }
    else {
        passwordStatusLabel->setText("PW must contain special letters.");
        passwordStatusLabel->setStyleSheet("QLabel { color : red; }");
    }

    });



    connect(check, &QPushButton::clicked,[=]()mutable{
        bool allFilled = true;
        for(int i = 0; i < 3; i++)
        {
            if(lineEdit[i]->text().isEmpty())
            {
                allFilled = false;
                break;
            }
        }

        if(!allFilled)
        {
            QMessageBox::warning(this, "&Warning", "Please fill in all fields.");
            return;
        }

        bool notEnglish = false;
        for(int i =0 ; i <lineEdit[0]->text().size();i++)
        {
            if(lineEdit[0]->text().at(i).isLetter())
                continue;
            else
            {
                notEnglish = true;
                break;
            }
        }

        bool idExists = false;
        for(int i = 0; i < Members.size(); i++)
        {
            if(Members[i].get_ID() == lineEdit[1]->text())
            {
                idExists = true;
                break;
            }
        }

        bool containSpecial = false;
        QString specialCharacters = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/`~\\";
        for(int i = 0; i < lineEdit[2]->text().size();i++)
        {
            if(specialCharacters.contains(lineEdit[2]->text().at(i)))
            {
                containSpecial = true;
                break;
            }

        }

        if(idExists )
        {
            QMessageBox::warning(this, "&Error", "ID has already taken. Please choose another one.");
            return;
        }

        if(notEnglish)
        {
            QMessageBox::warning(this, "&Error", "Name should be english. Please type down correctly.");
            return;
        }
        if(!containSpecial)
        {
            QMessageBox::warning(this, "&Error", "Password should have special letters. Please choose another one.");
            return;
        }

        QString inputAccount;
        std::random_device rd; // 시드값 random_device 생성
        std::mt19937 gen(rd()); // 난수 생성 엔진 초기화
        std::uniform_int_distribution<int> dis(100000, 999999);
        while(1){
            int i = 0;
            inputAccount = "20240801-00-";
            inputAccount += QString::number(dis(gen));
            for( ; i < Members.size(); i++)
            {
                if(Members[i].get_account() == inputAccount)
                    break;
            }
            if(i >= Members.size())
                break;
        }


        Member m = Member(lineEdit[1]->text(), lineEdit[2]->text(), lineEdit[0]->text(), inputAccount, 0);
        Members.push_back(m);
        for(int i = 0 ; i < Members.size();i++)
            qDebug() << Members[i].get_ID();

        QMessageBox::about(this, "Complete Message", "Complete making an account");

        save_data(Members);
        for(int i = 0 ; i<3;i++)
            lineEdit[i]->clear();
        this->close();

    });
}
MainWindow_1::~MainWindow_1()
{
    qDebug() << "~MAinWinow_1";
}

QLineEdit* MainWindow_1::MakeLineEdit( int maxLength,int Mode)
{
    QLineEdit* temp = new QLineEdit;
    temp->setMaxLength(maxLength);
    if(Mode == 1)
        temp->setEchoMode(QLineEdit::Password);

    return temp;
}



