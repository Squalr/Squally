#pragma once
#include "cocos2d.h"

#include "Engine/Objects/Hackables/HackableObject.h"

using namespace cocos2d;

class Chest : public HackableObject
{
public:
	static Chest * create(ValueMap* initProperties, Node* contentNode);

	virtual void open();
	virtual void close();

protected:
	Chest(ValueMap* initProperties, Node* contentNode);
	~Chest();

	void update(float) override;

	Node* content;
	Node* chestOpen;
	Node* chestClosed;

};
