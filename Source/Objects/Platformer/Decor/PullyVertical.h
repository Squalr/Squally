#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
};

class SmartAnimationSequenceNode;

class PullyVertical : public GameObject
{
public:
	static PullyVertical* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	PullyVertical(cocos2d::ValueMap& properties);
	virtual ~PullyVertical();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef GameObject super;
	
	cocos2d::Sprite* wheel;
	SmartAnimationSequenceNode* rope;
};
