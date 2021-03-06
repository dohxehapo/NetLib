// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Product:		NetLib
// Module:		Net
// Author:		Anton Egorov
// Description:	Class that contains common network
//				functions for client and server
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#pragma once

#ifndef NETLIB_NET_H
#define NETLIB_NET_H


#define NOMINMAX
#include <Windows.h>
#include <string>

#include "NetErrCodes.h"

#pragma comment(lib, "Ws2_32.lib") // Win socket library


// Manifest constant for shutdown()
#define SD_BOTH	0x02


namespace NetLib
{
	using namespace NetLib::NetErrCodes;

	// Class that contains common network functions for client and server
	class Net
	{
	public:

		// Static function for common network initialization
		static NetErrCode Init();

		// Static function for common network disposion
		static NetErrCode Dispose();


		// Returns the maximum size of a package that can be sent or received.
		// If the package to be sent is larger then it will be divided
		inline static int GetBufferSize() { return (32 * 1024); }


		// Creates a new socket
		// Params:
		// [out] SOCKET & pSocket	- reference to the socket to be create
		static NetErrCode CreateSocket(SOCKET &pSocket);

		// Sets the SO_REUSEADDR option for the given socket
		// Params:
		// [in] SOCKET & pSocket	- reference to the socket to set option to
		static NetErrCode SetOptReuseAddr(SOCKET &pSocket);

		// Sets the NONBLOCK option for the given socket
		// Params:
		// [in] SOCKET & pSocket	- reference to the socket to set option to
		// [in] bool pOn			- turn the option on or off
		static NetErrCode SetOptNonBlock(SOCKET &pSocket, bool pOn);

		// Closes the given socket
		// Params:
		// [in] SOCKET pSocket	- reference to the socket to close
		static NetErrCode CloseSocket(SOCKET pSocket);

		// Sends the given data to the given socket
		// Params:
		// [in] SOCKET & pSocket	- socket to send data to
		// [in] const char * pData	- data to be sent
		// [in] int pSizeInBytes	- size of data to be sent in bytes
		static NetErrCode Send(SOCKET &pSocket, const char *pData, int pSizeInBytes);

	};

} // ns NetLib


#endif // NETLIB_NET_H
