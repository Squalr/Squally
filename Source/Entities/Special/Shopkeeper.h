#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

class Shopkeeper : public Node
{
public:
	static Shopkeeper* create();

protected:
	Shopkeeper();
	~Shopkeeper();

private:
	AnimationNode* animationNode;
};
