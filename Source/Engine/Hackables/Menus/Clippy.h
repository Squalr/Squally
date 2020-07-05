#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;
class SpeechBubble;

class Clippy : public SmartNode
{
public:
	void setIsEnabled(bool isEnabled);
	bool getIsEnabled();

	virtual void startDialogue() = 0;

protected:
	Clippy(std::string uniqueRunKey = "");
	virtual ~Clippy();

	void initializePositions() override;
	void runDialogue(LocalizedString* localizedString, std::string soundResource);

	cocos2d::Node* animationNode;

private:
	typedef SmartNode super;

	bool isFirstUniqueRun();

	SpeechBubble* speechBubble;
	bool isEnabled;
	std::string uniqueRunKey;

	static std::map<std::string, bool> UniqueRunMap;
};
