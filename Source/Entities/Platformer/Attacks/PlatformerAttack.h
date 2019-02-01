#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;

class PlatformerAttack : public SmartNode
{
public:
	virtual PlatformerAttack* clone() = 0;
	virtual LocalizedString* getString() = 0;
	virtual std::string getAttackAnimation();
	std::string getIconResource();
	float getAttackDuration();
	float getRecoverDuration();

protected:
	PlatformerAttack(std::string iconResource, float attackDuration, float recoverDuration);
	~PlatformerAttack() = default;

private:
	typedef SmartNode super;

	std::string iconResource;
	float attackDuration;
	float recoverDuration;
};
