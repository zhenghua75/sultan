#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include "messagehandler.h"
#include "message.h"
#include <QDialog>
#include <QTimer>

namespace Ui {
class TestDialog;
}

namespace LibGUI {

class TestDialog : public QDialog, public LibG::MessageHandler
{
    Q_OBJECT

public:
    TestDialog(LibG::MessageBus *bus, QWidget *parent = 0);
    ~TestDialog();

protected:
    void messageReceived(LibG::Message *msg) override;

private:
    Ui::TestDialog *ui;
    bool mIsStarted = false;
    QTimer *mTimerBuy;
    QTimer *mTimerSell;

private slots:
    void executeBuy();
    void executeSell();
    void startStopClicked();
    void closeClicked();
};

}

#endif // TESTDIALOG_H
