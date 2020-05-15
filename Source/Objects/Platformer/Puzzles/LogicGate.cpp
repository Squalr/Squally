#include "LogicGate.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string LogicGate::MapKey = "logic-gate";
const std::string LogicGate::PropertyGateColor = "gate-color";
const std::string LogicGate::PropertyDelta = "delta";
const std::string LogicGate::PropertySaveKey = "save-key";

LogicGate* LogicGate::create(ValueMap& properties)
{
	LogicGate* instance = new LogicGate(properties);
	
	instance->autorelease();

	return instance;
}

LogicGate::LogicGate(ValueMap& properties) : super(properties)
{
	this->gateCollision = CollisionObject::create(CollisionObject::createBox(Size(285.0f, 676.0f)), (CollisionType)PlatformerCollisionType::Solid, CollisionObject::Properties(false, false));
	this->torchColor = LogicTorch::StrToColor(GameUtils::getKeyOrDefault(this->properties, LogicTorch::PropertyColor, Value("")).asString());
	this->operation = LogicTorch::StrToOperation(GameUtils::getKeyOrDefault(this->properties, LogicTorch::PropertyOperation, Value("")).asString());
	this->delta = GameUtils::getKeyOrDefault(this->properties, LogicGate::PropertyDelta, Value(512.0f)).asFloat();
	this->saveKey = GameUtils::getKeyOrDefault(this->properties, LogicGate::PropertySaveKey, Value("")).asString();
	this->spawnPosition = Vec2::ZERO;
	this->isOpen = false;

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
}

LogicGate::~LogicGate()
{
}

void LogicGate::onEnter()
{
	super::onEnter();

	this->spawnPosition = this->gateCollision->getPosition();

	if (!this->saveKey.empty())
	{
		this->isOpen = SaveManager::getProfileDataOrDefault(this->saveKey, Value(this->isOpen)).asBool();

		this->listenForMapEvent(LogicTorch::EventTorchLogicSwitchPrefix + this->saveKey, [=](ValueMap)
		{
			this->isOpen = SaveManager::getProfileDataOrDefault(this->saveKey, Value(this->isOpen)).asBool();

			this->runGateAnim();
		});
	}

	this->runGateAnim();
}

void LogicGate::initializeListeners()
{
	super::initializeListeners();
}

void LogicGate::runGateAnim()
{
	this->gateCollision->stopAllActions();
	this->gateCollision->runAction(MoveTo::create(1.0f, this->isOpen ? (this->spawnPosition - Vec2(0.0f, this->delta)) : this->spawnPosition));
}
