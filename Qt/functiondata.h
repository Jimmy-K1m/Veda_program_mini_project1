#ifndef FUNCTIONDATA_H
#define FUNCTIONDATA_H
#include <QVector>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include "member.h"

void read_data(QVector<Member>& Members);
void save_data(const QVector<Member>& input);
#endif // FUNCTIONDATA_H
