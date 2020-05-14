#pragma once

#include "Objects/Platformer/Interactables/Chests/ChestBase.h"

using namespace cocos2d;

class MinMaxPool;

class GlassDisplayBase : public ChestBase
{
public:
protected:
	GlassDisplayBase(cocos2d::ValueMap& properties, cocos2d::Size interactSize);
	virtual ~GlassDisplayBase();

	void onEnter() override;
	void closeDisplay();
	void openDisplay();

	cocos2d::Node* displayContentNode;

	bool isDisplayOpened;

private:
	typedef ChestBase super;

	cocos2d::Node* displayNormal;
	cocos2d::Node* displayOpened;
	cocos2d::Node* displayLooted;
};
