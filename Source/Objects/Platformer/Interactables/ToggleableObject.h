#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

class SmartAnimationSequenceNode;

class ToggleableObject : public InteractObject
{
public:
	bool isOn();
	void toggle(bool enabled, bool isInstant = true);
	void enable(bool isInstant = true);
	void disable(bool isInstant = true);

	std::string getSaveKey() const { return this->saveKey; }

	static const std::string MapEventToggledBySave;

protected:
	ToggleableObject(cocos2d::ValueMap& properties,
		InteractType interactType,
		cocos2d::CSize size,
		cocos2d::CSize cullPadding = cocos2d::CSize(64.0f, 64.0f),
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
	virtual void onToggle(bool isInstant = true);
	virtual void onEnable(bool isInit, bool isInstant = true);
	virtual void onDisable(bool isInit, bool isInstant = true);
	virtual void onOptimizationHide();
	virtual void onOptimizationShow();

	cocos2d::Node* cullNode = nullptr;
	cocos2d::Node* backOnNode = nullptr;
	cocos2d::Node* backOffNode = nullptr;
	cocos2d::Node* backNode = nullptr;
	cocos2d::Node* onNode = nullptr;
	cocos2d::Node* offNode = nullptr;
	cocos2d::Node* frontNode = nullptr;
	bool isCulled = false;

private:
	typedef InteractObject super;

	void loadSaveState();
	void optimizationHideOffscreenToggleableObject();

	cocos2d::CSize cullPadding;
	bool originalToggleValue = false;
	bool isToggledOn = false;
	bool isOneUse = false;
	bool isGlobalSave = false;
	float cooldown = 0.0f;
	std::string saveKey;

	static const std::string PropertyIsOn;
	static const std::string PropertyIsOneUse;
	static const std::string PropertyIsInteractable;
	static const std::string PropertyIsGlobalSave;
	static const std::string PropertySaveKey;
};
