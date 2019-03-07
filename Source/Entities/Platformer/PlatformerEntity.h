#pragma once

#include "cocos/math/CCGeometry.h"

#include "Engine/Hackables/HackableObject.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

class CollisionObject;
class ClickableNode;
class Inventory;
class PlatformerAttack;
class SmartAnimationNode;
class SpeechBubble;

class PlatformerEntity : public HackableObject
{
public:
	int getHealth();
	void addHealth(int healthDelta);
	int getMaxHealth();
	bool isDead();
	int getMana();
	int getMaxMana();
	int getRunes();
	int getMaxRunes();
	std::vector<PlatformerAttack*> getAttacks();
	std::vector<PlatformerAttack*> cloneAttacks();
	Inventory* getInventory();
	std::string getEmblemResource();
	SmartAnimationNode* getAnimations();
	cocos2d::Size getEntitySize();

	ClickableNode* clickHitbox;

	static const int FallBackMaxHealth;
	static const int FallBackMaxMana;
	static const int MaxRunes;

protected:
	PlatformerEntity(
		cocos2d::ValueMap& initProperties,
		std::string scmlResource,
		std::string emblemResource,
		PlatformerCollisionType collisionType,
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		int baseHealth,
		int baseSpecial);
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

	static cocos2d::PhysicsBody* createCapsulePolygon(cocos2d::Size size, float scale);

	CollisionObject* entityCollision;
	CollisionObject* groundCollision;
	Inventory* inventory;
	SpeechBubble* speechBubble;
	SmartAnimationNode* animationNode;
	cocos2d::Vec2 movement;
	cocos2d::Vec2 spawnCoords;
	ControlState controlState;

	bool isOnGround();
	
	int health;
	int maxHealth;
	int mana;
	int maxMana;
	int runes;

	cocos2d::Size entitySize;

private:
	typedef HackableObject super;

	std::string emblemResource;
	std::vector<PlatformerAttack*> attacks;

	static const float MoveAcceleration;
	static const cocos2d::Vec2 SwimAcceleration;
	static const float SwimVerticalDrag;
	static const float JumpVelocity;
	static const float GroundCollisionPadding;
	static const float GroundCollisionOffset;
	static const float CapsuleRadius;
};
