#pragma once
#include "cocos2d.h"
#include "Objects/Collision/CollisionObject.h"

using namespace cocos2d;

class Chest : public CollisionObject
{
public:
	static Chest * create(Node* contentNode);

	virtual void open();
	virtual void close();

protected:
	Chest(Node* contentNode);
	~Chest();

	void update(float) override;

	Node* content;
	Node* chestOpen;
	Node* chestClosed;

};
