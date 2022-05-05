#ifndef RMAPPLUGINUI_H
#define RMAPPLUGINUI_H

#include <QWidget>

namespace Ui
{
class RMAPPluginUi;
}

class RMAPPluginUi : public QWidget
{
    Q_OBJECT

public:
    explicit RMAPPluginUi(QWidget* parent = nullptr);
    ~RMAPPluginUi();

    Q_SIGNAL void connect_to_server(
        const QString& hostname, uint16_t requests_port, uint16_t subscribe_port);

    Q_SIGNAL void diconnect_from_server();

    void setConnected(bool connected);

private:
    Ui::RMAPPluginUi* ui;
    bool connected = false;
};

#endif // RMAPPLUGINUI_H
