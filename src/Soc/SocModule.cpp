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

#include "SocModule.hpp"
#include "Workspace.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

SocExplorer::Workspace* workspace(SocExplorer::SocModule* module)
{
    if (module)
    {
        auto parent = module->parent();
        auto w = qobject_cast<SocExplorer::Workspace*>(parent);
        while (parent && !w)
        {
            parent = parent->parent();
            w = qobject_cast<SocExplorer::Workspace*>(parent);
        }
        return w;
    }
    return nullptr;
}

uint64_t SocExplorer::SocModule::read(
    const address64_t address, std::size_t bytes, char* data) const
{
    auto p = parent();
    if (p)
    {
        return p->read(address, bytes, data);
    }
    return 0UL;
}

uint64_t SocExplorer::SocModule::write(
    const address64_t address, std::size_t bytes, char* data) const
{
    auto p = parent();
    if (p)
    {
        return p->write(address, bytes, data);
    }
    return 0UL;
}

SocExplorer::SocModule* SocExplorer::SocModule::parent() const
{
    return qobject_cast<SocModule*>(QObject::parent());
}

std::vector<SocExplorer::SocModule*> SocExplorer::SocModule::children() const
{
    using namespace ranges::views;
    return QObject::children()
        | transform([](QObject* qobject) { return qobject_cast<SocModule*>(qobject); })
        | remove_if([](SocModule* plugin) { return plugin == nullptr; }) | ranges::to<std::vector>;
}

SocExplorer::SocModule::SocModule(const QString& name, QObject* parent) : SEObject(name, parent)
{
    if (auto w = workspace(this); w)
        m_soc = w->soc();
    else
    {
        spdlog::critical(
            "{}, SocModule created without Workspace as top parent", name.toStdString());
    }
}
