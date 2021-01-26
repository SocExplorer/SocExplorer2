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
#include "SocExplorerApp.hpp"
#include <Factory/SocExplorerFactory.hpp>
#include <QPluginLoader>
#include <plugin/IFactory.hpp>
#include <spdlog/spdlog.h>

void SocExplorerApplication::load_static_plugins()
{
    using namespace SocExplorer;
    auto static_plugins = QPluginLoader::staticPlugins();
    for (const auto& plugin : static_plugins)
    {
        auto inst = plugin.instance();
        spdlog::info("Found static plugin: {}", inst->metaObject()->className());
        auto asIFactory = qobject_cast<Plugins::IFactory*>(inst);
        if (asIFactory)
        {
            spdlog::info("{} is an IFactory", inst->metaObject()->className());
            SocExplorerFactory sfactory;
            auto factories = asIFactory->factories();
            for (const auto& factory : factories)
            {
                sfactory.register_ctor(factory.first, factory.second);
                spdlog::info("{}: registering ctor={}", inst->metaObject()->className(),
                    factory.first.toStdString());
            }
        }
    }
}
