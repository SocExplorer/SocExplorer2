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
#include "Workspace.hpp"
#include "Factory/SocExplorerFactory.hpp"
#include "hedley.h"

SocExplorer::SocModule* find_module(SocExplorer::SocModule* parent, const QString& module)
{
    if (parent->name() == module)
    {
        return parent;
    }
    else
    {
        for (auto child : parent->children())
        {
            auto m = find_module(child, module);
            if (m)
                return m;
        }
    }
    return nullptr;
}


SocExplorer::SocModule* SocExplorer::Workspace::find_module(const QString& module)
{
    return ::find_module(m_root_module, module);
}


HEDLEY_NON_NULL(2, 3)
void SocExplorer::Workspace::load_module(
    SocExplorer::SocModule* parent, SocExplorer::SocModule* module)
{
    module->setParent(parent);
    emit module_loaded(module);
}

void SocExplorer::Workspace::load_module(
    const QString& parent, const QString& module, const QString& name)
{
    auto p = find_module(parent);
    if (p)
    {
        auto m = SocExplorerFactory().new_object<SocExplorer::SocModule>(module, name, p);
        emit module_loaded(m);
    }
}
