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
#include <QObject>

#include "Factory/SocExplorerFactory.hpp"
#include "SocExplorerObject.hpp"
#include "Workspace.hpp"

namespace SocExplorer
{
namespace details
{
    class WorkspacesManager : public QObject
    {
        Q_OBJECT
        WorkspacesManager();
        ~WorkspacesManager() = default;

    public:
        inline Workspace* new_workspace(Soc* soc, const QString& name)
        {
            auto w = new Workspace(soc, name, this);
            m_workspaces[name] = w;
            emit workspace_created(w);
            return w;
        }

        static WorkspacesManager& instance()
        {
            static WorkspacesManager self;
            return self;
        }

        inline QStringList workspaces() { return m_workspaces.keys(); }

        inline Workspace* workspace(const QString& name) { return m_workspaces[name]; }

        Q_SIGNAL void workspace_created(Workspace*);

    private:
        QMap<QString, Workspace*> m_workspaces;
    };
}

class WorkspacesManager : public SEObject
{
    Q_OBJECT
public:
    inline Workspace* new_workspace(Soc* soc, const QString& name)
    {
        return details::WorkspacesManager::instance().new_workspace(soc, name);
    }

    inline Workspace* new_workspace(const QString& soc, const QString& name)
    {
        return new_workspace(reinterpret_cast<Soc*>(SocExplorerFactory().new_object(
                                 category<Soc>(), soc, name + "_soc")),
            name);
    }

    inline QStringList workspaces() { return details::WorkspacesManager::instance().workspaces(); }
    inline Workspace* workspace(const QString& name)
    {
        return details::WorkspacesManager::instance().workspace(name);
    }

    Q_SIGNAL void workspace_created(Workspace*);

    WorkspacesManager(QObject* parent = nullptr);
    ~WorkspacesManager() { }

private:
};
}
