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
    //this->setFixedSize(600, 400);

    savingManager = make_unique<SavingManager>(
        QDir::currentPath() + "/settings.txt");
    try {
        savingManager->load(Settings::getInstance());
    } catch(GameException ex) {
        QMessageLogger().debug(ex.what());
    }

    yourFW = new FieldWidget(true);
    ui->yourFleetLayout->addWidget(yourFW);
    QObject::connect(yourFW, SIGNAL(shipsMapChanged()),
                     this, SLOT(on_shipsMap_changed()));
    opponentFW = new FieldWidget(false);
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
    auto atw = ui->actionStackedWidget;
    atw->setCurrentIndex(0);
    //this->setFixedSize(600, 500);
    game.start();
    on_shipsMap_changed();
}

void MainWindow::on_finishGameButton_clicked()
{
    BattleshipGame::get().quit();
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(0);
    //this->setFixedSize(600, 400);
}

void MainWindow::on_shipsMap_changed() {
    QMessageLogger().debug("ships map changed");
    auto d1 = ui->d1RadioButton;
    auto d2 = ui->d2RadioButton;
    auto d3 = ui->d3RadioButton;
    auto d4 = ui->d4RadioButton;
    auto& game = BattleshipGame::get();
    d1->setText(QString("single (") +
        QString::fromStdString(to_string(game.shipsLast[1])) + ")");
    d2->setText(QString("two (") +
        QString::fromStdString(to_string(game.shipsLast[2])) + ")");
    d3->setText(QString("three (") +
        QString::fromStdString(to_string(game.shipsLast[3])) + ")");
    d4->setText(QString("four (") +
        QString::fromStdString(to_string(game.shipsLast[4])) + ")");
    if (game.shipsLast[1] == 0) d1->setEnabled(false);
    else d1->setEnabled(true);
    if (game.shipsLast[2] == 0) d2->setEnabled(false);
    else d2->setEnabled(true);
    if (game.shipsLast[3] == 0) d3->setEnabled(false);
    else d3->setEnabled(true);
    if (game.shipsLast[4] == 0) d4->setEnabled(false);
    else d4->setEnabled(true);
    if (game.shipsLast[game.shipSize]) {
        switch (game.shipSize) {
            case 1: d1->setChecked(true); break;
            case 2: d2->setChecked(true); break;
            case 3: d3->setChecked(true); break;
            case 4: d4->setChecked(true); break;
        }
    } else {
        if (game.shipsLast[1] != 0) { d1->click(); yourFW->update(); }
        else if (game.shipsLast[2] != 0) { d2->click(); yourFW->update(); }
        else if (game.shipsLast[3] != 0) { d3->click(); yourFW->update(); }
        else if (game.shipsLast[4] != 0) { d4->click(); yourFW->update(); }
    }
    if (!(d1->isEnabled() || d2->isEnabled() || d3->isEnabled() || d4->isEnabled())) {
        game.mode = BattleshipGame::Mode::BATTLE;
        auto atw = ui->actionStackedWidget;
        atw->setCurrentIndex(1);
        QMessageLogger().debug("battle start");
    }
}

void MainWindow::on_d1RadioButton_clicked()
{
    BattleshipGame::get().shipSize = 1;
}

void MainWindow::on_d2RadioButton_clicked()
{
    BattleshipGame::get().shipSize = 2;
}

void MainWindow::on_d3RadioButton_clicked()
{
    BattleshipGame::get().shipSize = 3;
}

void MainWindow::on_d4RadioButton_clicked()
{
    BattleshipGame::get().shipSize = 4;
}
