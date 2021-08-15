#pragma once
#include <set>

#include "cocos/base/CCInputEvents.h"

#include "Engine/Hackables/HackableObject.h"

class ClickableNode;
class CollisionObject;
class ConstantString;
class HackableData;
class InteractMenu;
template <class T> class LazyNode;
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
		cocos2d::CSize size,
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
	bool isInteractable() const;
	bool getIsLocked() const;
	bool getIsDisabled() const;
	virtual void lock(bool animate = true);
	virtual void unlock(bool animate = true);

protected:
	InteractObject(cocos2d::ValueMap& properties,
		InteractType interactType,
		cocos2d::CSize size,
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

	// This exists to allow for adding objects that render below the interact collision for hitbox debugging
	cocos2d::Node* contentNode = nullptr;
	InteractType interactType = InteractType::None;
	CollisionObject* interactCollision = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;

	bool isLocked = false;
	bool isUnlockable = false;
	bool disabled = false;
	bool canInteract = false;
	bool wasTripped = false;

private:
	typedef HackableObject super;

	void onStateRefresh();
	std::string inputToString(cocos2d::InputEvents::KeyCode input);

	cocos2d::InputEvents::KeyCode input;
	LocalizedString* interactKeyStr = nullptr;
	ConstantString* unlockKeyStr = nullptr;
	
	LazyNode<InteractMenu>* interactMenu = nullptr;
	LazyNode<InteractMenu>* lockedMenu = nullptr;
	LazyNode<InteractMenu>* unlockMenu = nullptr;

	ClickableNode* lockButton = nullptr;
	ClickableNode* unlockButton = nullptr;
	
	std::function<bool()> interactCallback = nullptr;
	std::function<bool()> unlockCallback = nullptr;
};
