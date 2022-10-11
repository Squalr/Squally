#include "BinderDefault.h"

#include "cocos/base/ccTypes.h"
#include "cocos/base/CCValue.h"

#include "Objects/Platformer/MiniMap/MiniMapObject.h"

using namespace cocos2d;


BinderDefault* BinderDefault::create()
{
	BinderDefault* instance = new BinderDefault();

	instance->autorelease();

	return instance;
}

BinderDefault::BinderDefault() : super()
{
}

BinderDefault::~BinderDefault()
{
}

void BinderDefault::bindTo(MiniMapObject* miniMapObject, GameObject* gameObject)
{
	super::bindTo(miniMapObject, gameObject);
}

void BinderDefault::update(float dt)
{
	super::update(dt);

	if (this->miniMapObject == nullptr || this->gameObjectRaw == nullptr)
	{
		return;
	}

	this->miniMapObject->setPosition(gameObjectRaw->getPosition());
}
