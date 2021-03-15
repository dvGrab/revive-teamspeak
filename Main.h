#ifndef MAIN_H
#define MAIN_H

#define _CRT_SECURE_NO_WARNINGS
#define ASIO_STANDALONE
#define USE_STANDALONE_ASIO
#define _WEBSOCKETPP_CPP11_TYPE_TRAITS_

#pragma warning( disable : 4100 )

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <asio.hpp>

#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <fstream>
#include <vector>
#include <iostream>
#include <time.h> 

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <codecvt>
#include <string>

#include "teamspeak_sdk/plugin_definitions.h"
#include "teamspeak_sdk/ts3_functions.h"
#include "teamspeak_sdk/teamspeak/clientlib_publicdefinitions.h"
#include "teamspeak_sdk/teamspeak/public_definitions.h"
#include "teamspeak_sdk/teamspeak/public_errors.h"
#include "teamspeak_sdk/teamspeak/public_errors_rare.h"
#include "teamspeak_sdk/teamspeak/public_rare_definitions.h"

#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")

#include "Plugin.h"
#include "Utilities.h"
#include "Network.h"
#include "Events.h"
#include "Mechanics.h"
#include "json.hpp"

extern struct TS3Functions ts3Functions;

#endif