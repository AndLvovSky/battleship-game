#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "saving_manager.h"
#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent* e) override;

private slots:
    void on_settingsButton_clicked();

    void on_limitCheckBox_stateChanged(int arg1);

    void on_saveReturnButton_clicked();

    void closeEvent(QCloseEvent*) override;

private:
    Ui::MainWindow *ui;
    unique_ptr<battleshipGame::SavingManager> savingManager;
};

#endif // MAINWINDOW_H
