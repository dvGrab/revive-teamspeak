#ifndef NETWORK_H
#define NETWORK_H

#include "Main.h"

class CNetwork {
		
private:
	struct TS3Functions Functions;
	bool Initialized = false;

public: 
	bool Initialize(const struct TS3Functions ts3);

};

#endif