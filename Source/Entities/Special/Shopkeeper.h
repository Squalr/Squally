#pragma once

#include "Engine/SmartNode.h"

class SmartAnimationNode;

class Shopkeeper : public SmartNode
{
public:
	static Shopkeeper* create();

protected:
	Shopkeeper();
	~Shopkeeper();

private:
	SmartAnimationNode* animationNode;
};
