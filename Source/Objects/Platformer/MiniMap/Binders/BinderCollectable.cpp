#include "BinderCollectable.h"

#include "cocos/base/ccTypes.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/Collectables/Collectable.h"
#include "Objects/Platformer/MiniMap/MiniMapObject.h"

using namespace cocos2d;


BinderCollectable* BinderCollectable::create()
{
	BinderCollectable* instance = new BinderCollectable();

	instance->autorelease();

	return instance;
}

BinderCollectable::BinderCollectable() : super()
{
}

BinderCollectable::~BinderCollectable()
{
}

void BinderCollectable::bindTo(MiniMapObject* miniMapObject, GameObject* gameObject)
{
	super::bindTo(miniMapObject, gameObject);

	this->collectable = dynamic_cast<Collectable*>(gameObject);
}

void BinderCollectable::update(float dt)
{
	super::update(dt);

	if (this->collectable == nullptr)
	{
		return;
	}

	this->miniMapObject->setVisible(!this->collectable->isCollected);
}
