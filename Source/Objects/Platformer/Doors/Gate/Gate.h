#pragma once

#include "Objects/Platformer/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class CollisionObject;
class ConstantString;
class InteractMenu;
class LocalizedLabel;
class SmartAnimationSequenceNode;
class SmartClippingNode;
class Sound;

class Gate : public Portal
{
public:
	static Gate* create(cocos2d::ValueMap& properties);

	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string MapKeyGate;

protected:
	Gate(cocos2d::ValueMap& properties);
	~Gate();

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

	static const cocos2d::Vec2 GateLeftClosedOffset;
	static const cocos2d::Vec2 GateRightClosedOffset;
	static const cocos2d::Vec2 GateLeftOpenedOffset;
	static const cocos2d::Vec2 GateRightOpenedOffset;
};
