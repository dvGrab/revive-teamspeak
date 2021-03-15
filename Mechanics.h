#ifndef MECHANICS_H
#define MECHANICS_H

#include "Main.h"

class CMechanics {
private:

	char Name[128];
	bool clientsMuted = false;

public:
	uint64 serverHandle = -1;

	uint64 speechChannel = -1;
	uint64 lastChannel = -1;

	bool ConnectedToServer(uint64 serverHandle);
	bool JoinChannel(const char* channelname, const char* password, const char* username);
	bool Changename(const char* username);
	bool SetClientPosition(TS3_VECTOR Position);
	bool SetTargetPositions(const char* json);
	bool SetClientMuteState(anyID clientId, bool state);

	uint64 GetCurrentChannelId();
	anyID GetIdByName(const char * username);
	int GetServerClientCount();
};

extern CMechanics* Mechanics;

#endif