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

#include <cstdint>
#include <vector>

#include <range/v3/view.hpp>

#include "Soc.hpp"
#include "SocExplorerObject.hpp"
#include "address.h"
#include "endianness.hpp"

namespace SocExplorer
{
class SocModule : public SEObject
{
    Q_OBJECT
public:
    const uint64_t vid = -1;
    const uint64_t pid = -1;

    address64_t base_address() const { return m_base_address; }
    bool is_connected() const { return m_is_connected; }

    virtual uint64_t read(const address64_t address, std::size_t bytes, char* data) const;
    virtual uint64_t write(const address64_t address, std::size_t bytes, char* data) const;

    template <typename container_t>
    uint64_t write(const address64_t address, const container_t&& data) const
    {
        using value_type = typename container_t::value_type;
        if (m_soc->endianness() != Endianness::host_endianness_v())
        {
            Endianness::details::byte_swap(
                reinterpret_cast<value_type*>(data.data()), std::size(data));
        }
        const auto value_size = sizeof(value_type);
        return write(address, value_size * std::size(data), data.data());
    }

    template <typename value_t>
    bool memSet(address64_t address, value_t value, std::size_t count)
    {
        auto buffer = ranges::views::repeat_n(value, count);
        this->write(address, buffer);
        return true;
    }

    virtual QWidget* ui() { return nullptr; };

    std::vector<SocModule*> children() const;

    SocModule(const QString& name, QObject* parent = nullptr);

    virtual ~SocModule() { }

private:
    Soc* m_soc { nullptr };
    address64_t m_base_address { 0UL };
    bool m_is_connected { false };
};
}
