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
#pragma once
#include <QObject>
#include <QWidget>

#include "Soc/Soc.hpp"
#include "Soc/SocModule.hpp"
#include "SocExplorerObject.hpp"

namespace SocExplorer
{
class Workspace : public SEObject
{
    Q_OBJECT
public:
    inline void set_root_module(SocModule* module) { m_root_module = module; }
    inline SocModule* root_module() { return m_root_module; }
    inline Soc* soc() { return m_soc; }

    Workspace(Soc* soc, const QString& name, QObject* parent = nullptr)
            : SEObject(name, parent), m_soc { soc }
    {
        soc->setParent(this);
    }
    ~Workspace() = default;

private:
    Soc* m_soc;
    SocModule* m_root_module { nullptr };
};
}
