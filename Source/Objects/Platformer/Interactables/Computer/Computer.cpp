#include "Computer.h"

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

const std::string Computer::MapKey = "computer";
const std::string Computer::PropertyComputerType = "computer-type";
const std::string Computer::PropertyComputerSfx = "computer-sfx";

Computer* Computer::create(ValueMap& properties)
{
	Computer* instance = new Computer(properties);

	instance->autorelease();

	return instance;
}

Computer::Computer(ValueMap& properties) : super(properties, InteractObject::InteractType::Input, CSize(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat()))
{
	std::string computerType = GameUtils::getKeyOrDefault(this->properties, Computer::PropertyComputerType, Value("console")).asString();
	bool useComputerSfx = GameUtils::getKeyOrDefault(this->properties, Computer::PropertyComputerSfx, Value(false)).asBool();

	if (useComputerSfx)
	{
		this->computerSfx = WorldSound::create(SoundResources::Platformer_FX_ServerRoom);
		this->addChild(this->computerSfx);
	}

	this->animations = SmartAnimationNode::create(ObjectResources::Interactive_Computer_Animations, computerType);
	this->animations->setScale(0.35f);

	this->addChild(this->animations);
}

Computer::~Computer()
{
}

void Computer::onEnter()
{
	super::onEnter();
	
	this->disable();
	this->turnOff();
}

void Computer::initializePositions()
{
	super::initializePositions();

	this->animations->setPositionY(-properties.at(GameObject::MapKeyHeight).asFloat() / 2.0f);
}

void Computer::onInteract(PlatformerEntity* interactingEntity)
{
	super::onInteract(interactingEntity);

	this->broadcastMapEvent(this->getSendEvent(), ValueMap());
	this->disable();
}

void Computer::turnOn()
{
	this->animations->playAnimation("on", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f, 0.5f, true));

	if (this->computerSfx != nullptr)
	{
		this->computerSfx->play(true);
	}
}

void Computer::turnOff()
{
	this->animations->playAnimation("off", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.5f, 0.5f, true));

	if (this->computerSfx != nullptr)
	{
		this->computerSfx->stop();
	}
}
