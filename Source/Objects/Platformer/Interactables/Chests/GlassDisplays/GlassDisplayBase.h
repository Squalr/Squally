#pragma once

#include "Objects/Platformer/Interactables/Chests/ChestBase.h"

namespace cocos2d
{
	class Sprite;
};

class MinMaxPool;
class WorldSound;

class GlassDisplayBase : public ChestBase
{
public:
protected:
	GlassDisplayBase(cocos2d::ValueMap& properties, cocos2d::CSize interactSize);
	virtual ~GlassDisplayBase();

	void onEnter() override;
	void initializeListeners() override;
	void closeDisplay(bool animate);
	void openDisplay(bool animate);

	cocos2d::Node* displayContentNode = nullptr;

	bool isDisplayOpened = 0.0f;

private:
	typedef ChestBase super;

	float openDelay = 0.0f;

	cocos2d::Node* displayNormal = nullptr;
	cocos2d::Node* displayOpened = nullptr;
	cocos2d::Node* displayLooted = nullptr;

	cocos2d::Sprite* glassDisplayFrontNormal = nullptr;
	cocos2d::Sprite* glassDisplayFrontOpened = nullptr;
	cocos2d::Sprite* glassDisplayFrontLooted = nullptr;

	cocos2d::Sprite* normalGlow = nullptr;
	cocos2d::Sprite* openGlow = nullptr;

	WorldSound* openSound = nullptr;
	WorldSound* closeSound = nullptr;
	WorldSound* notifySound = nullptr;

	static const std::string SaveKeyIsDisplayOpened;
	static const std::string PropertyIsOpened;
	static const std::string PropertyDelay;
};
