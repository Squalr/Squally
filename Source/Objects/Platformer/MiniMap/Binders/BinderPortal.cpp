#include "BinderPortal.h"

#include "cocos/base/ccTypes.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/MiniMap/MiniMapObject.h"

using namespace cocos2d;


BinderPortal* BinderPortal::create()
{
	BinderPortal* instance = new BinderPortal();

	instance->autorelease();

	return instance;
}

BinderPortal::BinderPortal() : super()
{
}

BinderPortal::~BinderPortal()
{
}

void BinderPortal::bindTo(MiniMapObject* miniMapObject, GameObject* gameObject)
{
	super::bindTo(miniMapObject, gameObject);

	this->portal = dynamic_cast<Portal*>(gameObject);
}

void BinderPortal::update(float dt)
{
	super::update(dt);

	if (this->portal == nullptr)
	{
		return;
	}

	this->miniMapObject->setVisible(!this->portal->getIsDisabled());
}
