#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;
class SpeechBubble;

class Clippy : public SmartNode
{
public:
	// Shallower clone that gets its properties from the original (ie whether it is enabled)
	Clippy* refClone();

	// True clone
	Clippy* clone();
	
	void setIsEnabled(bool isEnabled);
	bool getIsEnabled();

protected:
	Clippy();
	~Clippy();

	void initializePositions() override;
	virtual Clippy* innerClone() = 0;
	void runDialogue(LocalizedString* localizedString, std::string soundResource);

	cocos2d::Node* animationNode;

private:
	typedef SmartNode super;

	Clippy* cloneRef;
	SpeechBubble* speechBubble;
	bool isEnabled;
};
