#include "PlatformerAttack.h"

using namespace cocos2d;

PlatformerAttack::PlatformerAttack(std::string iconResource, float attackDuration, float recoverDuration)
{
	this->iconResource = iconResource;
	this->attackDuration = attackDuration;
	this->recoverDuration = recoverDuration;
}

std::string PlatformerAttack::getAttackAnimation()
{
	return "Attack";
}

std::string PlatformerAttack::getIconResource()
{
	return this->iconResource;
}

float PlatformerAttack::getAttackDuration()
{
	return this->attackDuration;
}

float PlatformerAttack::getRecoverDuration()
{
	return this->recoverDuration;
}
