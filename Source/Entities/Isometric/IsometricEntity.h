#pragma once

#include "Engine/Hackables/HackableObject.h"

class SmartAnimationNode;

class IsometricEntity : public HackableObject
{
protected:
	IsometricEntity(
		cocos2d::ValueMap& properties,
		std::string scmlResource,
		float scale = 1.0f,
		cocos2d::Vec2 offset = cocos2d::Vec2(0.0f, 0.0f),
		cocos2d::Size size = cocos2d::Size(256.0f, 128.0f));
	~IsometricEntity();

	void onEnter() override;
	void update(float) override;

	cocos2d::Node* underNode;
	SmartAnimationNode* animationNode;

	cocos2d::Vec2 movement;
private:
	typedef HackableObject super;
};

