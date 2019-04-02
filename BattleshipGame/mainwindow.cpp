#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *e) {
    auto cw = ui->centralWidget;
    int w = cw->width();
    int h = cw->height();
    QPixmap pixmap;
    pixmap.load(":/images/main_background.jpg");
    pixmap = pixmap.scaled(w, h, Qt::IgnoreAspectRatio);
    QMessageLogger().debug(std::to_string(h).c_str());
    QPalette palette;
    palette.setBrush(QPalette::Background, pixmap);
    cw->setAutoFillBackground(true);
    cw->setPalette(palette);
    QMainWindow::resizeEvent(e);
}
