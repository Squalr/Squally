#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

class LocalizedString;

class Offhand : public Equipable
{
public:
	int getMinAttack();
	int getMaxAttack();
	virtual float getAttackOnset();
	virtual float getAttackSustain();
	virtual cocos2d::Vec2 getOffhandSizeMultiplier();
	virtual cocos2d::Vec2 getOffhandOffset();

protected:
	Offhand(int minAttack, int maxAttack);
	virtual ~Offhand();

private:
	typedef Equipable super;

	int minAttack;
	int maxAttack;
};
