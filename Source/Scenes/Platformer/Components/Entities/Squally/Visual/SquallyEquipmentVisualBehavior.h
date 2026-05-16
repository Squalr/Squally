#pragma once

#include <map>
#include <string>
#include <vector>

#include "Engine/Components/GameComponent.h"

class ConstantString;
class EntityInventoryBehavior;
class LocalizedLabel;
class Squally;

class SquallyEquipmentVisualBehavior : public GameComponent
{
public:
	static SquallyEquipmentVisualBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyEquipmentVisualBehavior(GameObject* owner);
	virtual ~SquallyEquipmentVisualBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	enum class DebugEquipmentSlot
	{
		Mainhand = 0,
		Offhand = 1,
		Hat = 2,
	};

	enum class DebugOffsetTarget
	{
		Visual = 0,
		WeaponCollision = 1,
	};
	
	void initializeDebugEquipment();
	void initializeDebugKeybindings();
	void refreshDebugHud();
	void initializeOffsetLabValidation();
	void enforceOffsetLabValidationEquipment(int remainingAttempts);
	void beginOffsetLabAutomation();
	void captureOffsetLabAutomationFrame(const std::string& captureLabel);
	void finalizeOffsetLabAutomation();
	void forceAutomationPose(bool flippedX);
	bool saveSceneCapture(const std::string& outputFilePath) const;
	std::string getOffsetLabArtifactsDirectory() const;
	bool isOffsetLabValidationMap() const;
	void syncDebugSelectionToEquipment();
	void cycleDebugSlot(int direction);
	void cycleDebugItem(int direction);
	void toggleDebugOffsetTarget();
	void nudgeSelectedDebugOffset(const cocos2d::Vec2& delta);
	void resetSelectedDebugOffset();
	void exportSelectedDebugOffset();
	void exportAllDebugOffsets();
	void equipDebugItem(const std::string& itemKey);

	std::vector<std::string>& getDebugCatalog(DebugEquipmentSlot slot);
	const std::vector<std::string>& getDebugCatalog(DebugEquipmentSlot slot) const;
	int& getDebugSelectionIndex(DebugEquipmentSlot slot);
	int getDebugSelectionIndex(DebugEquipmentSlot slot) const;
	std::string getDebugSlotName(DebugEquipmentSlot slot) const;
	std::string getDebugOffsetTargetName() const;
	DebugEquipmentSlot getDebugSlotForItem(const std::string& itemKey) const;
	std::string getEquippedItemKey(DebugEquipmentSlot slot) const;
	std::string getSelectedDebugItemKey() const;
	cocos2d::Vec2 getDebugOffsetForItem(const std::string& itemKey) const;
	cocos2d::Vec2 getDebugWeaponCollisionOffsetForItem(const std::string& itemKey) const;
	cocos2d::Vec2 getBaseOffsetForItem(const std::string& itemKey) const;
	cocos2d::Vec2 getBaseWeaponCollisionOffsetForItem(const std::string& itemKey) const;
	std::string getDebugLayoutName() const;
	bool isDebugModifierPressed() const;
	bool isDebugPrecisionModifierPressed() const;
	std::string formatVec2(const cocos2d::Vec2& value) const;

	void updateEquipmentVisual();

	EntityInventoryBehavior* entityInventoryBehavior = nullptr;
	std::map<std::string, cocos2d::Vec2> debugOffsetsByItem;
	std::map<std::string, cocos2d::Vec2> debugWeaponCollisionOffsetsByItem;
	std::vector<std::string> debugWeaponKeys;
	std::vector<std::string> debugHatKeys;
	std::vector<std::string> debugOffhandKeys;
	DebugEquipmentSlot debugSelectedSlot = DebugEquipmentSlot::Mainhand;
	DebugOffsetTarget debugOffsetTarget = DebugOffsetTarget::Visual;
	int debugSelectedWeaponIndex = 0;
	int debugSelectedHatIndex = 0;
	int debugSelectedOffhandIndex = 0;
	cocos2d::Node* debugHud = nullptr;
	ConstantString* debugHudStr = nullptr;
	LocalizedLabel* debugHudLabel = nullptr;
	Squally* squally = nullptr;
	bool offsetLabAutomationStarted = false;

	static const bool InvertDebugControls;
	static const float DebugNudgeAmount;
	static const float DebugPrecisionNudgeAmount;
};
