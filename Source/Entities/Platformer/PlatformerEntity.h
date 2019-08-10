#pragma once

#include "cocos/math/CCGeometry.h"

#include "Engine/Hackables/HackableObject.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class ClickableNode;
class CurrencyInventory;
class EquipmentInventory;
class HackablePreview;
class HexusOpponentData;
class Inventory;
class PlatformerAttack;
class SmartAnimationNode;
class SpeechBubble;

class PlatformerEntity : public HackableObject
{
public:
	enum class ControlState
	{
		Normal,
		Swimming,
	};

	std::string getEntityName();
	void disablePlatformerControls();
	bool getIsPlatformerDisabled();
	virtual float getFloatHeight();

	std::vector<PlatformerAttack*> getAttacks();
	std::vector<PlatformerAttack*> getAvailableAttacks();
	std::vector<PlatformerAttack*> cloneAttacks();
	Inventory* getInventory();
	CurrencyInventory* getCurrencyInventory();
	float getScale();
	std::string getAnimationResource();
	std::string getEmblemResource();
	SmartAnimationNode* getAnimations();
	cocos2d::Size getEntitySize();
	HexusOpponentData* getHexusOpponentData();
	virtual cocos2d::Vec2 getAvatarFrameOffset() = 0;

	SpeechBubble* speechBubble;
	SmartAnimationNode* animationNode;

protected:
	PlatformerEntity(
		cocos2d::ValueMap& properties,
		std::string scmlResource,
		std::string emblemResource,
		PlatformerCollisionType collisionType,
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		float hoverHeight = 0.0f,
		std::string inventorySaveKey = "",
		std::string equipmentSaveKey = "",
		std::string currencySaveKey = "");
	~PlatformerEntity();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;
	void registerAttack(PlatformerAttack* attack);
	virtual void performSwimAnimation();
	virtual void performJumpAnimation();
	void doOutOfCombatAttack();

	CollisionObject* entityCollision;
	CollisionObject* weaponCollision;
	HexusOpponentData* hexusOpponentData;
	Inventory* inventory;
	EquipmentInventory* equipmentInventory;
	CurrencyInventory* currencyInventory;
	cocos2d::Vec2 spawnCoords;

	virtual void rebuildWeaponCollision(cocos2d::Size size);
	
	bool isCinimaticHijacked;
	bool isPlatformerDisabled;
	std::string state;

	float entityScale;
	cocos2d::Vec2 entityCollisionOffset;
	cocos2d::Size entitySize;
	cocos2d::Size movementSize;
	ControlState controlState;

	static const float MoveAcceleration;
	static const cocos2d::Vec2 SwimAcceleration;
	static const cocos2d::Size DefaultWeaponSize;
	static const float SwimVerticalDrag;
	static const float JumpVelocity;
	static const std::string MapKeyPropertyState;

private:
	typedef HackableObject super;
	friend class EntityCollisionBehaviorGroup;
	friend class EntityDebugBehaviors;
	friend class EntityGroundCollisionBehaviors;
	friend class EntityMovementBehaviorBase;
	friend class EntityOutOfCombatAttackBehaviorBase;
	friend class EntityMovementCollisionBehaviors;
	friend class EntitySelectionBehavior;
	friend class EntityHealthBehaviorBase;

	float hoverHeight;
	float scale;
	std::string entityName;
	PlatformerCollisionType collisionType;
	std::string animationResource;
	std::string emblemResource;
	std::vector<PlatformerAttack*> attacks;
	cocos2d::Vec2 hackButtonOffset;
};
