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
#include <QtPlugin>

#include <cstdint>
#include <vector>

#include "address.h"

namespace SocExplorer
{
class SocModule : public QObject
{
    Q_OBJECT
public:
    const uint64_t vid = -1;
    const uint64_t pid = -1;

    const QString& name() const { return m_name; }
    void set_name(const QString& name)
    {
        this->m_name = name;
        this->setObjectName(name);
        emit name_changed(m_name);
    }
    address64_t base_address() const { return m_base_address; }
    bool is_connected() const { return m_is_connected; }

    virtual uint64_t read(const address64_t address, std::size_t bytes, char* data);
    virtual uint64_t write(const address64_t address, std::size_t bytes, char* data);

    virtual QWidget* ui() { return nullptr; };

    SocModule* parent() const;
    std::vector<SocModule*> children() const;

    SocModule(const QString& name, QObject* parent = nullptr);
    virtual ~SocModule() { }

    Q_SIGNAL void name_changed(const QString& name);

private:
    QString m_name { "" };
    address64_t m_base_address { 0UL };
    bool m_is_connected { false };
};
}

namespace SocExplorer::Plugins
{
class ISocModule : public SocExplorer::SocModule
{
    Q_OBJECT
public:
    ISocModule(const QString& name, QObject* parent = nullptr)
            : SocExplorer::SocModule(name, parent)
    {
    }
    virtual ~ISocModule() { }
};
}
Q_DECLARE_INTERFACE(SocExplorer::Plugins::ISocModule, "socexplorer.plugins.SocModule")
