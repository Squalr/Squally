#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;

class LanternGate : public Portal
{
public:
	static LanternGate* create(cocos2d::ValueMap& properties);

	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string MapKeyLanternGate;

protected:
	LanternGate(cocos2d::ValueMap& properties);
	virtual ~LanternGate();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef Portal super;

	cocos2d::Sprite* gateRight;
	cocos2d::Sprite* gateLeft;

	ClickableNode* lockButton;
	ClickableNode* unlockButton;
};
