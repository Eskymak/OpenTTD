/* $Id: network_base.h 22423 2011-05-04 20:24:23Z rubidium $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file network_base.h Base core network types and some helper functions to access them. */

#ifndef NETWORK_BASE_H
#define NETWORK_BASE_H

#ifdef ENABLE_NETWORK

#include "network_type.h"
#include "core/address.h"
#include "../core/pool_type.hpp"
#include "../company_type.h"

/** Type for the pool with client information. */
typedef Pool<NetworkClientInfo, ClientIndex, 8, MAX_CLIENT_SLOTS, PT_NCLIENT> NetworkClientInfoPool;
extern NetworkClientInfoPool _networkclientinfo_pool;

/** Container for all information known about a client. */
struct NetworkClientInfo : NetworkClientInfoPool::PoolItem<&_networkclientinfo_pool> {
	ClientID client_id;                             ///< Client identifier (same as ClientState->client_id)
	char client_name[NETWORK_CLIENT_NAME_LENGTH];   ///< Name of the client
	byte client_lang;                               ///< The language of the client
	CompanyID client_playas;                        ///< As which company is this client playing (CompanyID)
	Date join_date;                                 ///< Gamedate the client has joined

	/**
	 * Create a new client.
	 * @param client_id The unique identifier of the client.
	 */
	NetworkClientInfo(ClientID client_id = INVALID_CLIENT_ID) : client_id(client_id) {}
	~NetworkClientInfo();

	static NetworkClientInfo *GetByClientID(ClientID client_id);
};

/**
 * Iterate over all the clients from a given index.
 * @param var The variable to iterate with.
 * @param start The location to start the iteration from.
 */
#define FOR_ALL_CLIENT_INFOS_FROM(var, start) FOR_ALL_ITEMS_FROM(NetworkClientInfo, clientinfo_index, var, start)

/**
 * Iterate over all the clients.
 * @param var The variable to iterate with.
 */
#define FOR_ALL_CLIENT_INFOS(var) FOR_ALL_CLIENT_INFOS_FROM(var, 0)

#endif /* ENABLE_NETWORK */
#endif /* NETWORK_BASE_H */
