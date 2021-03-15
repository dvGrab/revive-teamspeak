#include "Mechanics.h"

bool CMechanics::JoinChannel(const char* channelname, const char* password, const char* username)
{

	if (this->serverHandle == -1)
		return false;

	uint64* Results = NULL;

	ts3Functions.getChannelList(this->serverHandle, &Results);

	for (int i = 0; i < 1024; i++)
	{
		if (Results[i] == NULL)
			break;

		char* Name = NULL;
		ts3Functions.getChannelVariableAsString(this->serverHandle, Results[i], CHANNEL_NAME, &Name);

		if (!strcmp(Name, channelname))
		{
			this->speechChannel = Results[i];
			ts3Functions.freeMemory(Name);
			break;
		}
	}

	if (this->speechChannel == -1)
	{
		ts3Functions.printMessageToCurrentTab("[color=red]Revive Voice - Der Ingamechannel wurde nicht gefunden!");
		return true;
	}
	else
	{
		anyID Client;
		if (ts3Functions.getClientID(this->serverHandle, &Client) != ERROR_ok)
			return false;

		if (this->GetCurrentChannelId() != this->speechChannel)
		{
			this->lastChannel = this->GetCurrentChannelId();

			if (ts3Functions.requestClientMove(this->serverHandle, Client, this->speechChannel, password, NULL) != ERROR_ok)
				return true;

			ts3Functions.printMessageToCurrentTab("[REVIVE-VOICE] Du befindest dich nun im Sprachchannel.");
		}

		if (!this->Changename(username))
			return true;
	}

	ts3Functions.freeMemory(Results);
	return true;
}

bool CMechanics::ConnectedToServer(uint64 serverHandle)
{
	this->serverHandle = serverHandle;
	
	ts3Functions.printMessageToCurrentTab("[REVIVE-VOICE] Du hast sich zu einem Server verbunden.");

	return true;
}

bool CMechanics::Changename(const char* username)
{
	if (this->serverHandle == -1)
		return false;

	char* currentName = NULL;
	anyID Client = NULL;

	if (ts3Functions.getClientID(this->serverHandle, &Client) != ERROR_ok)
		return false;

	if (ts3Functions.getClientVariableAsString(this->serverHandle, Client, CLIENT_NICKNAME, &currentName) != ERROR_ok)
		return false;

	std::string currentTemp = currentName;

	ts3Functions.freeMemory(currentName);

	if (currentTemp.find(username) != std::string::npos)
		return false;

	snprintf(this->Name, sizeof(this->Name), "%s", currentTemp.c_str());

	if (ts3Functions.setClientSelfVariableAsString(this->serverHandle, CLIENT_NICKNAME, username) != ERROR_ok)
		return false;

	if (ts3Functions.flushClientSelfUpdates(this->serverHandle, NULL) != ERROR_ok)
		return false;

	return true;
}

bool CMechanics::SetClientPosition(TS3_VECTOR Position)
{
	if (this->serverHandle == -1)
		return false;

	ts3Functions.systemset3DListenerAttributes(this->serverHandle, &Position, NULL, NULL);

	Event->timedOut = false;
	Event->lastTick = std::time(NULL) + 5;

	return true;
}

bool CMechanics::SetTargetPositions(const char* json) {

	if (this->serverHandle == -1)
		return false;

	auto jsonData = nlohmann::json::parse(json);

	std::vector<std::string> client_username;
	std::vector<float> client_x;
	std::vector<float> client_y;
	std::vector<float> client_z;

	for (auto& element : jsonData["data"])
	{
		client_username.push_back(element["username"]);
		client_x.push_back(std::atof(element["x"].get<std::string>().c_str()));
		client_y.push_back(std::atof(element["y"].get<std::string>().c_str()));
		client_z.push_back(std::atof(element["z"].get<std::string>().c_str()));
	}

	anyID* Clients = NULL;

	if (ts3Functions.getChannelClientList(this->serverHandle, this->GetCurrentChannelId(), &Clients) != ERROR_ok)
		return false;

	for (int i = 0; i < this->GetServerClientCount(); i++)
	{
		char* tempUsername = NULL;

		if (ts3Functions.getClientVariableAsString(this->serverHandle, Clients[i], CLIENT_NICKNAME, &tempUsername) != ERROR_ok)
			return NULL;

		bool isMuted = true;

		for (int e = 0; e < jsonData["data"].size(); e++)
		{
			if (client_username[e].find(tempUsername) != std::string::npos)
			{
				isMuted = false;

				TS3_VECTOR Position;
				Position.x = client_x[e];
				Position.y = client_y[e];
				Position.z = client_z[e];

				ts3Functions.channelset3DAttributes(this->serverHandle, Clients[i], &Position);
			}
		}

		this->SetClientMuteState(Clients[i], isMuted);

		ts3Functions.freeMemory(tempUsername);
	}

}

uint64 CMechanics::GetCurrentChannelId()
{
	if (this->serverHandle == -1)
		return NULL;

	uint64 returnValue = NULL;

	anyID Client;

	if (ts3Functions.getClientID(this->serverHandle, &Client) != ERROR_ok)
		return NULL;

	if (ts3Functions.getChannelOfClient(this->serverHandle, Client, &returnValue) != ERROR_ok)
		return NULL;

	return returnValue;
}

bool CMechanics::SetClientMuteState(anyID clientId, bool state)
{
	if (this->serverHandle == -1)
		return false;

	int isMuted;

	anyID Client[2];
	Client[0] = clientId;
	Client[1] = -1;

	if (ts3Functions.getClientVariableAsInt(this->serverHandle, clientId, CLIENT_IS_MUTED, &isMuted) != ERROR_ok)
		return false;

	if (state)
	{
		if (!isMuted)
		{
			if (ts3Functions.requestMuteClients(this->serverHandle, Client, NULL) != ERROR_ok)
				return false;
			else
				return true;
		}
	}
	else
	{
		if (isMuted)
		{
			if (ts3Functions.requestUnmuteClients(this->serverHandle, Client, NULL) != ERROR_ok)
				return false;
			else
				return true;
		}
	}

	return true;
}

anyID CMechanics::GetIdByName(const char* username)
{
	if (this->serverHandle == -1)
		return NULL;

	anyID returnClient = NULL;
	int Count = NULL;
	anyID* Clients = NULL;

	if (ts3Functions.getClientList(this->serverHandle, &Clients) != ERROR_ok)
		return NULL;

	if (ts3Functions.getServerVariableAsInt(this->serverHandle, VIRTUALSERVER_CLIENTS_ONLINE, &Count) != ERROR_ok)
		return NULL;

	char tempo[128];
	sprintf_s(tempo, 128, "Count: %i\n", Count);
	ts3Functions.printMessageToCurrentTab(tempo);

	for (int i = 0; i < Count; i++)
	{
		char* tempUsername = NULL;

		if (ts3Functions.getClientVariableAsString(this->serverHandle, Clients[i], CLIENT_NICKNAME, &tempUsername) != ERROR_ok)
			return NULL;

		if (!strcmp(username, tempUsername))
		{
			returnClient = Clients[i];
			break;
		}

	}

	return returnClient;
}

int CMechanics::GetServerClientCount()
{
	int returnValue = 0;

	if (ts3Functions.getServerVariableAsInt(this->serverHandle, VIRTUALSERVER_CLIENTS_ONLINE, &returnValue) != ERROR_ok)
		return NULL;

	return returnValue;
}
