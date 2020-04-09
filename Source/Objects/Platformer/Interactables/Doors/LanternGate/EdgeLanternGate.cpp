#include "EdgeLanternGate.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string EdgeLanternGate::MapKey = "edge-lantern-gate";

EdgeLanternGate* EdgeLanternGate::create(ValueMap& properties)
{
	EdgeLanternGate* instance = new EdgeLanternGate(properties);

	instance->autorelease();

	return instance;
}

EdgeLanternGate::EdgeLanternGate(ValueMap& properties) : super(properties, Size(356.0f, 320.0f), Vec2(0.0f, 0.0f))
{
	this->gateBack = Sprite::create(ObjectResources::Doors_LanternGate_LanternRight);
	this->gateFront = Sprite::create(ObjectResources::Doors_LanternGate_LanternRight);

	if (GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipX, Value(false)).asBool())
	{
		this->gateBack->setFlippedX(true);
		this->gateFront->setFlippedX(true);
	}

	this->addChild(this->gateBack);
	this->addChild(this->gateFront);
}

EdgeLanternGate::~EdgeLanternGate()
{
}

void EdgeLanternGate::onEnter()
{
	super::onEnter();

	this->defer([=]()
	{
		ObjectEvents::TriggerElevateObject(ObjectEvents::RelocateObjectArgs(this->gateFront));
	});
}

void EdgeLanternGate::initializePositions()
{
	super::initializePositions();

	const float OffsetX = 8.0f;
	const float OffsetY = 24.0f;
	
	if (GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipX, Value(false)).asBool())
	{
		this->gateBack->setPosition(Vec2(OffsetX + 48.0f, OffsetY));
		this->gateFront->setPosition(Vec2(OffsetX - 48.0f, OffsetY - 32.0f));
	}
	else
	{
		this->gateBack->setPosition(Vec2(OffsetX - 48.0f, OffsetY));
		this->gateFront->setPosition(Vec2(OffsetX + 48.0f, OffsetY - 32.0f));
	}
}

void EdgeLanternGate::initializeListeners()
{
	super::initializeListeners();
}

Vec2 EdgeLanternGate::getButtonOffset()
{
	return Vec2(-286.0f, -128.0f);
}

HackablePreview* EdgeLanternGate::createDefaultPreview()
{
	return nullptr;
}

void EdgeLanternGate::lock(bool animate)
{
	super::lock(animate);
}

void EdgeLanternGate::unlock(bool animate)
{
	super::unlock(animate);
}
