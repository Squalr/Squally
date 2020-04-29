#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class LocalizedLabel;
class ScrollPane;

class TutorialEntry : public SmartNode
{
public:
	static TutorialEntry* create(std::string saveKey, TutorialEntry* prereq = nullptr);

	bool isComplete();
	void setClickCallback(std::function<void()> clickCallback);

protected:
	TutorialEntry(std::string saveKey, TutorialEntry* prereq);
	virtual ~TutorialEntry();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	cocos2d::Sprite* back;
	ClickableNode* frame;
	cocos2d::Sprite* lockIcon;
	cocos2d::Sprite* completeIcon;
	
	TutorialEntry* prereq;
	std::string saveKey;
};
