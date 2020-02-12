#include "Anvil.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Anvil::MapKeyAnvil = "anvil";

Anvil* Anvil::create(ValueMap& properties)
{
	Anvil* instance = new Anvil(properties);

	instance->autorelease();

	return instance;
}

Anvil::Anvil(ValueMap& properties) : super(properties, InteractObject::InteractType::Input, Size(192.0f, 440.0f))
{
	this->anvil = Sprite::create(ObjectResources::Interactive_Anvil_Anvil);
	this->shine = Sprite::create(UIResources::HUD_EmblemGlow);
	this->hammer = Sprite::create(ObjectResources::Interactive_Anvil_AnvilHammer);
	this->floatContainer = Node::create();
	
	this->floatContainer->addChild(this->shine);
	this->floatContainer->addChild(this->hammer);
	this->addChild(this->anvil);
	this->addChild(this->floatContainer);
}

Anvil::~Anvil()
{
}

void Anvil::onEnter()
{
	super::onEnter();

	this->floatContainer->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(3.0f, Vec2(0.0f, 96.0f))),
		EaseSineInOut::create(MoveTo::create(3.0f, Vec2(0.0f, 160.0f))),
		nullptr
	)));
}

void Anvil::initializePositions()
{
	super::initializePositions();

	this->hammer->setPosition(Vec2(24.0f, 0.0f));
	this->shine->setPosition(Vec2(24.0f, 0.0f));
	this->floatContainer->setPosition(Vec2(0.0f, 160.0f));
	this->anvil->setPosition(Vec2(0.0f, 0.0f));
}

void Anvil::initializeListeners()
{
	super::initializeListeners();
}

void Anvil::onInteract()
{
	super::onInteract();

	PlatformerEvents::TriggerOpenCrafting(PlatformerEvents::CraftingOpenArgs());
}
