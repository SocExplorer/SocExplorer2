#include "rmappluginui.hpp"
#include "ui_rmappluginui.h"
#include <QPushButton>

RMAPPluginUi::RMAPPluginUi(QWidget* parent) : QWidget(parent), ui(new Ui::RMAPPluginUi)
{
    ui->setupUi(this);
    connect(ui->connectQpb, &QPushButton::clicked, [this]() {
        if (connected)
        {
            emit this->diconnect_from_server();
        }
        else
        {
            emit this->connect_to_server(
                ui->hostname->text(), ui->req_port->text().toInt(), ui->sub_port->text().toInt());
        }
    });
}

RMAPPluginUi::~RMAPPluginUi()
{
    delete ui;
}

void RMAPPluginUi::setConnected(bool connected)
{
    this->connected = connected;
    if (connected)
        ui->connectQpb->setText("Disonnect");
    else
        ui->connectQpb->setText("Connect");
}
