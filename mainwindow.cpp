#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QGraphicsTextItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gwidget = new GraphWidget(this);
    setCentralWidget(gwidget);
    ui->action_SaveImage->setEnabled(false);
    ui->action_OpenFile->trigger();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open data file"));
    if ( fileName.isEmpty() )
        return;
    QFile textFile(fileName);
    QTextStream in(&textFile);
    QString line;
    if ( textFile.open(QIODevice::ReadOnly|QIODevice::Text) )
    {
        gwidget->PrepareScene(true);
        int x = -1;
        do
        {
            line = in.readLine();
            if ( line == NULL || line.isEmpty() )
                continue;
            QStringList list = line.split("\t", QString::SkipEmptyParts);
            if ( list.isEmpty() || list.size() < 4 )
                continue;
            Record r(&list, &gwidget->chartData);
            if ( x != r.x )
            {
                x = r.x;
                gwidget->ppl_count++;
            }
            gwidget->chartData.addRecord(r);

        }
        while (!line.isNull());
        textFile.close();
        gwidget->chartData.header = fileName;
        gwidget->showChart();
        ui->action_SaveImage->setEnabled(true);
    }
}

void MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save image as"), QString(), "*.png");
    if ( fileName.isEmpty() )
        return;
    if ( fileName.indexOf('.') < 0 )
        fileName.append(".png");
    QImage image(gwidget->scene()->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
    image.fill(Qt::transparent);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    gwidget->scene()->render(&painter);
    image.save(fileName, "PNG");
}
