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


namespace SocExplorer
{

class SEObject : public QObject
{
    Q_OBJECT
public:
    SEObject(QObject* parent = nullptr) : QObject(parent) { }
    SEObject(const QString& name, QObject* parent = nullptr) : QObject(parent)
    {
        set_name(name);
    }

    QString name() const { return objectName(); }
    void set_name(const QString& name)
    {
        this->setObjectName(name);
        emit name_changed(name);
    }

    Q_SIGNAL void name_changed(const QString& name);
};
}
