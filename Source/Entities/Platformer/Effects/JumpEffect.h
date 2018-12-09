#pragma once
#include "Engine/SmartNode.h"

class JumpEffect : public SmartNode
{
public:
	static JumpEffect* create();

private:
	JumpEffect();
	virtual ~JumpEffect();
};
