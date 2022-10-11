#include "BinderDensityObject.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/ccTypes.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Physics/DensityObject.h"
#include "Objects/Platformer/MiniMap/MiniMapObject.h"

using namespace cocos2d;


BinderDensityObject* BinderDensityObject::create()
{
	BinderDensityObject* instance = new BinderDensityObject();

	instance->autorelease();

	return instance;
}

BinderDensityObject::BinderDensityObject() : super()
{
}

BinderDensityObject::~BinderDensityObject()
{
}

void BinderDensityObject::bindTo(MiniMapObject* miniMapObject, GameObject* gameObject)
{
	super::bindTo(miniMapObject, gameObject);

	this->densityObject = dynamic_cast<DensityObject*>(gameObject);
}

void BinderDensityObject::update(float dt)
{
	super::update(dt);

	if (this->densityObject == nullptr)
	{
		return;
	}

	this->miniMapObject->drawNode->setPositionY(-this->densityObject->heightRange / 2.0f + this->densityObject->currentDensity * this->densityObject->heightRange);
}
