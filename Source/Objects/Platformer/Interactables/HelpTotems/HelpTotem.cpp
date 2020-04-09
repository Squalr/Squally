#include "HelpTotem.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

HelpTotem* HelpTotem::create(ValueMap& properties)
{
	HelpTotem* instance = new HelpTotem(properties);

	instance->autorelease();

	return instance;
}

HelpTotem::HelpTotem(ValueMap& properties) : super(properties, InteractObject::InteractType::Collision, Size(248.0f, 248.0f), Vec2::ZERO)
{
	this->totem = Sprite::create(ObjectResources::Interactive_Help_HelpTotem);
	this->totemInactive = Sprite::create(ObjectResources::Interactive_Help_HelpTotemDeactivated);
	this->speechBubble = SpeechBubble::create(true);
	this->hint = nullptr;
	this->isInactive = false;

	this->totemInactive->setOpacity(0);

	this->addChild(this->totem);
	this->addChild(this->totemInactive);
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
}

void HelpTotem::onInteract()
{
	this->tryDisplayHint();
}

void HelpTotem::onEndCollision()
{
	this->tryDisplayHint();
}

void HelpTotem::deactivate()
{
	this->isInactive = true;
	this->totem->runAction(FadeTo::create(1.0f, 0));
	this->totemInactive->runAction(FadeTo::create(1.0f, 255));

	this->tryDisplayHint();
}

void HelpTotem::activate()
{
	this->isInactive = false;
	this->totem->runAction(FadeTo::create(1.0f, 255));
	this->totemInactive->runAction(FadeTo::create(1.0f, 0));

	this->tryDisplayHint();
}

void HelpTotem::tryDisplayHint()
{
	if (!this->isInactive && this->canInteract && this->hint != nullptr && this->isVisible())
	{
		this->speechBubble->runDialogue(this->hint->clone(), SoundResources::Platformer_Entities_TikiChatter, SpeechBubble::InfiniteDuration, nullptr, SpeechBubble::Direction::Centered);
	}
	else
	{
		this->speechBubble->hideDialogue();
	}
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
