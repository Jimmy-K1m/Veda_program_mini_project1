#include "member.h"
#include <QVector>



Member::Member() {}
Member::Member(QString ID, QString password, QString name, QString account){
    this->ID = ID;
    this->password = password;
    this->name = name;
    this->account = account;
    this->balance = 0;
}
Member::Member(QString ID, QString password, QString name, QString account, int balance){
    this->ID = ID;
    this->password = password;
    this->name = name;
    this->account = account;
    this->balance = balance;
}

QString Member::makeInformation() const{
    return ID + "|" + password + "|" + name + "|" + account + "|" + QString::number(balance);
}


QString Member::get_ID()const{
    return ID;
}

QString Member::get_Password() const{
    return password;
}

QString Member::get_name()const{
    return name;
}

QString Member::get_account() const{
    return account;
}

int Member::get_balance() const{
    return balance;
}
void Member::modify_balance(int Money, int Mode){
    if(Mode == 0)
    {
        balance += Money;
        return;
    }
    else
    balance = Money;

}

//QString Mem
