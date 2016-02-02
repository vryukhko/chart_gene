#ifndef DATA
#define DATA

#include "record.h"
#include <QList>

class Data: public QList<Record>
{
public:
    QString header;
    QStringList all_ids;
    int cur_x;
    void addRecord(Record &record)
    {
        append(record);
    }
    virtual void clear()
    {
        all_ids.clear();
        cur_x = -1;
        QList<Record>::clear();
    }
};

#endif // DATA

