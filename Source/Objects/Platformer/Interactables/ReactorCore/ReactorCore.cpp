#include "ReactorCore.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/PlatformerEvents.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ReactorCore::MapKey = "reactor";

ReactorCore* ReactorCore::create(ValueMap& properties)
{
	ReactorCore* instance = new ReactorCore(properties);

	instance->autorelease();

	return instance;
}

ReactorCore::ReactorCore(ValueMap& properties) : super(properties, InteractObject::InteractType::Input, CSize(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat()))
{
	this->reactorSfx = WorldSound::create(); //SoundResources::Platformer_FX_ServerRoom
	this->reactorCore = Sprite::create(ObjectResources::Interactive_ReactorCore_Reactor);
	this->reactorPad = Sprite::create(ObjectResources::Interactive_ReactorCore_ReactorPad);
	this->reactorCase = Sprite::create(ObjectResources::Interactive_ReactorCore_ReactorCase);

	
	this->contentNode->addChild(this->reactorCore);
	this->contentNode->addChild(this->reactorPad);
	this->contentNode->addChild(this->reactorCase);
	this->addChild(this->reactorSfx);
}

ReactorCore::~ReactorCore()
{
}

void ReactorCore::onEnter()
{
	super::onEnter();
}

void ReactorCore::initializePositions()
{
	super::initializePositions();

	const float HighY = -350.0f;
	const float LowY = -370.0f;

	this->reactorPad->setPositionY(LowY);
	this->reactorPad->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(2.0f, Vec2(0.0f, HighY))),
		EaseSineInOut::create(MoveTo::create(2.0f, Vec2(0.0f, LowY))),
		nullptr
	)));;

	this->reactorCore->setPositionY(-16.0f);
	this->reactorCore->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(1.75f, Vec2(0.0f, 16.0f))),
		EaseSineInOut::create(MoveTo::create(1.75f, Vec2(0.0f, -16.0f))),
		nullptr
	)));;
}

void ReactorCore::onInteract(PlatformerEntity* interactingEntity)
{
	super::onInteract(interactingEntity);
}
