#ifndef EVENTS_H
#define EVENTS_H

#include "Main.h"

class CEvent {
private:

public:
	int lastTick;
	bool timedOut = true;

	bool Listener(const char* json);
	bool Heartbeat();
};

extern CEvent* Event;

#endif