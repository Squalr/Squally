#pragma once

#include "Engine/SmartNode.h"

class SpeechBubble;

class Clippy : public SmartNode
{
public:
	virtual Clippy* clone() = 0;

protected:
	Clippy();
	~Clippy();

	void initializePositions() override;

	cocos2d::Node* animationNode;
	SpeechBubble* speechBubble;

private:
	typedef SmartNode super;
};
