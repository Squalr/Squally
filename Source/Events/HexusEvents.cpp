#include "HexusEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

#include "Entities/Platformer/PlatformerEntity.h"

using namespace cocos2d;

const std::string HexusEvents::EventOpenHexus = "EVENT_HEXUS_OPEN";
const std::string HexusEvents::EventExitHexus = "EVENT_HEXUS_EXIT";
const std::string HexusEvents::EventCardPreviewed = "EVENT_HEXUS_CARD_PREVIEWED";
const std::string HexusEvents::EventCardMousedOut = "EVENT_HEXUS_CARD_MOUSED_OUT";
const std::string HexusEvents::BeforeRequestStateUpdateEvent = "EVENT_HEXUS_BEFORE_REQUEST_UPDATE_STATE";
const std::string HexusEvents::RequestStateUpdateEvent = "EVENT_HEXUS_REQUEST_UPDATE_STATE";
const std::string HexusEvents::BeforeStateUpdateEvent = "EVENT_HEXUS_BEFORE_UPDATE_STATE";
const std::string HexusEvents::OnStateUpdateEvent = "EVENT_HEXUS_ON_UPDATE_STATE";

void HexusEvents::TriggerOpenHexus(HexusOpenArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HexusEvents::EventOpenHexus,
		&args
	);
}

void HexusEvents::TriggerExitHexus(HexusExitArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HexusEvents::EventExitHexus,
		&args
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

void HexusEvents::TriggerBeforeRequestStateUpdate(GameState* gameState)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HexusEvents::BeforeRequestStateUpdateEvent,
		gameState
	);
}

void HexusEvents::TriggerRequestStateUpdate(GameState* gameState)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HexusEvents::RequestStateUpdateEvent,
		gameState
	);
}

void HexusEvents::TriggerBeforeStateUpdate(GameState* gameState)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HexusEvents::BeforeStateUpdateEvent,
		gameState
	);
}

void HexusEvents::TriggerOnStateUpdate(GameState* gameState)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HexusEvents::OnStateUpdateEvent,
		gameState
	);
}

Node* HexusEvents::BuildPreviewNode(PlatformerEntity* entity)
{
	if (entity == nullptr)
	{
		return nullptr;
	}

	Node* wrapper = Node::create();
	PlatformerEntity* softClone = entity->softClone();

	if (softClone != nullptr)
	{
		wrapper->addChild(softClone);
		softClone->setPosition(Vec2(0.0f, -(softClone->getEntitySize() * softClone->getScale()).height / 2.0f));
	}

	return wrapper;
}
