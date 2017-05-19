/*
 * purchaseaction.cpp
 * Copyright 2017 - ~, Apin <apin.klas@gmail.com>
 *
 * This file is part of Turbin.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "purchaseaction.h"
#include "db.h"

using namespace LibServer;
using namespace LibDB;

PurchaseAction::PurchaseAction():
    ServerAction("purchases", "id")
{
}

void PurchaseAction::selectAndJoin()
{
    mDb->table(mTableName)->select("purchases.*, supliers.name as suplier")->
            join("LEFT JOIN supliers ON purchases.suplier_id = supliers.id");
}
