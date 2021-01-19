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
#include <QApplication>
#include <QObject>
#include <QtPlugin>
#include <bundled_plugins.hpp>

#if defined(socExplorerApp)
#undef socExplorerApp
#endif
#define socExplorerApp (static_cast<SqpApplication*>(QCoreApplication::instance()))

class SocExplorerApplication : public QApplication
{
    Q_OBJECT
public:
    explicit SocExplorerApplication(int& argc, char** argv) : QApplication(argc, argv)
    {
#ifdef QT_STATICPLUGIN

        Q_INIT_RESOURCE(python_providers);
#endif
        Q_IMPORT_PLUGIN(BundledPlugins);
        setOrganizationName("LPP");
        setOrganizationDomain("lpp.fr");
        setApplicationName("SocExplorer");
        QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    };
    ~SocExplorerApplication() override {};

private:
};

inline SocExplorerApplication* SocExplorerApplication_ctor()
{
    static int argc;
    static char** argv;
    return new SocExplorerApplication(argc, argv);
}
