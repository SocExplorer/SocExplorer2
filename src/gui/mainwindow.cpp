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
#include "mainwindow.hpp"
#include "Soc/Soc.hpp"
#include "ui_mainwindow.h"
#include "workspacewidget.hpp"
#include <Factory/SocExplorerFactory.hpp>
#include <QAction>
#include <Workspaces/WorkspacesManager.hpp>
#include <strings/algorithms.hpp>

namespace SocExplorer
{
void MainWindow::update_soc_list()
{
    using namespace cpp_utils::strings;
    const auto socs = m_factory->ctors(category<Soc>());
    ui->newWorkspaceMenu->clear();
    for (const auto& soc : socs)
    {
        auto action = ui->newWorkspaceMenu->addAction(soc);

        connect(action, &QAction::triggered, [soc, this]() {
            const QString basename("Workspace");
            const auto workspaces = m_workspace_manager->workspaces();
            auto i = 1UL;
            while (workspaces.contains(basename + QString::number(i)))
            {
                i++;
            }
            m_workspace_manager->new_workspace(soc, basename + QString::number(i));
        });
    }
}

void MainWindow::workspace_created(Workspace* workspace)
{
    auto menu = ui->workspaceMenu->addMenu(workspace->name());
    ui->tabWidget->addTab(new WorkspaceWidget(workspace, this), workspace->name());
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    m_factory = new SocExplorerFactory(this);
    m_workspace_manager = new WorkspacesManager(this);
    ui->setupUi(this);
    update_soc_list();
    connect(m_factory, &SocExplorerFactory::ctor_registered, this, &MainWindow::update_soc_list);
    connect(m_workspace_manager, &WorkspacesManager::workspace_created, this,
        &MainWindow::workspace_created);
}

MainWindow::~MainWindow()
{
    delete ui;
}

}
