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

class SEObjectCtor_t
{
public:
    virtual SEObject* operator()(const QString& name, QObject* parent) const;

    SEObjectCtor_t() { }
    virtual ~SEObjectCtor_t() {};
};


namespace details
{
    class FactorySingleton : public QObject
    {
        Q_OBJECT
        FactorySingleton(QObject* parent = nullptr) : QObject(parent) { }
        ~FactorySingleton() { }

    public:
        inline static FactorySingleton& instance();

        void register_ctor(const QString& name, SEObjectCtor_t* ctor);

        inline SEObject* new_object(
            const QString& factory_name, const QString& name, QObject* parent = nullptr);


    private:
        QMap<QString, SEObjectCtor_t*> m_ctors;
    };

}

#define _SX_FORWARD(name, ...) details::FactorySingleton::instance().name(__VA_ARGS__)

class SocExplorerFactory : public SEObject
{
    Q_OBJECT

public:
    inline void register_ctor(const QString& name, SEObjectCtor_t* ctor);

    inline SEObject* new_object(
        const QString& factory_name, const QString& name, QObject* parent = nullptr);

    SocExplorerFactory(QObject* parent = nullptr);
    ~SocExplorerFactory() { }
};


/*
 ===================================================================
         IMPLEMENTATION
 ===================================================================
 */
inline SEObject* SEObjectCtor_t::operator()(const QString& name, QObject* parent) const
{
    Q_UNUSED(name);
    Q_UNUSED(parent);
    return nullptr;
}

inline void SocExplorerFactory::register_ctor(const QString& name, SEObjectCtor_t* ctor)
{
    _SX_FORWARD(register_ctor, name, ctor);
}

inline SEObject* SocExplorerFactory::new_object(
    const QString& factory_name, const QString& name, QObject* parent)
{
    return _SX_FORWARD(new_object, factory_name, name, parent);
}

namespace details
{
    inline FactorySingleton& FactorySingleton::instance()
    {
        static FactorySingleton self;
        return self;
    }

    inline void FactorySingleton::register_ctor(const QString& name, SEObjectCtor_t* ctor)
    {
        m_ctors[name] = ctor;
    }

    inline SEObject* FactorySingleton::new_object(
        const QString& factory_name, const QString& name, QObject* parent)
    {
        static SEObjectCtor_t default_ctor;
        return (*m_ctors.value(factory_name, &default_ctor))(name, parent);
    }

}

}
