#pragma once
#include <set>

#include "cocos/math/CCGeometry.h"

#include "Engine/Physics/CollisionObject.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

class ClickableNode;
class PlatformerAttack;
class SmartAnimationNode;
class SpeechBubble;

class PlatformerEntity : public CollisionObject
{
public:
	struct CastResult
	{
		int damageDelta;

		CastResult(int damageDelta) : damageDelta(damageDelta) { }
	};

	int getHealth();
	void takeDamage(int healthDelta);
	int getMaxHealth();
	bool isDead();
	int getMana();
	int getMaxMana();
	int getRunes();
	int getMaxRunes();
	void castAttack(PlatformerAttack* attack, PlatformerEntity* target, std::function<void(CastResult)> onCastComplete);
	std::vector<PlatformerAttack*> getAttacks();
	std::vector<PlatformerAttack*> cloneAttacks();
	std::string getEmblemResource();
	cocos2d::Size getEntitySize();

	ClickableNode* clickHitbox;

	static const int FallBackMaxHealth;
	static const int FallBackMaxMana;
	static const int MaxRunes;

protected:
	PlatformerEntity(
		cocos2d::ValueMap* initProperties,
		std::string scmlResource,
		std::string emblemResource,
		PlatformerCollisionType collisionType,
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		int baseHealth,
		int baseSpecial);
	~PlatformerEntity();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	void registerAttack(PlatformerAttack* attack);
	virtual void initializeCollisionEvents();

	SpeechBubble* speechBubble;
	SmartAnimationNode* animationNode;
	cocos2d::Vec2 movement;
	cocos2d::Vec2 spawnCoords;

	bool isOnGround();
	
	int health;
	int maxHealth;
	int mana;
	int maxMana;
	int runes;

	cocos2d::Size entitySize;

	// CURRENT STATE
	float actualJumpLaunchVelocity;
	float actualGravityAcceleration;
	float actualMaxFallSpeed;

	float jumpLaunchVelocity;
	float gravityAcceleration;

	float moveAcceleration;

	static const float groundDragFactor;
	static const float airDragFactor;
	static const float maxMoveSpeed;
	static const float maxJumpSpeed;
	static const float maxFallSpeed;

private:
	typedef CollisionObject super;
	static cocos2d::PhysicsBody* createCapsulePolygon(cocos2d::Size size, float scale);

	std::string emblemResource;
	std::vector<PlatformerAttack*> attacks;
	std::set<CollisionObject*> groundCollisions;
	CollisionObject* groundCollisionDetector;

	static const float groundCollisionDetectorPadding;
	static const float groundCollisionDetectorOffset;
	static const float capsuleRadius;
};
