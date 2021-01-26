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

#include <type_traits>

#include <QMap>
#include <QObject>
#include <exception>
#include <functional>
#include <spdlog/spdlog.h>

#include "Soc/Soc.hpp"
#include "Soc/SocModule.hpp"
#include "SocExplorerObject.hpp"


namespace SocExplorer
{

template <typename T>
const char* category()
{
    static_assert(std::is_base_of_v<SEObject, T>, "T must be derived from SEObject.");
    if constexpr (std::is_base_of_v<Soc, T>)
    {
        return "Soc";
    }
    if constexpr (std::is_base_of_v<SocModule, T>)
    {
        return "SocModule";
    }
    if constexpr (std::is_base_of_v<SEObject, T>)
    {
        return "SEObject";
    }
}

class SEObjectCtor_t
{
public:
    virtual SEObject* operator()(const QString& name, QObject* parent) const;
    virtual QString category() const { return SocExplorer::category<SEObject>(); };
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

        inline SEObject* new_object(const QString& category, const QString& factory_name,
            const QString& name, QObject* parent = nullptr);

        inline QStringList ctors() { return m_per_category_ctors[category<SEObject>()].keys(); }
        inline QStringList ctors(const QString& category);

        Q_SIGNAL void ctor_registered(SEObjectCtor_t*);

    private:
        QMap<QString, QMap<QString, SEObjectCtor_t*>> m_per_category_ctors;
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

    inline SEObject* new_object(const QString& category, const QString& factory_name,
        const QString& name, QObject* parent = nullptr);

    inline QStringList ctors();
    inline QStringList ctors(const QString& category);


    template <typename T>
    static inline T* new_object(
        const QString& factory_name, const QString& name, QObject* parent = nullptr)
    {
        return reinterpret_cast<T*>(details::FactorySingleton::instance().new_object(
            category<T>(), factory_name, name, parent));
    }

    Q_SIGNAL void ctor_registered(SEObjectCtor_t*);

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

inline SEObject* SocExplorerFactory::new_object(
    const QString& category, const QString& factory_name, const QString& name, QObject* parent)
{
    return _SX_FORWARD(new_object, category, factory_name, name, parent);
}

inline QStringList SocExplorerFactory::ctors()
{
    return _SX_FORWARD(ctors);
}

inline QStringList SocExplorerFactory::ctors(const QString& category)
{
    return _SX_FORWARD(ctors, category);
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
        if (ctor)
        {
            if (ctor->category() == "SEObject")
            {
                spdlog::critical(
                    "Registering a new ctor ({}) with unset category, this is likely an error",
                    name.toStdString());
            }
            else
            {
                m_per_category_ctors[ctor->category()][name] = ctor;
            }
            m_per_category_ctors["SEObject"][name] = ctor;
            emit ctor_registered(ctor);
        }
        else
        {
            spdlog::critical("Registering a new ctor ({}) with nullptr, this is likely an error",
                name.toStdString());
        }
    }

    inline SEObject* FactorySingleton::new_object(
        const QString& factory_name, const QString& name, QObject* parent)
    {
        static SEObjectCtor_t default_ctor;
        return (*m_per_category_ctors[category<SEObject>()].value(factory_name, &default_ctor))(
            name, parent);
    }

    inline SEObject* FactorySingleton::new_object(
        const QString& category, const QString& factory_name, const QString& name, QObject* parent)
    {
        static SEObjectCtor_t default_ctor;
        return (*m_per_category_ctors[category].value(factory_name, &default_ctor))(name, parent);
    }

    inline QStringList FactorySingleton::ctors(const QString& category)
    {
        return m_per_category_ctors[category].keys();
    }

}

}
