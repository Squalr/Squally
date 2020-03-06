#pragma once
#include <set>

#include "Engine/Hackables/HackableObject.h"

class ClickableNode;
class CollisionObject;
class HackableData;
class InteractMenu;

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
	void setOpenCallback(std::function<bool()> openCallback);
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

	bool isLocked;
	bool disabled;
	bool canInteract;
	bool wasTripped;

private:
	typedef HackableObject super;

	void onStateRefresh();

	InteractMenu* interactMenu;
	InteractMenu* lockedMenu;

	ClickableNode* lockButton;
	ClickableNode* unlockButton;
	
	std::function<bool()> interactCallback;
};
