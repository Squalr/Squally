#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"

using namespace cocos2d;

class GlobalNode : public SmartNode
{
public:
	virtual void pause() override;
	virtual void addEventListener(EventListener* listener) override;
};
