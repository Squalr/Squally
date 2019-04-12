#include "CipherEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string CipherEvents::EventLoadCipher = "EVENT_LOAD_CIPHER";
const std::string CipherEvents::EventOpenCipher = "EVENT_OPEN_CIPHER";
const std::string CipherEvents::EventRequestBlockSpawn = "EVENT_REQUEST_BLOCK_SPAWN";
const std::string CipherEvents::EventRequestConnectionCreate = "EVENT_REQUEST_CONNECTION_SPAWN";
const std::string CipherEvents::EventConnectionUpdated = "EVENT_CONNECTION_UPDATED";
const std::string CipherEvents::EventConnectionDestroy = "EVENT_CONNECTION_DESTROY";
const std::string CipherEvents::EventChangeActiveCipher = "EVENT_CHANGE_ACTIVE_CIPHER";
const std::string CipherEvents::EventChangeDisplayDataType = "EVENT_CHANGE_DISPLAY_DATA_TYPE";
const std::string CipherEvents::EventOpenAsciiTable = "EVENT_OPEN_ASCII_TABLE";
const std::string CipherEvents::EventTryUnlockCurrentCipher = "EVENT_TRY_UNLOCK_CURRENT_CIPHER";

void CipherEvents::TriggerLoadCipher(CipherLoadArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CipherEvents::EventLoadCipher,
		&args
	);
}

void CipherEvents::TriggerOpenCipher(CipherOpenArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CipherEvents::EventOpenCipher,
		&args
	);
}

void CipherEvents::TriggerRequestBlockSpawn(CipherBlockSpawnArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CipherEvents::EventRequestBlockSpawn,
		&args
	);
}

void CipherEvents::TriggerRequestConnectionCreate(CipherConnectionCreateArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CipherEvents::EventRequestConnectionCreate,
		&args
	);
}

void CipherEvents::TriggerConnectionUpdated(CipherConnectionUpdatedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CipherEvents::EventConnectionUpdated,
		&args
	);
}

void CipherEvents::TriggerDestroyConnectionToInput(CipherConnectionDestroyArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CipherEvents::EventConnectionDestroy,
		&args
	);
}

void CipherEvents::TriggerChangeActiveCipher(CipherChangeActiveCipherArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CipherEvents::EventChangeActiveCipher,
		&args
	);
}

void CipherEvents::TriggerChangeDisplayDataType(CipherChangeDisplayDataTypeArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CipherEvents::EventChangeDisplayDataType,
		&args
	);
}

void CipherEvents::TriggerOpenAsciiTable(CipherOpenAsciiTableArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CipherEvents::EventOpenAsciiTable,
		&args
	);
}

void CipherEvents::TriggerTryUnlockCurrentCipher(UnlockArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CipherEvents::EventTryUnlockCurrentCipher,
		&args
	);
}
