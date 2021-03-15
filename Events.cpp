#include "Events.h"

bool CEvent::Heartbeat()
{
	while (true)
	{
		if (!this->timedOut)
		{
			if (this->lastTick < std::time(NULL))
			{
				anyID Client = NULL;

				if (ts3Functions.getClientID(Mechanics->serverHandle, &Client) != ERROR_ok)
					return true;

				if (ts3Functions.requestClientMove(Mechanics->serverHandle, Client, Mechanics->lastChannel, "", NULL) != ERROR_ok)
					return true;

				this->timedOut = true;
			}
		}

		Sleep(1000);
	}

	return true;
}

bool CEvent::Listener(const char* json)
{
	auto jsonData = nlohmann::json::parse(json);

	if (jsonData["method"].is_null())
		return false;

	if (jsonData["method"].get<std::string>().find("ts3:joinchannel") != std::string::npos)
	{
		if (jsonData["data"]["channel"].is_null())
			return false;

		if (jsonData["data"]["password"].is_null())
			return false;

		if (jsonData["data"]["username"].is_null())
			return false;

		if (!Mechanics->JoinChannel(jsonData["data"]["channel"].get<std::string>().c_str(), 
			jsonData["data"]["password"].get<std::string>().c_str(),
			jsonData["data"]["username"].get<std::string>().c_str()))
		{
			ts3Functions.printMessageToCurrentTab("[color=red]Revive Voice - Stell sicher das du dich auf dem richtigen Teamspeak befindest![/color]");
			return false;
		}
	}

	if (jsonData["method"].get<std::string>().find("ts3:localposition") != std::string::npos)
	{
		if (jsonData["data"]["x"].is_null())
			return false;

		if (jsonData["data"]["y"].is_null())
			return false;

		if (jsonData["data"]["z"].is_null())
			return false;

		TS3_VECTOR Position;
		Position.x = std::atof(jsonData["data"]["x"].get<std::string>().c_str());
		Position.y = std::atof(jsonData["data"]["y"].get<std::string>().c_str());
		Position.z = std::atof(jsonData["data"]["z"].get<std::string>().c_str());

		Mechanics->SetClientPosition(Position); 
	}

	if (jsonData["method"].get<std::string>().find("ts3:playerpositions") != std::string::npos)
	{
		if (!jsonData["data"].size())
			return false;

		Mechanics->SetTargetPositions(json);
	}

	return true;
}