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
	GlassDisplayBase(cocos2d::ValueMap& properties, cocos2d::Size interactSize);
	virtual ~GlassDisplayBase();

	void onEnter() override;
	void initializeListeners() override;
	void closeDisplay(bool animate);
	void openDisplay(bool animate);

	cocos2d::Node* displayContentNode;

	bool isDisplayOpened;

private:
	typedef ChestBase super;

	float openDelay;

	cocos2d::Node* displayNormal;
	cocos2d::Node* displayOpened;
	cocos2d::Node* displayLooted;

	cocos2d::Sprite* glassDisplayFrontNormal;
	cocos2d::Sprite* glassDisplayFrontOpened;
	cocos2d::Sprite* glassDisplayFrontLooted;

	cocos2d::Sprite* normalGlow;
	cocos2d::Sprite* openGlow;

	WorldSound* openSound;
	WorldSound* closeSound;
	WorldSound* notifySound;

	static const std::string SaveKeyIsDisplayOpened;
	static const std::string PropertyIsOpened;
	static const std::string PropertyDelay;
};
