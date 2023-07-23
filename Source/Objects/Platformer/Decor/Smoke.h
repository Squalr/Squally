#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
};

class SmartAnimationSequenceNode;

class Smoke : public GameObject
{
public:
	static Smoke* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Smoke(cocos2d::ValueMap& properties);
	virtual ~Smoke();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef GameObject super;
	
	SmartAnimationSequenceNode* smoke = nullptr;

	bool isCulled = false;
};
