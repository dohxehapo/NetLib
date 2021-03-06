#pragma once

#ifndef NETLIB_NETERRCODES_H
#define NETLIB_NETERRCODES_H


namespace NetLib
{
	namespace NetErrCodes
	{

		// Enumeration that contains error codes
		enum NetErrCode : int
		{
			neterr_noErr = 0,
			neterr_noWsa,
			neterr_cantCleanupWsa,
			neterr_cantCreateSocket,
			neterr_cantSetSocketOptions,
			neterr_cantBindSocket,
			neterr_cantStartListen,
			neterr_cantConnect,
			neterr_connectionRefused,
			neterr_connectionTimedOut,
			neterr_cantSend,
			neterr_cantSendInvalidLength,
			neterr_connectionClosed,
			neterr_noSuchClient,
			neterr_errorDisconnecting,
			neterr_cantSelect,
			neterr_cantReceive,

			neterr_parse_cantParse,
			neterr_parse_requestLineTooLong,
			neterr_parse_bodyTooLong,
			neterr_parse_methodNotAllowed,

			neterr_noRootDir,
			neterr_fileHandlerMethodNotRecognized,

			neterr_authError,
			neterr_cantParseAuth,
			neterr_notFound,
			neterr_authRequired,
			neterr_forbidden,

			neterr_invalidAddress,

			neterr_end
		};

	} // ns NetErrCode_Wrapper
} // ns NetLib


#endif // NETLIB_NETERRCODES_H
