#ifndef WORKSPACEWIDGET_H
#define WORKSPACEWIDGET_H

#include <QMainWindow>

namespace Ui
{
class WorkspaceWidget;
}

namespace SocExplorer
{
class Workspace;
class SocModule;
}

class WorkspaceWidget : public QMainWindow
{
    Q_OBJECT

    void module_loaded(SocExplorer::SocModule* module);

public:
    explicit WorkspaceWidget(SocExplorer::Workspace* workspace, QWidget* parent = nullptr);
    ~WorkspaceWidget();

private:
    Ui::WorkspaceWidget* ui;
    SocExplorer::Workspace* m_workspace;
};

#endif // WORKSPACEWIDGET_H
