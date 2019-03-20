#include "CipherEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string CipherEvents::EventLoadCipher = "EVENT_LOAD_CIPHER";
const std::string CipherEvents::EventOpenCipher = "EVENT_OPEN_CIPHER";
const std::string CipherEvents::EventRequestToolSpawn = "EVENT_REQUEST_TOOL_SPAWN";
const std::string CipherEvents::EventShowAsciiTable = "EVENT_SHOW_ASCII_TABLE";
const std::string CipherEvents::EventChangeActiveCipher = "EVENT_CHANGE_ACTIVE_CIPHER";
const std::string CipherEvents::EventChangeDisplayDataType = "EVENT_CHANGE_DISPLAY_DATA_TYPE";

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

void CipherEvents::TriggerRequestToolSpawn(CipherSpawnArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CipherEvents::EventRequestToolSpawn,
		&args
	);
}

void CipherEvents::TriggerShowAsciiTable()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CipherEvents::EventShowAsciiTable
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