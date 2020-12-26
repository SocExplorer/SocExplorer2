/*------------------------------------------------------------------------------
███████╗ ██████╗  ██████╗    ███████╗██╗  ██╗██████╗ ██╗      ██████╗ ██████╗ ███████╗██████╗
██╔════╝██╔═══██╗██╔════╝    ██╔════╝╚██╗██╔╝██╔══██╗██║     ██╔═══██╗██╔══██╗██╔════╝██╔══██╗
███████╗██║   ██║██║         █████╗   ╚███╔╝ ██████╔╝██║     ██║   ██║██████╔╝█████╗  ██████╔╝
╚════██║██║   ██║██║         ██╔══╝   ██╔██╗ ██╔═══╝ ██║     ██║   ██║██╔══██╗██╔══╝  ██╔══██╗
███████║╚██████╔╝╚██████╗    ███████╗██╔╝ ██╗██║     ███████╗╚██████╔╝██║  ██║███████╗██║  ██║
╚══════╝ ╚═════╝  ╚═════╝    ╚══════╝╚═╝  ╚═╝╚═╝     ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝

--  This file is a part of the SOC Explorer Software
--  Copyright (C) 2018, Plasma Physics Laboratory - CNRS
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
#ifndef ADDRESS_H
#define ADDRESS_H
#include <opaque/numeric_typedef.hpp>
#include <stdint.h>

/**
 * Taken from https://sourceforge.net/p/opaque-typedef/wiki/Home/
 * This exactly what we want
 */

template <typename T>
struct offset_t : opaque::numeric_typedef<T, offset_t<T>> {
  using base  = opaque::numeric_typedef<T, offset_t<T>>;
  using base::base;
};

template <typename T>
struct address_t : opaque::numeric_typedef_base<T, address_t<T>>
  , opaque::binop::addable     <address_t<T>, true , address_t<T>,  offset_t<T>>
  , opaque::binop::addable     <address_t<T>, true ,  offset_t<T>, address_t<T>>
  , opaque::binop::subtractable<address_t<T>, false, address_t<T>,  offset_t<T>>
  , opaque::binop::subtractable<offset_t<T> , false, address_t<T>, address_t<T>, T, T>
{
  using base   = opaque::numeric_typedef_base<T, address_t<T>>;
  using base::base;
  address_t& operator*=(const address_t&) = delete;
  address_t& operator+=(const address_t&) = delete;
  address_t& operator-=(const address_t&) = delete;
  address_t& operator+=(const offset_t<T>& o) {
    this->value += o.value;
    return *this;
  }
  address_t& operator-=(const offset_t<T>& o) {
    this->value -= o.value;
    return *this;
  }
};

using offset64_t = offset_t<uint64_t>;
using address64_t = address_t<uint64_t>;

#endif //ADDRESS_H
