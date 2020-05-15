#pragma once
#include <set>

#include "Engine/Hackables/HackableObject.h"

class ClickableNode;
class CollisionObject;
class HackableData;
class InteractMenu;
class Scrappy;
class Squally;

class InteractObject : public HackableObject
{
public:
	enum class InteractType
	{
		None,
		Input,
		Collision,
	};

	static InteractObject* create(InteractType interactType, cocos2d::Size size, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO);
	
	void enable();
	void disable();
	void setInteractType(InteractType interactType);
	void setInteractCallback(std::function<bool()> interactCallback);
	void setUnlockable(bool isUnlockable, std::function<bool()> unlockCallback = nullptr);
	virtual void lock(bool animate = true);
	virtual void unlock(bool animate = true);

protected:
	InteractObject(cocos2d::ValueMap& properties, InteractType interactType, cocos2d::Size size, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO);
	virtual ~InteractObject();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void updateInteractMenuVisibility();
	void tryInteractObject();
	virtual void onInteract();
	virtual void onEndCollision();

	InteractType interactType;
	CollisionObject* interactCollision;
	Scrappy* scrappy;
	Squally* squally;

	bool isLocked;
	bool isUnlockable;
	bool disabled;
	bool canInteract;
	bool wasTripped;

private:
	typedef HackableObject super;

	void onStateRefresh();

	InteractMenu* interactMenu;
	InteractMenu* lockedMenu;
	InteractMenu* unlockMenu;

	ClickableNode* lockButton;
	ClickableNode* unlockButton;
	
	std::function<bool()> interactCallback;
	std::function<bool()> unlockCallback;
};
