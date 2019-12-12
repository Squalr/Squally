#pragma once
#include <set>

#include "Engine/Hackables/HackableObject.h"

class CollisionObject;
class HackableData;
class InteractMenu;

class Portal : public HackableObject
{
public:
	static Portal* create(cocos2d::ValueMap& properties);

	void enable();
	void disable();
	virtual void lock(bool animate = true);
	virtual void unlock(bool animate = true);
	void setRequiresInteraction(bool requiresInteraction);
	void setOpenCallback(std::function<bool()> openCallback);

	static const std::string MapKeyPortal;
	static const std::string MapKeyPortalMap;
	static const std::string MapKeyPortalTransition;

protected:
	Portal(cocos2d::ValueMap& properties, cocos2d::Size size, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO);
	virtual ~Portal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	virtual void loadMap();

	bool requiresInteraction;

private:
	typedef HackableObject super;

	void updateInteractMenuVisibility();
	void enterPortal();

	CollisionObject* portalCollision;
	ClickableNode* lockButton;
	ClickableNode* unlockButton;
	InteractMenu* interactMenu;
	InteractMenu* lockedMenu;

	bool disabled;
	bool canInteract;
	bool wasTripped;
	bool isLocked;
	std::string transition;
	std::string mapFile;
	std::function<bool()> openCallback;
};
