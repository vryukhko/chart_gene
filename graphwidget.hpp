#ifndef GRAPHWIDGET_HPP
#define GRAPHWIDGET_HPP

#include <QGraphicsView>
#include "record.h"
#include "data.h"

#define MARGIN 50
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    Data chartData;
    GraphWidget(QWidget *parent = 0);
    void AddBarToScene(Record *record);
    void PrepareScene(bool cleanData=false);
    QRectF chartRect;
    int ppl_count;
    qreal bar_width();

    void showChart();


    void setHeader(QString &fileName);
    void setChartRectSize(int w, int h);
    virtual void resizeEvent(QResizeEvent *e);
};
#endif // GRAPHWIDGET_HPP

