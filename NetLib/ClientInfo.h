#pragma once

#ifndef NETLIB_CLIENTINFO_H
#define NETLIB_CLIENTINFO_H


#include <Windows.h>
#include <string>


namespace NetLib
{

	typedef UINT_PTR CLIENTID;


	// Struct that represents client. It contains it's unique Id, address and port
	struct ClientInfo
	{
		ClientInfo()
			: Id(0), Address(""), Port(0)
		{
		}

		ClientInfo(CLIENTID pId, const std::string &pAddress, int pPort)
			: Id(pId), Address(pAddress), Port(pPort)
		{
		}

		CLIENTID Id;			// Client's Id
		std::string Address;	// Client's address
		int Port;				// Client's port

	};

} // ns Netlib


#endif // NETLIB_CLIENTINFO_H