#pragma once
#include <set>

#include "Objects/Platformer/Interactables/InteractObject.h"

class HackableData;
class InteractMenu;

class Portal : public InteractObject
{
public:
	static Portal* create(cocos2d::ValueMap& properties);
	
	virtual void loadMap();

	static const std::string MapKey;
	static const std::string PropertyPortalMap;
	static const std::string PropertyPortalTransition;
	static const std::string PropertyIsLocked;

protected:
	Portal(cocos2d::ValueMap& properties, cocos2d::Size size, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO, cocos2d::Color3B color = cocos2d::Color3B::BLACK);
	virtual ~Portal();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onInteract(PlatformerEntity* interactingEntity) override;

private:
	typedef InteractObject super;

	std::string transition;
	std::string mapFile;
	
	static const std::string SaveKeyListenEventTriggered;
};
