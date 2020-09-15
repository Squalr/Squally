#include "BinderLogicGate.h"

#include "cocos/base/ccTypes.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Puzzles/LogicGate.h"
#include "Objects/Platformer/MiniMap/MiniMapObject.h"

using namespace cocos2d;


BinderLogicGate* BinderLogicGate::create()
{
	BinderLogicGate* instance = new BinderLogicGate();

	instance->autorelease();

	return instance;
}

BinderLogicGate::BinderLogicGate() : super()
{
}

BinderLogicGate::~BinderLogicGate()
{
}

void BinderLogicGate::bindTo(MiniMapObject* miniMapObject, GameObject* gameObject)
{
	super::bindTo(miniMapObject, gameObject);

	this->logicGate = dynamic_cast<LogicGate*>(gameObject);
}

void BinderLogicGate::update(float dt)
{
	super::update(dt);

	if (this->logicGate == nullptr)
	{
		return;
	}

	this->miniMapObject->setPosition(GameUtils::getWorldCoords(this->logicGate->gateCollision));
}
