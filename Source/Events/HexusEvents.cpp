#include "HexusEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string HexusEvents::EventOpenHexus = "EVENT_OPEN_HEXUS";
const std::string HexusEvents::EventExitHexus = "EVENT_EXIT_HEXUS";
const std::string HexusEvents::EventCardPreviewed = "EVENT_CARD_PREVIEWED";
const std::string HexusEvents::EventCardMousedOut = "EVENT_CARD_MOUSED_OUT";

void HexusEvents::TriggerOpenHexus(HexusOpenArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HexusEvents::EventOpenHexus,
		&args
	);
}

void HexusEvents::TriggerExitHexus()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HexusEvents::EventExitHexus
	);
}

void HexusEvents::TriggerCardPreviewed(CardPreviewArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HexusEvents::EventCardPreviewed,
		&args
	);
}

void HexusEvents::TriggerCardMousedOut()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HexusEvents::EventCardMousedOut
	);
}
