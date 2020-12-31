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
#include "SocExplorerObject.hpp"
#include <QObject>
#include <QVariantMap>
#include <endianness.hpp>

namespace SocExplorer
{

enum class BusSize
{
    sUnknown = 0,
    s8 = 1,
    s16 = 2,
    s32 = 4,
    s64 = 8
};

class Soc : public SEObject
{
    Q_OBJECT
public:
    inline Endianness::Endianness endianness() const { return m_endianness; };

    inline BusSize data_width() { return m_data_width; }
    inline BusSize address_width() { return m_address_width; }

    QVariant value(const QString& key) const { return m_env[key]; }
    void set_value(const QString& key, QVariant value) { m_env[key] = std::move(value); }

    Soc(const QString& name, QObject* parent = nullptr) : SEObject(name, parent) { }
    virtual ~Soc() = default;

private:
    Endianness::Endianness m_endianness { Endianness::Endianness::unknown };
    QVariantMap m_env;
    BusSize m_data_width = BusSize::sUnknown;
    BusSize m_address_width = BusSize::sUnknown;
};
}
