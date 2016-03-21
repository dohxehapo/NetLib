#include "stdafx.h"
#include "Net.h"


#pragma comment(lib, "Ws2_32.lib")	// Link socket library


#define SD_BOTH	0x02				// Manifest constant for shutdown() 


namespace NetLib
{

	NetErrCode Net::Init()
	{
		LOG("Net::Init()");
		int res;

		// Initialize socket library

		WSADATA wsaData;
		res = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (res != 0)
		{
			echo("Can't initialize socket library.");
			return neterr_noWsa;
		}

		return neterr_noErr;
	}

	NetErrCode Net::Dispose()
	{
		LOG("Net::Dispose()");
		int res;

		// Clean up socket library

		res = WSACleanup();
		if (res != 0)
		{
			echo("Error whilst disposing socket library");
			return neterr_cantCleanupWsa;
		}

		return neterr_noErr;
	}


	NetErrCode Net::CreateSocket(SOCKET &pSocket)
	{
		LOG("Net::CreateSocket()");

		pSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (pSocket == INVALID_SOCKET)
		{
			echo("Can't create socket.");
			return neterr_cantCreateSocket;
		}

		return neterr_noErr;
	}

	NetErrCode Net::SetOptReuseAddr(SOCKET &pSocket)
	{
		LOG("Net::SetOptReuseAddr()");
		int res;

		int int_on = 1;
		res = setsockopt(pSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&int_on, sizeof(int_on));
		if (res != 0)
		{
			echo("Can't set socket SO_REUSEADDR option.");
			return neterr_cantSetSocketOptions;
		}

		return neterr_noErr;
	}

	NetErrCode Net::SetOptNonBlock(SOCKET &pSocket)
	{
		LOG("Net::SetOptNonBlock()");
		int res;

		u_long u_long_on = 1;
		res = ioctlsocket(pSocket, FIONBIO, &u_long_on);
		if (res != 0)
		{
			echo("Can't set socket non-blocking mode.");
			return neterr_cantSetSocketOptions;
		}

		return neterr_noErr;
	}

	NetErrCode Net::CloseSocket(SOCKET &pSocket)
	{
		shutdown(pSocket, SD_BOTH);
		closesocket(pSocket);

		return neterr_noErr;
	}

	NetErrCode Net::Send(SOCKET &pSocket, const char *pData, int pSizeInBytes)
	{
		LOG("Net::Send()");
		int res;

		int offset = 0;
		while (true)
		{
			res = send(pSocket, &pData[offset], min(pSizeInBytes - offset, Net::GetBufferSize()), 0);
			if (res == SOCKET_ERROR)
			{
				echo("Can't send data.");
				return neterr_cantSend;
			}
			else if (res == 0)
				return neterr_connectionClosed;

			offset += res;

			if (offset == pSizeInBytes)
				break;
		}

		return neterr_noErr;
	}

} // NetLib
