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

	void runDialogue(LocalizedString* localizedString, std::string soundResource, float sustainDuration = 4.0f, std::function<void()> onComplete = nullptr, Direction direction = Direction::Auto, bool instant = false);
	bool isRunning();
	void hideDialogue();

	static const float InfiniteDuration;

protected:
	SpeechBubble(bool uiBound);
	virtual ~SpeechBubble();

private:
	typedef SmartNode super;
	
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Node* speechBubbleNode = nullptr;
	cocos2d::DrawNode* stem = nullptr;
	cocos2d::DrawNode* bubble = nullptr;
	LocalizedLabel* text = nullptr;
	WorldSound* voiceSound = nullptr;

	bool isDialogueRunning = false;
	bool hasBound = false;
	bool uiBound = false;

	static const cocos2d::Color4F BubbleColor;
	static const cocos2d::Color4F BubbleEdgeColor;
	static const cocos2d::Color4B BubbleTextColor;
	static const float BubbleBorderSize;
};
