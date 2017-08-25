#include "testdialog.h"
#include "ui_testdialog.h"
#include "message.h"
#include "global_constant.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

using namespace LibGUI;
using namespace LibG;

TestDialog::TestDialog(LibG::MessageBus *bus, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestDialog),
    mTimerBuy(new QTimer(this)),
    mTimerSell(new QTimer(this))
{
    ui->setupUi(this);
    setMessageBus(bus);
    //connect(mTimerBuy, SIGNAL(timeout()), SLOT(executeBuy()));
    connect(mTimerSell, SIGNAL(timeout()), SLOT(executeSell()));
    mTimerBuy->setSingleShot(true);
    mTimerSell->setSingleShot(true);
    connect(ui->pushStart, SIGNAL(clicked(bool)), SLOT(startStopClicked()));
    connect(ui->pushClose, SIGNAL(clicked(bool)), SLOT(closeClicked()));
}

TestDialog::~TestDialog()
{
    delete ui;
}

void TestDialog::messageReceived(LibG::Message *msg)
{
    if(msg->isTypeCommand(MSG_TYPE::PURCHASE, MSG_COMMAND::INSERT)) {
        auto json = QJsonDocument::fromJson(ui->plainBuy->toPlainText().toUtf8()).object();
        auto arr = json.value("data2").toArray();
        for(int i = 0; i < arr.size(); i++) {
            Message message(MSG_TYPE::PURCHASE_ITEM, MSG_COMMAND::INSERT);
            QVariantMap m = arr[i].toObject().toVariantMap();
            m.insert("purchase_id", msg->data("id").toInt());
            message.setData(m);
            sendMessage(&message);
        }
    } else if(msg->isTypeCommand(MSG_TYPE::PURCHASE_ITEM, MSG_COMMAND::INSERT)) {
        mTimerBuy->start();
    } else if(msg->isTypeCommand(MSG_TYPE::SOLD, MSG_COMMAND::NEW_SOLD)) {
        mTimerSell->start();
    }
}

void TestDialog::executeBuy()
{
    auto json = QJsonDocument::fromJson(ui->plainBuy->toPlainText().toUtf8()).object();
    Message msg(MSG_TYPE::PURCHASE, MSG_COMMAND::INSERT);
    msg.setData(json.value("data1").toObject().toVariantMap());
    sendMessage(&msg);
}

void TestDialog::executeSell()
{
    auto json = QJsonDocument::fromJson(ui->plainSell->toPlainText().toUtf8()).object();
    Message msg(MSG_TYPE::SOLD, MSG_COMMAND::NEW_SOLD);
    msg.setData(json.value("data").toObject().toVariantMap());
    sendMessage(&msg);
}

void TestDialog::startStopClicked()
{
    if(mIsStarted) {
        mTimerBuy->stop();
        mTimerSell->stop();
        ui->pushStart->setText(tr("Start"));
    } else {
        mTimerBuy->setInterval(ui->spinBuy->value() * 1000);
        mTimerSell->setInterval(ui->spinSell->value() * 1000);
        mTimerBuy->start();
        mTimerSell->start();
        ui->pushStart->setText(tr("Stop"));
    }
    mIsStarted = !mIsStarted;
}

void TestDialog::closeClicked()
{
    mTimerBuy->stop();
    mTimerSell->stop();
    close();
}
