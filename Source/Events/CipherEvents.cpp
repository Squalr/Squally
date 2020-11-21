#include "CipherEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string CipherEvents::EventOpenCipher = "EVENT_CIPHER_OPEN_CIPHER";
const std::string CipherEvents::EventExitCipher = "EVENT_CIPHER_EXIT_CIPHER";
const std::string CipherEvents::EventRequestBlockSpawn = "EVENT_CIPHER_REQUEST_BLOCK_SPAWN";
const std::string CipherEvents::EventRequestConnectionCreate = "EVENT_CIPHER_REQUEST_CONNECTION_SPAWN";
const std::string CipherEvents::EventConnectionUpdated = "EVENT_CIPHER_CONNECTION_UPDATED";
const std::string CipherEvents::EventConnectionDestroy = "EVENT_CIPHER_CONNECTION_DESTROY";
const std::string CipherEvents::EventChangeActiveCipher = "EVENT_CIPHER_CHANGE_ACTIVE_CIPHER";
const std::string CipherEvents::EventChangeDisplayDataType = "EVENT_CIPHER_CHANGE_DISPLAY_DATA_TYPE";
const std::string CipherEvents::EventOpenAsciiTable = "EVENT_CIPHER_OPEN_ASCII_TABLE";
const std::string CipherEvents::EventTryUnlockCurrentCipher = "EVENT_CIPHER_TRY_UNLOCK_CURRENT_CIPHER";
const std::string CipherEvents::EventRequestStateUpdate = "EVENT_CIPHER_REQUEST_STATE_UPDATE";
const std::string CipherEvents::EventBeforeRequestStateUpdate = "EVENT_CIPHER_BEFORE_REQUEST_STATE_UPDATE";
const std::string CipherEvents::EventBeforeStateUpdate = "EVENT_CIPHER_BEFORE_STATE_UPDATE";
const std::string CipherEvents::EventOnStateUpdate = "EVENT_CIPHER_ON_STATE_UPDATE";

void CipherEvents::TriggerOpenCipher(CipherOpenArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventOpenCipher,
		&args
	);
}

void CipherEvents::TriggerExitCipher(CipherExitArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventExitCipher,
		&args
	);
}

void CipherEvents::TriggerRequestBlockSpawn(CipherBlockSpawnArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventRequestBlockSpawn,
		&args
	);
}

void CipherEvents::TriggerRequestConnectionCreate(CipherConnectionCreateArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventRequestConnectionCreate,
		&args
	);
}

void CipherEvents::TriggerConnectionUpdated(CipherConnectionUpdatedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventConnectionUpdated,
		&args
	);
}

void CipherEvents::TriggerDestroyConnectionToInput(CipherConnectionDestroyArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventConnectionDestroy,
		&args
	);
}

void CipherEvents::TriggerChangeActiveCipher(CipherChangeActiveCipherArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventChangeActiveCipher,
		&args
	);
}

void CipherEvents::TriggerChangeDisplayDataType(CipherChangeDisplayDataTypeArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventChangeDisplayDataType,
		&args
	);
}

void CipherEvents::TriggerOpenAsciiTable(CipherOpenAsciiTableArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventOpenAsciiTable,
		&args
	);
}

void CipherEvents::TriggerTryUnlockCurrentCipher(UnlockArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventTryUnlockCurrentCipher,
		&args
	);
}

void CipherEvents::TriggerBeforeRequestStateUpdate(CipherState* cipherState)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventBeforeRequestStateUpdate,
		cipherState
	);
}
	
void CipherEvents::TriggerRequestStateUpdate(CipherState* cipherState)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventRequestStateUpdate,
		cipherState
	);
}

void CipherEvents::TriggerBeforeStateUpdate(CipherState* cipherState)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventBeforeStateUpdate,
		cipherState
	);
}

void CipherEvents::TriggerOnStateUpdate(CipherState* cipherState)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		CipherEvents::EventOnStateUpdate,
		cipherState
	);
}
