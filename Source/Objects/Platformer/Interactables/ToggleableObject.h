#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

class SmartAnimationSequenceNode;

class ToggleableObject : public InteractObject
{
public:
	bool isOn();
	void enable();
	void disable();

protected:
	ToggleableObject(cocos2d::ValueMap& properties,
		InteractType interactType,
		cocos2d::Size size,
		cocos2d::Size cullPadding = cocos2d::Size(64.0f, 64.0f),
		cocos2d::Vec2 offset = cocos2d::Vec2::ZERO,
		LocalizedString* actionStr = nullptr,
		cocos2d::InputEvents::KeyCode input = cocos2d::InputEvents::KeyCode::KEY_V,
		cocos2d::Color3B interactColor = cocos2d::Color3B::BLACK,
		cocos2d::Color4F debugColor = cocos2d::Color4F::MAGENTA,
		bool disableLockDebug = false
	);
	virtual ~ToggleableObject();

	void onEnter() override;
	void update(float dt) override;
	void onInteract(PlatformerEntity* interactingEntity) override;
	virtual void onToggle();
	virtual void onEnable(bool isInit);
	virtual void onDisable(bool isInit);
	virtual void onOptimizationHide();
	virtual void onOptimizationShow();

	cocos2d::Node* cullNode;
	cocos2d::Node* backOnNode;
	cocos2d::Node* backOffNode;
	cocos2d::Node* backNode;
	cocos2d::Node* onNode;
	cocos2d::Node* offNode;
	cocos2d::Node* frontNode;

	bool isCulled;

private:
	typedef InteractObject super;

	void optimizationHideOffscreenToggleableObject();

	cocos2d::Size cullPadding;
	bool originalToggleValue;
	bool isToggledOn;
	bool isOneUse;
	float cooldown;
	std::string saveKey;

	static const std::string PropertyIsOn;
	static const std::string PropertyIsOneUse;
	static const std::string PropertyIsInteractable;
	static const std::string PropertySaveKey;
};
