#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;

class EdgeLanternGate : public Portal
{
public:
	static EdgeLanternGate* create(cocos2d::ValueMap& properties);

	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string MapKey;

protected:
	EdgeLanternGate(cocos2d::ValueMap& properties);
	virtual ~EdgeLanternGate();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef Portal super;

	cocos2d::Sprite* gateBack;
	cocos2d::Sprite* gateFront;

	ClickableNode* lockButton;
	ClickableNode* unlockButton;
};
