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

#include <QMap>
#include <QObject>
#include <functional>

#include "SocExplorerObject.hpp"


namespace SocExplorer
{

class Soc;
class SocCtor_t
{
public:
    SocCtor_t() { }
    virtual ~SocCtor_t() {};
    virtual Soc* operator()(const QString& name, QObject* parent) const
    {
        Q_UNUSED(name);
        Q_UNUSED(parent);
        return nullptr;
    };
};

namespace details
{
    class FactorySingleton : public QObject
    {
        Q_OBJECT
        FactorySingleton(QObject* parent = nullptr) : QObject(parent) { }
        ~FactorySingleton() { }

    public:
        inline static FactorySingleton& instance()
        {
            static FactorySingleton self;
            return self;
        }

        void register_soc_ctor(const QString& name, SocCtor_t* ctor) { m_socs[name] = ctor; }
        inline Soc* new_soc(
            const QString& factory_name, const QString& name, QObject* parent = nullptr)
        {
            static SocCtor_t default_soc;
            return (*m_socs.value(factory_name, &default_soc))(name, parent);
        }

    private:
        QMap<QString, SocCtor_t*> m_socs;
    };
}

#define _SX_FORWARD(name, ...) details::FactorySingleton::instance().name(__VA_ARGS__)

class SocExplorerFactory : public SocExplorerObject
{
    Q_OBJECT

public:
    SocExplorerFactory(QObject* parent = nullptr);
    ~SocExplorerFactory() { }
    inline void register_soc_ctor(const QString& name, SocCtor_t* ctor)
    {
        _SX_FORWARD(register_soc_ctor, name, ctor);
    }
    inline Soc* new_soc(const QString& factory_name, const QString& name, QObject* parent = nullptr)
    {
        return _SX_FORWARD(new_soc, factory_name, name, parent);
    }
};

}
