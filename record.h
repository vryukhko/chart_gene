#ifndef RECORD
#define RECORD

#include <QString>
#define MAX_REC 2881000000UL
class QStringList;
class Data;

static qint64 chromosomes[] = {0,
                       249300000,
                       492500000,
                       690500000,
                       881700000,
                       1062600000,
                       1233700000,
                       1392800000,
                       1539200000,
                       1680400000,
                       1815900000,
                       1950900000,
                       2084800000,
                       2200000000UL,
                       2307300000UL,
                       2409800000UL,
                       2500200000UL,
                       2581400000UL,
                       2659500000UL,
                       2718600000UL,
                       2781600000UL,
                       2829700000UL,
                       2881000000UL,
    //                   3036300000UL,
};

struct Record
{
    Record(QStringList *list, Data *data);
    int x;
    QString id;
    int chromosome;
    qint64 start;
    qint64 end;

    int get_len()
    {
        int l = end - start;
        return l;
    }
};

#endif // RECORD

