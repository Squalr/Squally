#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class JumpEffect : public SmartNode
{
public:
	static JumpEffect* create();

private:
	JumpEffect();
	~JumpEffect();
};
