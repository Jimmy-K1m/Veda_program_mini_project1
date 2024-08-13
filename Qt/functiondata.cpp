#include <QDebug>
#include "functiondata.h"

#define url "C:\\Users\\dongjin\\Desktop\\mini_project\\first\\datatest.txt"


void read_data(QVector<Member>& Members) {
    QFile file(url);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can't open the file";
        return;
    }

    QTextStream in(&file);
    QString output;
    QString name_temp;
    QString ID_temp;
    QString password_temp;
    QString account_temp;
    int saved_money_temp;
    int i = 0;

    while (!in.atEnd()) {
        output = in.readLine();

        QStringList fields = output.split('|');  // '|'는 구분자

        for (const QString &temp : fields) {
            if (i == 0)
                ID_temp = temp;
            else if (i == 1)
                password_temp = temp;
            else if (i == 2)
                name_temp = temp;
            else if (i == 3)
                account_temp = temp;
            else {
                saved_money_temp = temp.toInt();
                i = -1;  // 모든 데이터를 다 읽었으므로, i 초기화
                Members.append(Member(ID_temp, password_temp, name_temp, account_temp, saved_money_temp));
            }
            i++;
        }
    }

    file.close();

}

void save_data(const QVector<Member>& input) {
    QFile file(url);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Can't open txt file";
        return;
    }

    QTextStream fout(&file);

    for (const auto& member : input) {
        fout << member.makeInformation() << "\n";
    }

    file.close();
}
