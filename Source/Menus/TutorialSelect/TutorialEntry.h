#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;
class ScrollPane;

class TutorialEntry : public SmartNode
{
public:
	static TutorialEntry* create();

protected:
	TutorialEntry();
	virtual ~TutorialEntry();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	cocos2d::Sprite* back;
	cocos2d::Sprite* frame;
	cocos2d::Sprite* lockIcon;
	cocos2d::Sprite* completeIcon;
};
