#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;
class PlatformerEntity;
class Projectile;

class PlatformerAttack : public SmartNode
{
public:
	enum AttackType
	{
		Damage,
		Healing,
		Buff,
		Debuff,
		Resurrection,
	};

	PlatformerAttack* clone();
	virtual LocalizedString* getString() = 0;
	void registerAttackCompleteCallback(std::function<void()> callback);
	virtual std::string getAttackAnimation();
	std::string getIconResource();
	void execute(PlatformerEntity* owner, PlatformerEntity* target, std::function<void()> onCastComplete, std::function<void()> onRecoverComplete);

	float getPriority();
	int getSpecialCost();
	AttackType getAttackType();
	virtual void onAttackTelegraphBegin();
	virtual void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target);
	virtual void performAttack(PlatformerEntity* owner, PlatformerEntity* target) = 0;
	virtual bool isWorthUsing(const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam);
	virtual void onAttackEnd();
	virtual void onCleanup();
	int getRandomDamage();

	static const float PriorityCommon;
	static const float PriorityUncommon;
	static const float PriorityRare;

protected:
	PlatformerAttack(AttackType attackType, std::string iconResource, float probabilityWeight, int baseDamageOrHealingMin, int baseDamageOrHealingMax, int specialCost, float attackDuration, float recoverDuration, float cleanupDuration = PlatformerAttack::DefaultCleanupDuration);
	~PlatformerAttack() = default;

	int getBaseDamageMin();
	int getBaseDamageMax();
	int getRandomHealing();
	int getBaseHealingMin();
	int getBaseHealingMax();
	float getAttackDuration();
	float getRecoverDuration();
	std::string getMainhandResource(PlatformerEntity* owner);
	std::string getOffhandResource(PlatformerEntity* owner);
	void replaceMainhandWithProjectile(PlatformerEntity* owner, Projectile* projectile);
	void replaceOffhandWithProjectile(PlatformerEntity* owner, Projectile* projectile);

	float attackDuration;
	float recoverDuration;
	float priority;
	
	static const float DefaultCleanupDuration;

private:
	typedef SmartNode super;

	void replaceAnimationPartWithProjectile(std::string animationPart, PlatformerEntity* owner, Projectile* projectile);
	virtual PlatformerAttack* cloneInternal() = 0;

	AttackType attackType;
	std::string iconResource;
	int baseDamageOrHealingMin;
	int baseDamageOrHealingMax;
	int specialCost;

	std::vector<std::function<void()>> attackCompleteCallbacks;
};
