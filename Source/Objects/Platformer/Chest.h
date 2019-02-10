#pragma once

#include "Engine/SmartNode.h"

using namespace cocos2d;

class Chest : public SmartNode
{
public:
	static Chest* create(cocos2d::Node* contentNode);

	virtual void open();
	virtual void close();

protected:
	typedef SmartNode super;
	Chest(cocos2d::Node* contentNode);
	virtual ~Chest();

	cocos2d::Node* content;
	cocos2d::Node* chestOpen;
	cocos2d::Node* chestClosed;
};
