#include "Main.h"

#define _strcpy(dest, destSize, src) strcpy_s(dest, destSize, src)
#define snprintf sprintf_s

#define PLUGIN_API_VERSION 23

#define PATH_BUFSIZE 512
#define COMMAND_BUFSIZE 128
#define INFODATA_BUFSIZE 128
#define SERVERINFO_BUFSIZE 256
#define CHANNELINFO_BUFSIZE 512
#define RETURNCODE_BUFSIZE 128

static char* pluginID = NULL;

struct TS3Functions ts3Functions;

CNetwork* Network = new CNetwork();
CEvent* Event = new CEvent();
CMechanics* Mechanics = new CMechanics();

const char* ts3plugin_name() {
	return "Revive Voice";
}

const char* ts3plugin_version() {
	return "0.0.1";
}

int ts3plugin_apiVersion() {
	return PLUGIN_API_VERSION;
}

const char* ts3plugin_author() {
	return "REVIVE NETWORK";
}

const char* ts3plugin_description() {

	return "The Revive Network Voice Plugin for GTA5!";
}

void ts3plugin_setFunctionPointers(const struct TS3Functions funcs) {
	ts3Functions = funcs;
}

int ts3plugin_init() {
	char appPath[PATH_BUFSIZE];
	char resourcesPath[PATH_BUFSIZE];
	char configPath[PATH_BUFSIZE];
	char pluginPath[PATH_BUFSIZE];

	ts3Functions.getAppPath(appPath, PATH_BUFSIZE);
	ts3Functions.getResourcesPath(resourcesPath, PATH_BUFSIZE);
	ts3Functions.getConfigPath(configPath, PATH_BUFSIZE);
	ts3Functions.getPluginPath(pluginPath, PATH_BUFSIZE, pluginID);

	Network->Initialize(ts3Functions);

	return 0;
}

/* Custom code called right before the plugin is unloaded */
void ts3plugin_shutdown() {
	if (pluginID) {
		free(pluginID);
		pluginID = NULL;
	}
}

int ts3plugin_offersConfigure() {
	return PLUGIN_OFFERS_NO_CONFIGURE; 
}

void ts3plugin_configure(void* handle, void* qParentWidget) {
}

void ts3plugin_registerPluginID(const char* id) {
	const size_t sz = strlen(id) + 1;
	pluginID = (char*)malloc(sz * sizeof(char));
	_strcpy(pluginID, sz, id);  
}

const char* ts3plugin_commandKeyword() {
	return NULL;
}

static void print_and_free_bookmarks_list(struct PluginBookmarkList* list)
{
}


int ts3plugin_processCommand(uint64 serverConnectionHandlerID, const char* command) {
	return 0; 
}

void ts3plugin_currentServerConnectionChanged(uint64 serverConnectionHandlerID) {
}

const char* ts3plugin_infoTitle() {
	return "Revive Network - Voiceplugin";
}

void ts3plugin_infoData(uint64 serverConnectionHandlerID, uint64 id, enum PluginItemType type, char** data) {

}

void ts3plugin_freeMemory(void* data) {
	free(data);
}


int ts3plugin_requestAutoload() {
	return 0;  /* 1 = request autoloaded, 0 = do not request autoload */
}


static struct PluginMenuItem* createMenuItem(enum PluginMenuType type, int id, const char* text, const char* icon) {
	struct PluginMenuItem* menuItem = (struct PluginMenuItem*)malloc(sizeof(struct PluginMenuItem));
	menuItem->type = type;
	menuItem->id = id;
	_strcpy(menuItem->text, PLUGIN_MENU_BUFSZ, text);
	_strcpy(menuItem->icon, PLUGIN_MENU_BUFSZ, icon);
	return menuItem;
}

#define BEGIN_CREATE_MENUS(x) const size_t sz = x + 1; size_t n = 0; *menuItems = (struct PluginMenuItem**)malloc(sizeof(struct PluginMenuItem*) * sz);
#define CREATE_MENU_ITEM(a, b, c, d) (*menuItems)[n++] = createMenuItem(a, b, c, d);
#define END_CREATE_MENUS (*menuItems)[n++] = NULL; assert(n == sz);

void ts3plugin_initMenus(struct PluginMenuItem*** menuItems, char** menuIcon) {

}

static struct PluginHotkey* createHotkey(const char* keyword, const char* description) {
	struct PluginHotkey* hotkey = (struct PluginHotkey*)malloc(sizeof(struct PluginHotkey));
	_strcpy(hotkey->keyword, PLUGIN_HOTKEY_BUFSZ, keyword);
	_strcpy(hotkey->description, PLUGIN_HOTKEY_BUFSZ, description);
	return hotkey;
}

#define BEGIN_CREATE_HOTKEYS(x) const size_t sz = x + 1; size_t n = 0; *hotkeys = (struct PluginHotkey**)malloc(sizeof(struct PluginHotkey*) * sz);
#define CREATE_HOTKEY(a, b) (*hotkeys)[n++] = createHotkey(a, b);
#define END_CREATE_HOTKEYS (*hotkeys)[n++] = NULL; assert(n == sz);

void ts3plugin_initHotkeys(struct PluginHotkey*** hotkeys) {
	BEGIN_CREATE_HOTKEYS(0);  
	END_CREATE_HOTKEYS;
}

void ts3plugin_onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber) {

	if (newStatus == STATUS_CONNECTED)
	{
		Mechanics->ConnectedToServer(serverConnectionHandlerID);
	}
		

}

void ts3plugin_onNewChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID) {
}

void ts3plugin_onNewChannelCreatedEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
}

void ts3plugin_onDelChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
}

void ts3plugin_onChannelMoveEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 newChannelParentID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
}

void ts3plugin_onUpdateChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
}

void ts3plugin_onUpdateChannelEditedEvent(uint64 serverConnectionHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
}

void ts3plugin_onUpdateClientEvent(uint64 serverConnectionHandlerID, anyID clientID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
}

void ts3plugin_onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage) {

}

void ts3plugin_onClientMoveSubscriptionEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility) {
}

void ts3plugin_onClientMoveTimeoutEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* timeoutMessage) {
}

void ts3plugin_onClientMoveMovedEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID moverID, const char* moverName, const char* moverUniqueIdentifier, const char* moveMessage) {
}

void ts3plugin_onClientKickFromChannelEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage) {
}

void ts3plugin_onClientKickFromServerEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage) {
}

void ts3plugin_onClientIDsEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, anyID clientID, const char* clientName) {
}

void ts3plugin_onClientIDsFinishedEvent(uint64 serverConnectionHandlerID) {
}

void ts3plugin_onServerEditedEvent(uint64 serverConnectionHandlerID, anyID editerID, const char* editerName, const char* editerUniqueIdentifier) {
}

void ts3plugin_onServerUpdatedEvent(uint64 serverConnectionHandlerID) {
}

int ts3plugin_onServerErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage) {
if (returnCode) {
		return 1;
	}
	return 0;  /* If no plugin return code was used, the return value of this function is ignored */
}

void ts3plugin_onServerStopEvent(uint64 serverConnectionHandlerID, const char* shutdownMessage) {
}

int ts3plugin_onTextMessageEvent(uint64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message, int ffIgnored) {
	return 0; 
}

void ts3plugin_onTalkStatusChangeEvent(uint64 serverConnectionHandlerID, int status, int isReceivedWhisper, anyID clientID) {

}

void ts3plugin_onConnectionInfoEvent(uint64 serverConnectionHandlerID, anyID clientID) {
}

void ts3plugin_onServerConnectionInfoEvent(uint64 serverConnectionHandlerID) {
}

void ts3plugin_onChannelSubscribeEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
}

void ts3plugin_onChannelSubscribeFinishedEvent(uint64 serverConnectionHandlerID) {
}

void ts3plugin_onChannelUnsubscribeEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
}

void ts3plugin_onChannelUnsubscribeFinishedEvent(uint64 serverConnectionHandlerID) {
}

void ts3plugin_onChannelDescriptionUpdateEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
}

void ts3plugin_onChannelPasswordChangedEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
}

void ts3plugin_onPlaybackShutdownCompleteEvent(uint64 serverConnectionHandlerID) {
}

void ts3plugin_onSoundDeviceListChangedEvent(const char* modeID, int playOrCap) {
}

void ts3plugin_onEditPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, anyID clientID, short* samples, int sampleCount, int channels) {
}

void ts3plugin_onEditPostProcessVoiceDataEvent(uint64 serverConnectionHandlerID, anyID clientID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask) {
}

void ts3plugin_onEditMixedPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask) {
}

void ts3plugin_onEditCapturedVoiceDataEvent(uint64 serverConnectionHandlerID, short* samples, int sampleCount, int channels, int* edited) {
}

void ts3plugin_onCustom3dRolloffCalculationClientEvent(uint64 serverConnectionHandlerID, anyID clientID, float distance, float* volume) {
}

void ts3plugin_onCustom3dRolloffCalculationWaveEvent(uint64 serverConnectionHandlerID, uint64 waveHandle, float distance, float* volume) {
}

void ts3plugin_onUserLoggingMessageEvent(const char* logMessage, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* completeLogString) {
}

void ts3plugin_onClientBanFromServerEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, uint64 time, const char* kickMessage) {
}

int ts3plugin_onClientPokeEvent(uint64 serverConnectionHandlerID, anyID fromClientID, const char* pokerName, const char* pokerUniqueIdentity, const char* message, int ffIgnored) {
	return 0;  
}

void ts3plugin_onClientSelfVariableUpdateEvent(uint64 serverConnectionHandlerID, int flag, const char* oldValue, const char* newValue) {
}

void ts3plugin_onFileListEvent(uint64 serverConnectionHandlerID, uint64 channelID, const char* path, const char* name, uint64 size, uint64 datetime, int type, uint64 incompletesize, const char* returnCode) {
}

void ts3plugin_onFileListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelID, const char* path) {
}

void ts3plugin_onFileInfoEvent(uint64 serverConnectionHandlerID, uint64 channelID, const char* name, uint64 size, uint64 datetime) {
}

void ts3plugin_onServerGroupListEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID, const char* name, int type, int iconID, int saveDB) {
}

void ts3plugin_onServerGroupListFinishedEvent(uint64 serverConnectionHandlerID) {
}

void ts3plugin_onServerGroupByClientIDEvent(uint64 serverConnectionHandlerID, const char* name, uint64 serverGroupList, uint64 clientDatabaseID) {
}

void ts3plugin_onServerGroupPermListEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
}

void ts3plugin_onServerGroupPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID) {
}

void ts3plugin_onServerGroupClientListEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID, uint64 clientDatabaseID, const char* clientNameIdentifier, const char* clientUniqueID) {
}

void ts3plugin_onChannelGroupListEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID, const char* name, int type, int iconID, int saveDB) {
}

void ts3plugin_onChannelGroupListFinishedEvent(uint64 serverConnectionHandlerID) {
}

void ts3plugin_onChannelGroupPermListEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
}

void ts3plugin_onChannelGroupPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID) {
}

void ts3plugin_onChannelPermListEvent(uint64 serverConnectionHandlerID, uint64 channelID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
}

void ts3plugin_onChannelPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
}

void ts3plugin_onClientPermListEvent(uint64 serverConnectionHandlerID, uint64 clientDatabaseID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
}

void ts3plugin_onClientPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 clientDatabaseID) {
}

void ts3plugin_onChannelClientPermListEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 clientDatabaseID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
}

void ts3plugin_onChannelClientPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 clientDatabaseID) {
}

void ts3plugin_onClientChannelGroupChangedEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID, uint64 channelID, anyID clientID, anyID invokerClientID, const char* invokerName, const char* invokerUniqueIdentity) {
}

int ts3plugin_onServerPermissionErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, unsigned int failedPermissionID) {
	return 0; 
}

void ts3plugin_onPermissionListGroupEndIDEvent(uint64 serverConnectionHandlerID, unsigned int groupEndID) {
}

void ts3plugin_onPermissionListEvent(uint64 serverConnectionHandlerID, unsigned int permissionID, const char* permissionName, const char* permissionDescription) {
}

void ts3plugin_onPermissionListFinishedEvent(uint64 serverConnectionHandlerID) {
}

void ts3plugin_onPermissionOverviewEvent(uint64 serverConnectionHandlerID, uint64 clientDatabaseID, uint64 channelID, int overviewType, uint64 overviewID1, uint64 overviewID2, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
}

void ts3plugin_onPermissionOverviewFinishedEvent(uint64 serverConnectionHandlerID) {
}

void ts3plugin_onServerGroupClientAddedEvent(uint64 serverConnectionHandlerID, anyID clientID, const char* clientName, const char* clientUniqueIdentity, uint64 serverGroupID, anyID invokerClientID, const char* invokerName, const char* invokerUniqueIdentity) {
}

void ts3plugin_onServerGroupClientDeletedEvent(uint64 serverConnectionHandlerID, anyID clientID, const char* clientName, const char* clientUniqueIdentity, uint64 serverGroupID, anyID invokerClientID, const char* invokerName, const char* invokerUniqueIdentity) {
}

void ts3plugin_onClientNeededPermissionsEvent(uint64 serverConnectionHandlerID, unsigned int permissionID, int permissionValue) {
}

void ts3plugin_onClientNeededPermissionsFinishedEvent(uint64 serverConnectionHandlerID) {
}

void ts3plugin_onFileTransferStatusEvent(anyID transferID, unsigned int status, const char* statusMessage, uint64 remotefileSize, uint64 serverConnectionHandlerID) {
}

void ts3plugin_onClientChatClosedEvent(uint64 serverConnectionHandlerID, anyID clientID, const char* clientUniqueIdentity) {
}

void ts3plugin_onClientChatComposingEvent(uint64 serverConnectionHandlerID, anyID clientID, const char* clientUniqueIdentity) {
}

void ts3plugin_onServerLogEvent(uint64 serverConnectionHandlerID, const char* logMsg) {
}

void ts3plugin_onServerLogFinishedEvent(uint64 serverConnectionHandlerID, uint64 lastPos, uint64 fileSize) {
}

void ts3plugin_onMessageListEvent(uint64 serverConnectionHandlerID, uint64 messageID, const char* fromClientUniqueIdentity, const char* subject, uint64 timestamp, int flagRead) {
}

void ts3plugin_onMessageGetEvent(uint64 serverConnectionHandlerID, uint64 messageID, const char* fromClientUniqueIdentity, const char* subject, const char* message, uint64 timestamp) {
}

void ts3plugin_onClientDBIDfromUIDEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, uint64 clientDatabaseID) {
}

void ts3plugin_onClientNamefromUIDEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, uint64 clientDatabaseID, const char* clientNickName) {
}

void ts3plugin_onClientNamefromDBIDEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, uint64 clientDatabaseID, const char* clientNickName) {
}

void ts3plugin_onComplainListEvent(uint64 serverConnectionHandlerID, uint64 targetClientDatabaseID, const char* targetClientNickName, uint64 fromClientDatabaseID, const char* fromClientNickName, const char* complainReason, uint64 timestamp) {
}

void ts3plugin_onBanListEvent(uint64 serverConnectionHandlerID, uint64 banid, const char* ip, const char* name, const char* uid, const char* mytsid, uint64 creationTime, uint64 durationTime, const char* invokerName,
	uint64 invokercldbid, const char* invokeruid, const char* reason, int numberOfEnforcements, const char* lastNickName) {
}

void ts3plugin_onClientServerQueryLoginPasswordEvent(uint64 serverConnectionHandlerID, const char* loginPassword) {
}

void ts3plugin_onPluginCommandEvent(uint64 serverConnectionHandlerID, const char* pluginName, const char* pluginCommand, anyID invokerClientID, const char* invokerName, const char* invokerUniqueIdentity) {
}

void ts3plugin_onIncomingClientQueryEvent(uint64 serverConnectionHandlerID, const char* commandText) {
}

void ts3plugin_onServerTemporaryPasswordListEvent(uint64 serverConnectionHandlerID, const char* clientNickname, const char* uniqueClientIdentifier, const char* description, const char* password, uint64 timestampStart, uint64 timestampEnd, uint64 targetChannelID, const char* targetChannelPW) {
}

void ts3plugin_onAvatarUpdated(uint64 serverConnectionHandlerID, anyID clientID, const char* avatarPath) {

}


void ts3plugin_onMenuItemEvent(uint64 serverConnectionHandlerID, enum PluginMenuType type, int menuItemID, uint64 selectedItemID) {
	
}

void ts3plugin_onHotkeyEvent(const char* keyword) {
}


void ts3plugin_onHotkeyRecordedEvent(const char* keyword, const char* key) {
}

const char* ts3plugin_keyDeviceName(const char* keyIdentifier) {
	return NULL;
}


const char* ts3plugin_displayKeyText(const char* keyIdentifier) {
	return NULL;
}

const char* ts3plugin_keyPrefix() {
	return NULL;
}

void ts3plugin_onClientDisplayNameChanged(uint64 serverConnectionHandlerID, anyID clientID, const char* displayName, const char* uniqueClientIdentifier) {
}
