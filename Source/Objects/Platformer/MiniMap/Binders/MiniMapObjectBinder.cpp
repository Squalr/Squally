#include "MiniMapObjectBinder.h"

#include "cocos/base/ccTypes.h"
#include "cocos/base/CCValue.h"

using namespace cocos2d;

MiniMapObjectBinder::MiniMapObjectBinder() : super()
{
	this->miniMapObject = nullptr;
	this->gameObjectRaw = nullptr;
}

MiniMapObjectBinder::~MiniMapObjectBinder()
{
}

void MiniMapObjectBinder::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void MiniMapObjectBinder::bindTo(MiniMapObject* miniMapObject, GameObject* gameObject)
{
	this->miniMapObject = miniMapObject;
	this->gameObjectRaw = gameObject;
}
