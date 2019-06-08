#pragma once

#include "cocos/math/CCGeometry.h"

#include "Engine/Hackables/HackableObject.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

class CollisionObject;
class ClickableNode;
class CurrencyInventory;
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
	int getMaxHealth();
	bool isDead();
	int getMana();
	void addMana(int manaDelta);
	void setMana(int mana);
	int getMaxMana();
	int getRunes();
	void setRunes(int runes);
	int getMaxRunes();
	void disablePlatformerControls();
	bool getIsPlatformerDisabled();
	virtual float getFloatHeight();

	std::vector<PlatformerAttack*> getAttacks();
	std::vector<PlatformerAttack*> getAvailableAttacks();
	std::vector<PlatformerAttack*> cloneAttacks();
	Inventory* getInventory();
	CurrencyInventory* getCurrencyInventory();
	std::string getEmblemResource();
	SmartAnimationNode* getAnimations();
	cocos2d::Size getEntitySize();
	HexusOpponentData* getHexusOpponentData();
	CollisionObject* getCollision();
	virtual cocos2d::Vec2 getAvatarFrameOffset() = 0;

	ClickableNode* clickHitbox;

	static const int FallBackMaxHealth;
	static const int FallBackMaxMana;
	static const int MaxRunes;

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
		cocos2d::Size movementCollisionSize = cocos2d::Size::ZERO);
	virtual ~PlatformerEntity();

	enum class ControlState
	{
		Normal,
		Swimming,
	};

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	void registerAttack(PlatformerAttack* attack);
	virtual void initializeCollisionEvents();
	virtual void performSwimAnimation();
	virtual void performJumpAnimation();

	static cocos2d::PhysicsBody* createCapsulePolygon(cocos2d::Size size, float scale);

	CollisionObject* movementCollision;
	CollisionObject* entityCollision;
	CollisionObject* groundCollision;
	HexusOpponentData* hexusOpponentData;
	Inventory* inventory;
	CurrencyInventory* currencyInventory;
	SpeechBubble* speechBubble;
	SmartAnimationNode* animationNode;
	cocos2d::Vec2 movement;
	cocos2d::Vec2 spawnCoords;
	ControlState controlState;

	bool isOnGround();
	bool isStandingOnSolid();
	bool isStandingOnSomethingOtherThan(CollisionObject* collisonObject);
	
	bool isCinimaticHijacked;
	bool isPlatformerDisabled;
	std::string state;
	int health;
	int maxHealth;
	int mana;
	int maxMana;
	int runes;

	cocos2d::Size entitySize;

	static const float MoveAcceleration;
	static const cocos2d::Vec2 SwimAcceleration;
	static const float SwimVerticalDrag;
	static const float JumpVelocity;
	static const float GroundCollisionPadding;
	static const float GroundCollisionOffset;
	static const float CapsuleRadius;
	static const std::string MapKeyPropertyState;

private:
	typedef HackableObject super;

	std::string emblemResource;
	std::vector<PlatformerAttack*> attacks;
};
