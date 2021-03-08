#pragma once

#include "Engine/Hackables/HackableObject.h"

#include "Scenes/Platformer/Level/Combat/Attacks/AbilityType.h"

class LocalizedString;
class PlatformerEntity;
class Projectile;

class PlatformerAttack : public HackableObject
{
public:
	enum class AttackType
	{
		Damage,
		Healing,
		Buff,
		Debuff,
		Resurrection,
	};

	enum class TargetingType
	{
		Single,
		Self,
		Multi
	};

	enum class Priority
	{
		Guaranteed,	// 100% (not weighted against other attacks, this gets priority)
		VeryCommon,	// 75%
		Common,		// 50%
		Reasonable,	// 25%
		Uncommon,	// 15%
		Rare,		// 8%
		IfNecessary // 0% (Will still get selected if no other choices)
	};

	PlatformerAttack* clone();
	virtual LocalizedString* getString() = 0;
	virtual LocalizedString* getDescription();
	void registerAttackCompleteCallback(std::function<void()> callback);
	virtual std::string getAttackAnimation();
	const std::string& getIconResource();
	void execute(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets, std::function<void()> onCastComplete, std::function<void()> onRecoverComplete);
	Priority getPriority();
	int getSpecialCost();
	AttackType getAttackType();
	TargetingType getTargetingType();
	virtual void onAttackTelegraphBegin();
	virtual void doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target);
	virtual void performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets) = 0;

	/*
		Determines if an ability is even worth using -- if it has any utility at all.
	*/
	virtual bool isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam);

	/*
		Determines how valuable it is to use the attack from caster => target. For example, healing a low HP target is higher utility than healing a high HP target.
		The value returned is NOT used to compare different spells, only the relative utility of casting the same spell on different targets.
	*/
	virtual float getUseUtility(PlatformerEntity* caster, PlatformerEntity* target, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam);

	virtual void onAttackEnd();
	virtual void onCleanup();
	int getRandomDamage();

protected:
	friend class EntityAttackBehavior;
	
	PlatformerAttack(AttackType attackType, std::string iconResource, Priority priority, AbilityType abilityType, int baseDamageOrHealingMin, int baseDamageOrHealingMax, int specialCost, float attackDuration, float recoverDuration, TargetingType targetingType = TargetingType::Single);
	virtual ~PlatformerAttack();

	int getBaseDamageMin();
	int getBaseDamageMax();
	int getRandomHealing();
	int getBaseHealingMin();
	int getBaseHealingMax();
	float getAttackDuration();
	float getRecoverDuration();
	void setDamageMultiplier(float damageMultiplier);
	std::string getMainhandResource(PlatformerEntity* owner);
	std::string getOffhandResource(PlatformerEntity* owner);
	void replaceMainhandWithProjectile(PlatformerEntity* owner, Projectile* projectile);
	void replaceOffhandWithProjectile(PlatformerEntity* owner, Projectile* projectile);

	PlatformerEntity* owner;
	float attackDuration;
	float recoverDuration;
	Priority priority;
	AbilityType abilityType;
	
	static const float DefaultCleanupDuration;
	static const std::string TagArenaTop;
	static const std::string TagArenaCenter;
	static const std::string TagArenaBottom;

private:
	typedef HackableObject super;

	void replaceAnimationPartWithProjectile(std::string animationPart, PlatformerEntity* owner, Projectile* projectile);
	virtual PlatformerAttack* cloneInternal() = 0;

	AttackType attackType;
	TargetingType targetingType;
	std::string iconResource;
	int baseDamageOrHealingMin;
	int baseDamageOrHealingMax;
	float damageMultiplier;
	int specialCost;

	std::vector<std::function<void()>> attackCompleteCallbacks;
};
