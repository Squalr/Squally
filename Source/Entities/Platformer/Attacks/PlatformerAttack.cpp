#include "PlatformerAttack.h"

using namespace cocos2d;

PlatformerAttack::PlatformerAttack(std::string iconResource, int baseDamageMin, int baseDamageMax, int specialCost, float attackDuration, float recoverDuration)
{
	this->iconResource = iconResource;
	this->baseDamageMin = baseDamageMin;
	this->baseDamageMax = baseDamageMax;
	this->specialCost = specialCost;
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

int PlatformerAttack::getBaseDamageMin()
{
	return this->baseDamageMin;
}

int PlatformerAttack::getBaseDamageMax()
{
	return this->baseDamageMax;
}

float PlatformerAttack::getAttackDuration()
{
	return this->attackDuration;
}

float PlatformerAttack::getRecoverDuration()
{
	return this->recoverDuration;
}
