#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "saving_manager.h"
#include "field_widget.h"
#include "battleship_game.h"
#include <QMainWindow>
#include <memory>

using namespace battleshipGame;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void resizeEvent(QResizeEvent* e) override;
    void updateRadioGroup();

private slots:
    void on_settingsButton_clicked();

    void on_limitCheckBox_stateChanged(int arg1);

    void on_saveReturnButton_clicked();

    void closeEvent(QCloseEvent*) override;

    void on_startGameButton_clicked();

    void on_finishGameButton_clicked();

    void on_shipsMap_changed();

    void on_d1RadioButton_clicked();

    void on_d2RadioButton_clicked();

    void on_d3RadioButton_clicked();

    void on_d4RadioButton_clicked();

private:

    Ui::MainWindow *ui;
    FieldWidget* yourFW;
    FieldWidget* opponentFW;
    unique_ptr<SavingManager> savingManager;
    BattleshipGame* game;
};

#endif // MAINWINDOW_H
