#include "HelpTotem.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

HelpTotem* HelpTotem::create(ValueMap& properties)
{
	HelpTotem* instance = new HelpTotem(properties);

	instance->autorelease();

	return instance;
}

HelpTotem::HelpTotem(ValueMap& properties) : super(properties)
{
	this->totem = Sprite::create(ObjectResources::Interactive_Help_HelpTotem);
	this->hintCollision = CollisionObject::create(PhysicsBody::createBox(Size(248.0f, 248.0f)), (CollisionType)PlatformerCollisionType::Trigger, false, false);
	this->speechBubble = SpeechBubble::create();
	this->hint = nullptr;

	this->addChild(this->totem);
	this->addChild(this->hintCollision);
	this->addChild(this->speechBubble);
}

HelpTotem::~HelpTotem()
{
}

void HelpTotem::onEnter()
{
	super::onEnter();

	if (!this->listenEvent.empty())
	{
		this->setVisible(false);

		this->listenForMapEvent(this->listenEvent, [=](ValueMap args)
		{
			this->setVisible(true);
		});
	}
}

void HelpTotem::initializePositions()
{
	super::initializePositions();

	this->speechBubble->setPosition(Vec2(0.0f, 128.0f));
}

void HelpTotem::initializeListeners()
{
	super::initializeListeners();

	this->hintCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		if (this->hint != nullptr && this->isVisible())
		{
			this->speechBubble->runDialogue(this->hint->clone(), SpeechBubble::InfiniteDuration, nullptr, SpeechBubble::Direction::Centered);
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->hintCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->speechBubble->hideDialogue();
		
		return CollisionObject::CollisionResult::DoNothing;
	});
}

void HelpTotem::setHint(LocalizedString* hint)
{
	if (this->hint != nullptr)
	{
		this->removeChild(this->hint);
	}

	this->hint = hint;

	if (this->hint != nullptr)
	{
		this->addChild(this->hint);
	}
}
