#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ClickableNode;
class PlatformerEntity;
class SmartClippingNode;

class TutorialEntry : public SmartNode
{
public:
	static TutorialEntry* create(std::string saveKey, TutorialEntry* prereq = nullptr);

	PlatformerEntity* addEntity(PlatformerEntity* entity, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO);
	cocos2d::Node* addContent(cocos2d::Node* content, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO);
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

	cocos2d::Sprite* back = nullptr;
	SmartClippingNode* contentClip = nullptr;
	cocos2d::Node* contentHost = nullptr;
	cocos2d::Node* content = nullptr;
	cocos2d::LayerColor* lockedLayer = nullptr;
	ClickableNode* frame = nullptr;
	cocos2d::Sprite* lockIcon = nullptr;
	cocos2d::Sprite* completeIcon = nullptr;
	
	TutorialEntry* prereq = nullptr;
	std::string saveKey;
};
