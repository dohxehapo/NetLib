#include "Config.h"

#include <fstream>
#include <sstream>

#include "Utils.h"


namespace NetLib
{

	int Config::m_serverPort = 0;
	bool Config::m_keepAliveSupport;
	int Config::m_keepAliveTimeout;
	int Config::m_keepAliveMaxRequests;
	int Config::m_maxConnections;

	bool Config::m_allowFileHandle = false;
	std::string Config::m_rootFolder = "./";
	std::string Config::m_defaultPage400 = "";
	std::string Config::m_defaultPage404 = "";
	std::string Config::m_defaultPage405 = "";
	std::string Config::m_defaultPage414 = "";
	std::string Config::m_defaultPage501 = "";

	std::vector<std::string> Config::m_allowedRequestMethods;
	int Config::m_requestUriMaxLength = 0;

	bool Config::m_appendDateTimeStamp = false;
	bool Config::m_appendServerName = false;
	std::string Config::m_serverName = "";


	NetErrCode Config::ReadFromFile(const std::string &pFileName)
	{
		std::fstream f(pFileName, std::ios::in);
		std::string line;
		std::vector<std::string> tokens;

		std::string header;
		std::string value;

		while (std::getline(f, line))
		{
			line = TrimString(line);
			if (line.empty())
				continue;
			if (line[0] == ';')
				continue;

			int pos = line.find_first_of('=', 0);
			if ((pos == std::string::npos) || (pos == 0))
				continue;

			header = TrimString(line.substr(0, pos));
			value = TrimString(line.substr(pos + 1));

			if (header.compare("ServerPort") == 0)
				m_serverPort = std::stoi(value);
			else if (header.compare("KeepAlive") == 0)
				m_keepAliveSupport = StringToBool(value);
			else if (header.compare("KeepAliveTimeout") == 0)
				m_keepAliveTimeout = std::stoi(value);
			else if (header.compare("KeepAliveMaxRequests") == 0)
				m_keepAliveMaxRequests = std::stoi(value);
			else if (header.compare("MaxConnections") == 0)
				m_maxConnections = std::stoi(value);
			else if (header.compare("AllowFileHandle") == 0)
				m_allowFileHandle = StringToBool(value);
			else if (header.compare("RootFolder") == 0)
				m_rootFolder = value;
			else if (header.compare("DefaultPage400") == 0)
				m_defaultPage400 = value;
			else if (header.compare("DefaultPage404") == 0)
				m_defaultPage404 = value;
			else if (header.compare("DefaultPage405") == 0)
				m_defaultPage405 = value;
			else if (header.compare("DefaultPage414") == 0)
				m_defaultPage414 = value;
			else if (header.compare("DefaultPage501") == 0)
				m_defaultPage501 = value;
			else if (header.compare("AppendDateTime") == 0)
				m_appendDateTimeStamp = StringToBool(value);
			else if (header.compare("AppendServerName") == 0)
				m_appendServerName = StringToBool(value);
			else if (header.compare("ServerName") == 0)
				m_serverName = value;
			else if (header.compare("AllowedRequestMethods") == 0)
			{
				tokens = SplitString(value, ',');
				for (auto & name : tokens)
					m_allowedRequestMethods.push_back(TrimString(name));
			}
			else if (header.compare("RequestUriMaxLength") == 0)
				m_requestUriMaxLength = std::stoi(value);
			else
			{
				// Log unrecognized token
			}
		}

		return neterr_noErr;
	}

} // ns NetLib
