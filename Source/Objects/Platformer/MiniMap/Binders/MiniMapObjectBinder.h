#pragma once

#include "cocos/2d/CCNode.h"

class GameObject;
class MiniMapObject;

class MiniMapObjectBinder : public cocos2d::Node
{
public:
	virtual void bindTo(MiniMapObject* miniMapObject, GameObject* gameObject);

protected:
	MiniMapObjectBinder();
	virtual ~MiniMapObjectBinder();

	void onEnter() override;

	GameObject* gameObjectRaw;
	MiniMapObject* miniMapObject;

private:
	typedef cocos2d::Node super;
};
