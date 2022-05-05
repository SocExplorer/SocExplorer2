#include "workspacewidget.hpp"
#include "ui_workspacewidget.h"
#include <QDockWidget>
#include <Workspaces/Workspace.hpp>
#include <spdlog/spdlog.h>

void WorkspaceWidget::module_loaded(SocExplorer::SocModule* module)
{
    assert(module);
    if (module)
    {
        auto w = module->ui();
        spdlog::debug("Loading module {} UI", module->name().toStdString());
        if (w)
        {
            auto doc = new QDockWidget(this);
            doc->setAllowedAreas(Qt::AllDockWidgetAreas);
            doc->setWidget(w);
            this->addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea, doc);
            /*
             *     plugin->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->pluginsDockContainer->addDockWidget(Qt::TopDockWidgetArea,plugin);
    if(p_pluginGUIlist->count()!=0)
        this->pluginsDockContainer->tabifyDockWidget(p_pluginGUIlist->last(),plugin);
*/
        }
        else
        {
            spdlog::warn("Module {} has no UI", module->name().toStdString());
        }
    }
}

WorkspaceWidget::WorkspaceWidget(SocExplorer::Workspace* workspace, QWidget* parent)
        : QMainWindow(parent), ui(new Ui::WorkspaceWidget), m_workspace { workspace }
{
    ui->setupUi(this);
    connect(
        workspace, &SocExplorer::Workspace::module_loaded, this, &WorkspaceWidget::module_loaded);
}

WorkspaceWidget::~WorkspaceWidget()
{
    delete ui;
}
