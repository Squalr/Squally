#pragma once
#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;

class SmartNode : public Node
{
public:
	SmartNode();
	~SmartNode();

protected:
	virtual void onEnter() override;
	virtual void initializePositions();
	virtual void initializeListeners();
};

