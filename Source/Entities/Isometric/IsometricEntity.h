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
		cocos2d::CSize size = cocos2d::CSize(256.0f, 128.0f));
	virtual ~IsometricEntity();

	void onEnter() override;
	void update(float) override;

	cocos2d::Node* underNode = nullptr;
	SmartAnimationNode* animationNode = nullptr;

	cocos2d::Vec2 movement = cocos2d::Vec2::ZERO;
	
private:
	typedef HackableObject super;
};

