
#include "graphwidget.hpp"
#include "record.h"
#include "data.h"
#include <math.h>

#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QTextDocument>


//=========================================================================
void GraphWidget::setChartRectSize(int w, int h)
{
    chartRect = QRectF(0, 0, w, h);
    scene()->setSceneRect(-MARGIN, -MARGIN, chartRect.width()+2*MARGIN, chartRect.height()+2*MARGIN);
    PrepareScene();
}

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *s = new QGraphicsScene(this);
    s->setItemIndexMethod(QGraphicsScene::NoIndex);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setMinimumSize(400, 200);
    setWindowTitle(tr("Gene chart"));
    setDragMode(QGraphicsView::ScrollHandDrag);
    setScene(s);

    setChartRectSize(800, 800);
}

//=========================================================================
void GraphWidget::resizeEvent(QResizeEvent *e)
{
    QSize s = e->size();
    setChartRectSize(s.width()*0.8, s.height()*0.8);
    if ( !chartData.isEmpty() )
        showChart();
}

//=========================================================================
void GraphWidget::showChart()
{
    setHeader(chartData.header);
    QPen pen(Qt::lightGray);
    QBrush brush(Qt::transparent);
    for ( int i = 0; i < ppl_count; i++ )
    {
        qreal x1 = i*bar_width();
        scene()->addRect(chartRect.x()+x1, chartRect.y(), bar_width(), chartRect.height(), pen, brush);
    }
    for( int i = 0; i < chartData.size(); i++ )
        AddBarToScene(&chartData[i]);
}


//=========================================================================
qreal GraphWidget::bar_width()
{
    return (qreal)chartRect.width()/(qreal)ppl_count;
}

//=========================================================================
void GraphWidget::setHeader(QString &fileName)
{

    int idx = fileName.lastIndexOf('/');
    fileName = fileName.mid(idx+1);
    idx = fileName.indexOf('.');
    fileName = fileName.left(idx);
    QGraphicsTextItem *header = scene()->addText(fileName);
    header->document()->setDefaultTextOption(QTextOption(Qt::AlignCenter | Qt::AlignVCenter));
    QFont font;
    font.setPixelSize(25);
    font.setBold(true);
    header->setFont(font);
    QFontMetrics fm(font);
    header->setPos(chartRect.width()/2-fm.width(fileName)/2, -36);
}

//=========================================================================
void GraphWidget::PrepareScene(bool cleanData)
{
    if ( cleanData )
    {
        chartData.clear();
        ppl_count = 0;
    }
    scene()->clear();
    qreal dmax_rec = chartRect.height()/(qreal)MAX_REC;
    QPen pen(Qt::darkGray);
    QBrush brush(Qt::transparent);
    scene()->addRect(chartRect, pen, brush);
    for ( unsigned int i = 0; i < sizeof(chromosomes)/sizeof(qint64)-1; i++ )
    {
        qreal y1 = chartRect.height()-dmax_rec*(qreal)chromosomes[i];
        scene()->addLine(chartRect.left(), y1,chartRect.right(), y1, pen);
        QGraphicsTextItem *txt = scene()->addText(QString::number(i+1));
        txt->setPos(chartRect.left()-30, y1-16);
    }
}

//=========================================================================
void GraphWidget::AddBarToScene(Record *record)
{
    if ( record->chromosome <= 0 )
        return;
    qreal dmax_rec = chartRect.height()/(qreal)MAX_REC;
    QPen pen(Qt::black);
    QBrush brush(Qt::darkGray);
    qreal x = chartRect.x()+record->x*bar_width();
    qreal height = dmax_rec*(qreal)record->get_len();
    qreal y = chartRect.y()+chartRect.height()-dmax_rec*(qreal)record->end;
    qreal width = bar_width();
    scene()->addRect(QRectF(x, y, width, height), pen, brush);
}
