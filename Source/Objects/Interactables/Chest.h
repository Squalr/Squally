#pragma once
#include "cocos2d.h"
#include "Objects/Collision/CollisionObject.h"

using namespace cocos2d;

class Chest : public CollisionObject
{
public:
	static Chest * create();

	virtual void open();
	virtual void close();

	Node* contentNode;

protected:
	Chest();
	~Chest();

	void update(float) override;

	Sprite* chestOpenLidSprite;
	Sprite* chestOpenFrontSprite;
	Sprite* chestOpenSprite;
	Sprite* chestClosedSprite;
	Sprite* sprite;

};
