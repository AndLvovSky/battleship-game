#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "saving/saving_manager.h"
#include "widgets/field_widget.h"
#include "models/battleship_game.h"
#include <QMainWindow>
#include <memory>

using namespace battleshipGame;

namespace Ui {
    class MainWindow;
}

/**
 * @brief The MainWindow class contains controller logic
 * and manages all widgets.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * Explicit constructor from QMainWindow.
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /**
      * Overrided destructor.
      */
    ~MainWindow() override;

    /**
     * Handler of resize event.
     */
    void resizeEvent(QResizeEvent*) override;

signals:
    /**
     * Signal that emits when player fired a valid square.
     * @param fireResult - result of the fire.
     */
    void fired(FireResult fireResult);

    /**
      * Signal that emits when got winner.
      * @param youWon - is you winner.
      */
    void gotWinner(bool youWon);

private slots:
    /**
     * Slot for button click.
     */
    void on_settingsButton_clicked();

    /**
     * Slot for time limit checkbox change.
     */
    void on_limitCheckBox_stateChanged(int);

    /**
     * Slot for save button click.
     */
    void on_saveReturnButton_clicked();

    /**
     * Overrided slot for close window.
     */
    void closeEvent(QCloseEvent*) override;

    /**
     * Slot for start game button click.
     */
    void on_startGameButton_clicked();

    /**
     * Slot for finish game button click.
     */
    void on_finishGameButton_clicked();

    /**
     * Slot for radio button for single-decks ships click.
     */
    void on_d1RadioButton_clicked();

    /**
     * Slot for radio button for two-decks ships click.
     */
    void on_d2RadioButton_clicked();

    /**
     * Slot for radio button for three-decks ships click.
     */
    void on_d3RadioButton_clicked();

    /**
     * Slot for radio button for four-decks ships click.
     */
    void on_d4RadioButton_clicked();

    /**
     * Slot for opponent step.
     */
    void on_opponentStep();

    /**
     * Slot for human time left.
     */
    void on_yourTimeLeft();

    /**
     * Slot for restart button click.
     */
    void on_restartButton_clicked();

    /**
     * Slot for adding new a ship to human fleet.
     */
    void on_shipsMap_changed();

    /**
     * Slot for firing square.
     * @param fireResult - result of the fire.
     */
    void on_fired(FireResult fireResult);

    /**
     * Slot for getting winner.
     * @param youWon - is you winner.
     */
    void on_gotWinner(bool youWon);

private:
    Ui::MainWindow *ui; /**< autogenerated user interface */
    FieldWidget* yourFW; /**< human field widget */
    FieldWidget* opponentFW; /** machine field widget */
    unique_ptr<SavingManager> savingManager; /**< saving manager */
    QTimer* yourTimer; /** human timer */
    QTimer* opponentTimer; /** machine timer */
    int timeLeft; /** human's time left in seconds */
};

#endif // MAINWINDOW_H
