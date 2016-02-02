#include "record.h"
#include "data.h"
#include <QStringList>

Record::Record(QStringList *list, Data *data)
{
    if ( list == NULL || list->empty() || list->size() < 4 )
        return;
    id = (*list)[0];
    if (!data->all_ids.contains(id))
    {
        data->all_ids << id;
        data->cur_x++;
    }
    x = data->cur_x;
    chromosome = (*list)[1].toInt();
    bool ok;
    qint64 g_start = (*list)[2].toLongLong(&ok, 10);
    start = chromosomes[chromosome-1]+g_start;
    qint64 g_end = (*list)[3].toLongLong(&ok, 10);
    end = chromosomes[chromosome-1]+ g_end;
}
