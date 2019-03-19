#include "CipherEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string CipherEvents::EventLoadCipher = "EVENT_LOAD_CIPHER";
const std::string CipherEvents::EventOpenCipher = "EVENT_OPEN_CIPHER";

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
		CipherEvents::EventOpenCipher
	);
}
