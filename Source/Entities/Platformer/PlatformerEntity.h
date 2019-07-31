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
	int getHealth();
	void addHealth(int healthDelta);
	void setHealth(int health);
	virtual void kill(bool loadDeadAnim = false);
	virtual void revive();
	int getMaxHealth();
	bool isAlive();
	bool isDead();
	int getMana();
	void addMana(int manaDelta);
	void setMana(int mana);
	int getMaxMana();
	int getAvailableRunes();
	bool tryUseRune();
	float getRuneCooldown(int runeIndex);
	void setRuneCooldown(int runeIndex, float cooldown);
	int getMaxRunes();
	void setEq(int eq);
	int getEq();
	bool setEqExperience(int eqExperience);
	bool addEqExperience(int eqExperience);
	int getEqExperience();
	void disablePlatformerControls();
	bool getIsPlatformerDisabled();
	virtual float getFloatHeight();

	void killAndRespawn();
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
	CollisionObject* getCollision();
	virtual cocos2d::Vec2 getAvatarFrameOffset() = 0;

	ClickableNode* clickHitbox;
	SpeechBubble* speechBubble;
	SmartAnimationNode* animationNode;

	static const int FallBackMaxHealth;
	static const int FallBackMaxMana;
	static const int MaxRunes;
	static const float RuneCooldown;

protected:
	PlatformerEntity(
		cocos2d::ValueMap& properties,
		std::string scmlResource,
		std::string emblemResource,
		PlatformerCollisionType collisionType,
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		int baseHealth,
		int baseSpecial,
		cocos2d::Size movementCollisionSize = cocos2d::Size::ZERO,
		float ghettoGroundCollisionFix = 0.0f,
		PlatformerCollisionType movementCollisionType = PlatformerCollisionType::Movement,
		std::string inventorySaveKey = "",
		std::string equipmentSaveKey = "",
		std::string currencySaveKey = "");
	virtual ~PlatformerEntity();

	enum class ControlState
	{
		Normal,
		Swimming,
	};

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	HackablePreview* createDefaultPreview() override;
	void registerAttack(PlatformerAttack* attack);
	virtual void initializeCollisionEvents();
	virtual void performSwimAnimation();
	virtual void performJumpAnimation();
	void doOutOfCombatAttack();
	virtual std::string getOutOfCombatAttackAnimation();
	virtual float getOutOfCombatAttackOnset();
	virtual float getOutOfCombatAttackSustain();

	static cocos2d::PhysicsBody* createCapsulePolygon(cocos2d::Size size, float scale);

	CollisionObject* movementCollision;
	CollisionObject* entityCollision;
	CollisionObject* groundCollision;
	CollisionObject* leftCollision;
	CollisionObject* rightCollision;
	CollisionObject* weaponCollision;
	HexusOpponentData* hexusOpponentData;
	Inventory* inventory;
	EquipmentInventory* equipmentInventory;
	CurrencyInventory* currencyInventory;
	cocos2d::Vec2 movement;
	cocos2d::Vec2 spawnCoords;
	ControlState controlState;
	
	ClickableNode* resurrectButton;
	ClickableNode* killButton;

	bool isOnGround();
	bool isStandingOnSolid();
	bool isStandingOnSomethingOtherThan(CollisionObject* collisonObject);
	virtual void rebuildWeaponCollision(cocos2d::Size size);
	
	bool isCinimaticHijacked;
	bool isPerformingOutOfCombatAttack;
	bool isPlatformerDisabled;
	std::string state;

	cocos2d::Size entitySize;

	static const int DefaultEq;
	static const float MoveAcceleration;
	static const cocos2d::Vec2 SwimAcceleration;
	static const float WallDetectorSize;
	static const cocos2d::Size DefaultWeaponSize;
	static const float SwimVerticalDrag;
	static const float JumpVelocity;
	static const float GroundCollisionPadding;
	static const float GroundCollisionOffset;
	static const float CapsuleRadius;
	static const std::string MapKeyPropertyState;

private:
	typedef HackableObject super;

	int health;
	int maxHealth;
	int mana;
	int maxMana;
	std::vector<float> runeCooldowns;
	int eq;
	int eqExperience;
	float hoverHeight;

	float scale;
	PlatformerCollisionType collisionType;
	std::string animationResource;
	std::string emblemResource;
	std::vector<PlatformerAttack*> attacks;
	cocos2d::Vec2 hackButtonOffset;

	cocos2d::Sprite* outOfCombatAttackDebug;
};
