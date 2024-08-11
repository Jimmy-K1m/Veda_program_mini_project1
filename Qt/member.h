#ifndef MEMBER_H
#define MEMBER_H
#include <QString>
#include <QMetaType>
class Member
{
protected:
    QString ID;
    QString password;
    QString name;
    QString account;
    int balance;
public:
    Member();
    Member(QString ID, QString password, QString name, QString account);
    Member(QString ID, QString password, QString name, QString account, int balance);
    QString makeInformation() const;
    QString get_ID () const;
    QString get_Password() const;
    QString get_name () const;
    QString get_account() const;
    int get_balance() const;
    void modify_balance(int Money, int Mode);
};

Q_DECLARE_METATYPE(Member)

#endif // MEMBER_H
