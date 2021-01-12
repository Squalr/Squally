#include "LogicGate.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string LogicGate::MapKey = "logic-gate";
const std::string LogicGate::PropertyGateColor = "gate-color";
const std::string LogicGate::PropertyDelta = "delta";
const std::string LogicGate::PropertyAnswer = "answer";

LogicGate* LogicGate::create(ValueMap& properties)
{
	LogicGate* instance = new LogicGate(properties);
	
	instance->autorelease();

	return instance;
}

LogicGate::LogicGate(ValueMap& properties) : super(properties, InteractType::None, Size(285.0f, 676.0f))
{
	this->torchColorName = GameUtils::getKeyOrDefault(this->properties, GameObject::PropertyColor, Value("")).asString();
	this->gateCollision = CollisionObject::create(CollisionObject::createBox(Size(285.0f, 676.0f)), (CollisionType)PlatformerCollisionType::Solid, CollisionObject::Properties(false, false));
	this->delta = GameUtils::getKeyOrDefault(this->properties, LogicGate::PropertyDelta, Value(512.0f)).asFloat();
	this->answer = GameUtils::getKeyOrDefault(this->properties, LogicGate::PropertyAnswer, Value(false)).asBool();
	this->openSound = WorldSound::create(SoundResources::Platformer_Objects_Machines_WoodMechanism1);
	this->torchColor = Brazier::StrToColor(this->torchColorName);

	std::string gateColor = GameUtils::getKeyOrDefault(this->properties, LogicGate::PropertyGateColor, Value("")).asString();

	if (gateColor == "yellow")
	{
		this->gate = Sprite::create(ObjectResources::Puzzles_LogicGate_LogicGateYellow);
	}
	else
	{
		this->gate = Sprite::create(ObjectResources::Puzzles_LogicGate_LogicGateGray);
	}

	this->gateCollision->addChild(this->gate);
	this->addChild(this->gateCollision);
	this->addChild(this->openSound);
}

LogicGate::~LogicGate()
{
}

void LogicGate::onEnter()
{
	super::onEnter();
}

void LogicGate::initializeListeners()
{
	super::initializeListeners();
}

void LogicGate::onToggle()
{
	super::onToggle();
}

Brazier::TorchColor LogicGate::getTorchColor()
{
	return this->torchColor;
}

void LogicGate::onEnable(bool isInit)
{
	super::onEnable(isInit);

	if (!isInit)
	{
		this->openSound->play();
	}

	this->runGateAnim(isInit);
}

void LogicGate::onDisable(bool isInit)
{
	this->runGateAnim(isInit);
}

void LogicGate::runGateAnim(bool isInstant)
{
	Vec2 endPosition = this->isOn() ? Vec2(0.0f, -this->delta) : Vec2::ZERO;
	float max = std::abs(this->delta);
	float progress = std::abs(this->gateCollision->getPositionY()) / max;
	float relativeProgress = this->isOn() ? (1.0f - progress) : progress;

	this->gateCollision->stopAllActions();

	if (isInstant)
	{
		this->gateCollision->setPosition(endPosition);
	}
	else
	{
		this->gateCollision->runAction(MoveTo::create(relativeProgress * 3.0f, endPosition));

	}
}
