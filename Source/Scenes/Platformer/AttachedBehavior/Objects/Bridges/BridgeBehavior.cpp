#include "BridgeBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/PlatformerEvents.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string BridgeBehavior::MapKey = "bridge";
const std::string BridgeBehavior::PropertyGroup = "bridge-group";
const std::string BridgeBehavior::PropertyBridgeIndex = "bridge-index";
const std::string BridgeBehavior::SaveKeyRaised = "SAVE_KEY_RAISED";

BridgeBehavior* BridgeBehavior::create(GameObject* owner)
{
	BridgeBehavior* instance = new BridgeBehavior(owner);

	instance->autorelease();

	return instance;
}

BridgeBehavior::BridgeBehavior(GameObject* owner) : super(owner)
{
	this->object = owner;
	this->group = "";
	this->bridgeIndex = 0;
	this->raiseSound = WorldSound::create(SoundResources::Platformer_FX_Woosh_WooshPulse1);

	this->raiseSound->disableZDepth();

	if (this->object == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->group = GameUtils::getKeyOrDefault(this->object->properties, BridgeBehavior::PropertyGroup, Value("")).asString();
		this->bridgeIndex = GameUtils::getKeyOrDefault(this->object->properties, BridgeBehavior::PropertyBridgeIndex, Value(0)).asInt();
	}

	this->addChild(this->raiseSound);
}

BridgeBehavior::~BridgeBehavior()
{
}

void BridgeBehavior::onLoad()
{
	if (this->object->loadObjectStateOrDefault(BridgeBehavior::SaveKeyRaised, Value(false)).asBool())
	{
		return;
	}

	this->originalPosition = this->object->getPosition();
	this->object->setPositionY(this->originalPosition.y - 512.0f);

	this->object->listenForMapEventOnce(this->group, [=](ValueMap args)
	{
		this->object->saveObjectState(BridgeBehavior::SaveKeyRaised, Value(true));
		this->object->runAction(MoveTo::create(0.25f * float(this->bridgeIndex + 1), originalPosition));
		this->object->runAction(Sequence::create(
			DelayTime::create(0.25f * float(this->bridgeIndex + 1) - 0.15f),
			CallFunc::create([=]()
			{
				this->raiseSound->play();
			}),
			nullptr
		));
	});
}

void BridgeBehavior::onDisable()
{
	super::onDisable();
}
