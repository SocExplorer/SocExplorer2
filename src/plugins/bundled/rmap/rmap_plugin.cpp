/*------------------------------------------------------------------------------
--  This file is a part of the SocExplorer Software
--  Copyright (C) 2020, Plasma Physics Laboratory - CNRS
--
--  This program is free software; you can redistribute it and/or modify
--  it under the terms of the GNU General Public License as published by
--  the Free Software Foundation; either version 2 of the License, or
--  (at your option) any later version.
--
--  This program is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU General Public License for more details.
--
--  You should have received a copy of the GNU General Public License
--  along with this program; if not, write to the Free Software
--  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
-------------------------------------------------------------------------------*/
/*--                  Author : Alexis Jeandet
--                     Mail : alexis.jeandet@lpp.polytechnique.fr
----------------------------------------------------------------------------*/
#include "rmap_plugin.hpp"
#include <ZMQClient.hpp>
#include <spdlog/spdlog.h>

using ZMQClient_t
    = decltype(ZMQClient { { topics::types::RMAP }, {}, topic_policy::merge_all_topics {} });

class _ZMQClient : public ZMQClient_t
{
    using ZMQClient_t::ZMQClient_t;
};

void RmapPlugin::connect_to_server(
    const QString& hostname, uint16_t requests_port, uint16_t subscribe_port)
{
    spdlog::debug("RmapPlugin: connecting to server");
    if (m_client)
        delete m_client;
    Config cfg;
    cfg["address"] = hostname.toStdString();
    cfg["pub_port"] = int(subscribe_port);
    cfg["req_port"] = int(requests_port);
    m_client = new _ZMQClient { { topics::types::RMAP }, cfg, topic_policy::merge_all_topics {} };
    if (m_ui)
        m_ui->setConnected(true);
}

void RmapPlugin::disconnect_form_server()
{
    spdlog::debug("RmapPlugin: disconnecting from server");
    if (m_client)
        delete m_client;
    if (m_ui)
        m_ui->setConnected(false);
}

RmapPlugin::RmapPlugin(const QString& name, QObject* parent) : SocExplorer::SocModule(name, parent)
{
}

QWidget* RmapPlugin::ui()
{
    if (!m_ui)
    {
        m_ui = new RMAPPluginUi;
        connect(m_ui, &RMAPPluginUi::connect_to_server, this, &RmapPlugin::connect_to_server);
        connect(
            m_ui, &RMAPPluginUi::diconnect_from_server, this, &RmapPlugin::disconnect_form_server);
    }
    return m_ui;
}
