#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class DrawNode;
}

class LocalizedLabel;
class LocalizedString;
 
class SpeechBubble : public SmartNode
{
public:
	static SpeechBubble* create(bool uiBound = true);

	enum class Direction
	{
		ExpandLeft,
		ExpandRight,
		Centered,
		Auto
	};

	void runDialogue(LocalizedString* localizedString, Direction direction = Direction::Auto);
	void hideDialogue();

private:
	typedef SmartNode super;
	SpeechBubble(bool uiBound);
	virtual ~SpeechBubble();

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::DrawNode* stem;
	cocos2d::DrawNode* bubble;
	LocalizedLabel* text;

	bool uiBound;

	static const cocos2d::Color4F BubbleColor;
	static const cocos2d::Color4F BubbleEdgeColor;
	static const cocos2d::Color4B BubbleTextColor;
	static const float BubbleBorderSize;
};
