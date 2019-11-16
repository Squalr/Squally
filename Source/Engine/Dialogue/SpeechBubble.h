#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class DrawNode;
}

class LocalizedLabel;
class LocalizedString;
class WorldSound;
 
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

	void runDialogue(LocalizedString* localizedString, std::string soundResource, float sustainDuration = 4.0f, std::function<void()> onComplete = nullptr, Direction direction = Direction::Auto);
	void hideDialogue();

	static const float InfiniteDuration;

private:
	typedef SmartNode super;
	SpeechBubble(bool uiBound);
	~SpeechBubble();

	void onEnter() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::DrawNode* stem;
	cocos2d::DrawNode* bubble;
	LocalizedLabel* text;
	WorldSound* voiceSound;

	bool uiBound;

	static const cocos2d::Color4F BubbleColor;
	static const cocos2d::Color4F BubbleEdgeColor;
	static const cocos2d::Color4B BubbleTextColor;
	static const float BubbleBorderSize;
};
