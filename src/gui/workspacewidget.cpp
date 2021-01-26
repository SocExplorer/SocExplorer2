#include "workspacewidget.hpp"
#include "ui_workspacewidget.h"
#include <Workspaces/Workspace.hpp>

WorkspaceWidget::WorkspaceWidget(SocExplorer::Workspace* workspace, QWidget* parent)
        : QMainWindow(parent), ui(new Ui::WorkspaceWidget), m_workspace { workspace }
{
    ui->setupUi(this);
}

WorkspaceWidget::~WorkspaceWidget()
{
    delete ui;
}
