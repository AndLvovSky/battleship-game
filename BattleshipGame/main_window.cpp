#include "main_window.h"
#include "ui_mainwindow.h"
#include "saving_manager.h"
#include "game_exception.h"
#include "field_widget.h"

#include <QPainter>
#include <QDir>

using namespace battleshipGame;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    savingManager = make_unique<SavingManager>(
        QDir::currentPath() + "/settings.txt");
    try {
        savingManager->load(Settings::getInstance());
    } catch(GameException ex) {
        QMessageLogger().debug(ex.what());
    }

    yourFW = new FieldWidget();
    opponentFW = new FieldWidget();
    ui->yourFleetLayout->addWidget(yourFW);
    ui->opponentFleetLayout->addWidget(opponentFW);
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
    QPalette palette;
    palette.setBrush(QPalette::Background, pixmap);
    cw->setAutoFillBackground(true);
    cw->setPalette(palette);
    QMainWindow::resizeEvent(e);
}

void MainWindow::on_settingsButton_clicked()
{
    auto& settings = Settings::getInstance();
    auto shipsMap = settings.getShipsMap();
    ui->d1SpinBox->setValue(shipsMap[1]);
    ui->d2SpinBox->setValue(shipsMap[2]);
    ui->d3SpinBox->setValue(shipsMap[3]);
    ui->d4SpinBox->setValue(shipsMap[4]);
    auto timeLimited = settings.isTimeLimited();
    ui->limitCheckBox->setChecked(timeLimited);
    ui->durationSpinBox->setEnabled(timeLimited);
    if (timeLimited) {
       ui->durationSpinBox->setValue(settings.getStepDuration());
    }
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(2);
}

void MainWindow::on_limitCheckBox_stateChanged(int checked)
{
    ui->durationSpinBox->setEnabled(checked);
}

void MainWindow::on_saveReturnButton_clicked()
{
    try {
        auto& settings = Settings::getInstance();
        int n1 = ui->d1SpinBox->value();
        int n2 = ui->d2SpinBox->value();
        int n3 = ui->d3SpinBox->value();
        int n4 = ui->d4SpinBox->value();
        settings.setShipsMap({{1, n1}, {2, n2}, {3, n3}, {4, n4}});
        auto timeLimited = ui->limitCheckBox->isChecked();
        settings.setTimeLimited(timeLimited);
        if (timeLimited) {
            settings.setStepDuration(ui->durationSpinBox->value());
        }
    } catch(GameException ex) {
       QMessageLogger().debug(ex.what());
    }
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(0);
}

void MainWindow::closeEvent(QCloseEvent* e) {
    try {
        savingManager->save(Settings::getInstance());
    } catch(GameException ex) {
         QMessageLogger().debug(ex.what());
    }
    QWidget::closeEvent(e);
}

void MainWindow::on_startGameButton_clicked()
{
    auto& game = BattleshipGame::get();
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(1);
    this->setFixedSize(600, 500);
    game.start();
}

void MainWindow::on_finishGameButton_clicked()
{
    BattleshipGame::get().quit();
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(0);
    this->setFixedSize(600, 400);
}
