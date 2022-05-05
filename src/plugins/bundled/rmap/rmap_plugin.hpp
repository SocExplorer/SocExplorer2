/*------------------------------------------------------------------------------
--  This file is a part of the SocExplorer Software
--  Copyright (C) 2021, Plasma Physics Laboratory - CNRS
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
#pragma once
#include "Soc/SocModule.hpp"
#include "SocExplorerObject.hpp"
#include "rmappluginui.hpp"
#include <QObject>
#include <QtPlugin>

class _ZMQClient;

class RmapPlugin : public SocExplorer::SocModule
{
    Q_OBJECT
    RMAPPluginUi* m_ui = nullptr;
    _ZMQClient* m_client = nullptr;

    void connect_to_server(
        const QString& hostname, uint16_t requests_port, uint16_t subscribe_port);

    void disconnect_form_server();

public:
    RmapPlugin(const QString& name, QObject* parent = nullptr);

    virtual QWidget* ui() final;
    ;
};
