#pragma once

#include "Engine/SmartNode.h"

class SmartAnimationNode;

class Shopkeeper : public SmartNode
{
public:
	static Shopkeeper* create();

protected:
	Shopkeeper();
	virtual ~Shopkeeper();

private:
	typedef SmartNode super;
	SmartAnimationNode* animationNode;
};
