#include "ZFadeBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"

using namespace cocos2d;

const std::string ZFadeBehavior::MapKey = "z-fade";
const std::string ZFadeBehavior::PropertyFadeMultiplier = "fade-multiplier";

ZFadeBehavior* ZFadeBehavior::create(GameObject* owner)
{
	ZFadeBehavior* instance = new ZFadeBehavior(owner);

	instance->autorelease();

	return instance;
}

ZFadeBehavior::ZFadeBehavior(GameObject* owner) : super(owner)
{
	this->object = owner;

	if (this->object == nullptr)
	{
		this->invalidate();
	}

	this->multiplier = GameUtils::getKeyOrDefault(owner->properties, ZFadeBehavior::PropertyFadeMultiplier, Value(1.0f)).asFloat();
}

ZFadeBehavior::~ZFadeBehavior()
{
}

void ZFadeBehavior::onLoad()
{
	this->scheduleUpdate();
}

void ZFadeBehavior::onDisable()
{
	super::onDisable();

	this->object->setOpacity(255);
}

void ZFadeBehavior::update(float dt)
{
	super::update(dt);

	const float Increment = 64.0f;
	const float HalfIncrement = Increment / 2.0f;

	float depth = GameUtils::getDepth(this->object);

	if (depth >= (GameCamera::getInstance()->getTargetDepth() + Increment * 6 + HalfIncrement))
	{
		this->object->setOpacity(GLubyte(64.0f * this->multiplier));
	}
	else if (depth >= (GameCamera::getInstance()->getTargetDepth() + HalfIncrement))
	{
		this->object->setOpacity(GLubyte(127.0f * this->multiplier));
	}
	else
	{
		this->object->setOpacity(GLubyte(255.0f * this->multiplier));
	}
}
