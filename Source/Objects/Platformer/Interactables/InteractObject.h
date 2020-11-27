#pragma once
#include <set>

#include "cocos/base/CCInputEvents.h"

#include "Engine/Hackables/HackableObject.h"

class ClickableNode;
class CollisionObject;
class ConstantString;
class HackableData;
class InteractMenu;
template <class T>
class LazyNode;
class LocalizedString;
class PlatformerEntity;
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

	static InteractObject* create(
		InteractType interactType,
		cocos2d::Size size,
		cocos2d::Vec2 offset = cocos2d::Vec2::ZERO,
		LocalizedString* actionStr = nullptr,
		cocos2d::InputEvents::KeyCode input = cocos2d::InputEvents::KeyCode::KEY_V,
		cocos2d::Color3B interactColor = cocos2d::Color3B::BLACK,
		cocos2d::Color4F debugColor = cocos2d::Color4F::MAGENTA,
		bool disableLockDebug = false
	);
	
	void enable();
	void disable();
	void setInteractType(InteractType interactType);
	void setInteractCallback(std::function<bool()> interactCallback);
	void setUnlockable(bool isUnlockable, std::function<bool()> unlockCallback = nullptr);
	bool getIsLocked();
	bool getIsDisabled();
	virtual void lock(bool animate = true);
	virtual void unlock(bool animate = true);

protected:
	InteractObject(cocos2d::ValueMap& properties,
		InteractType interactType,
		cocos2d::Size size,
		cocos2d::Vec2 offset = cocos2d::Vec2::ZERO,
		LocalizedString* actionStr = nullptr,
		cocos2d::InputEvents::KeyCode input = cocos2d::InputEvents::KeyCode::KEY_V,
		cocos2d::Color3B interactColor = cocos2d::Color3B::BLACK,
		cocos2d::Color4F debugColor = cocos2d::Color4F::MAGENTA,
		bool disableLockDebug = false
	);
	virtual ~InteractObject();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void updateInteractMenuVisibility();
	void tryInteractObject(PlatformerEntity* interactingEntity);
	virtual void onInteract(PlatformerEntity* interactingEntity);
	virtual void onEndCollision();

	InteractType interactType;
	cocos2d::Node* backNode;
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
	std::string inputToString(cocos2d::InputEvents::KeyCode input);

	cocos2d::InputEvents::KeyCode input;
	LocalizedString* interactKeyStr;
	ConstantString* unlockKeyStr;
	
	LazyNode<InteractMenu>* interactMenu;
	LazyNode<InteractMenu>* lockedMenu;
	LazyNode<InteractMenu>* unlockMenu;

	ClickableNode* lockButton;
	ClickableNode* unlockButton;
	
	std::function<bool()> interactCallback;
	std::function<bool()> unlockCallback;
};
