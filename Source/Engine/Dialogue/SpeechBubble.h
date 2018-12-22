#pragma once
#include "cocos/math/CCGeometry.h"

#include "Engine/SmartNode.h"

class SpeechBubble : public SmartNode
{
public:
	static SpeechBubble* create();

private:
	SpeechBubble();
	virtual ~SpeechBubble();
};
