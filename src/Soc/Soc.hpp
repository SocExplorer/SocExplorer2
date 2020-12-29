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

class Soc : public SocExplorerObject
{
    Q_OBJECT
public:
    inline Endianness::Endianness endianness() const { return m_endianness; };

    QVariant value(const QString& key) const { return m_env[key]; }
    void set_value(const QString& key, QVariant value) { m_env[key] = std::move(value); }

    using SocExplorerObject::SocExplorerObject;
    virtual ~Soc() = default;

private:
    Endianness::Endianness m_endianness { Endianness::Endianness::unknown };
    QVariantMap m_env;
};
}
