#include "EntityFloatBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityFloatBehavior::MapKey = "entity-float";
const std::string EntityFloatBehavior::MapPropertyDeathSinkHeight = "death-sink-height";

EntityFloatBehavior* EntityFloatBehavior::create(GameObject* owner)
{
	EntityFloatBehavior* instance = new EntityFloatBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityFloatBehavior::EntityFloatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	// Default to values that work well for Squally
	this->deathSinkHeight = GameUtils::getKeyOrDefault(owner->properties, EntityFloatBehavior::MapPropertyDeathSinkHeight, Value(Squally::HoverHeight + 42.0f)).asFloat();
}

EntityFloatBehavior::~EntityFloatBehavior()
{
}

void EntityFloatBehavior::onLoad()
{
	this->scheduleUpdate();
}

void EntityFloatBehavior::onDisable()
{
	super::onDisable();
}

void EntityFloatBehavior::update(float dt)
{
	super::update(dt);

	if (this->entity == nullptr)
	{
		return;
	}

	if (this->entity->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
	{
		this->elapsed += dt;
		this->deathElapsed -= dt;
	}
	else
	{
		this->deathElapsed += dt;
	}

	static const float DeathSinkTime = 0.25f;

	this->deathElapsed = MathUtils::clamp(this->deathElapsed, 0.0f, DeathSinkTime);

	this->entity->getFloatNode()->setPositionY(std::sin(this->elapsed * 1.5f) * 8.0f - (this->deathElapsed / DeathSinkTime) * this->deathSinkHeight);
}
