#pragma once

#include "Engine/SmartNode.h"

class SpeechBubble;

class Clippy : public SmartNode
{
public:
	Clippy* clone();
	
	void setIsEnabled(bool isEnabled);
	bool getIsEnabled();

protected:
	Clippy();
	~Clippy();

	void initializePositions() override;
	virtual Clippy* innerClone() = 0;

	cocos2d::Node* animationNode;
	SpeechBubble* speechBubble;

private:
	typedef SmartNode super;

	bool isEnabled;
};
