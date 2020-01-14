#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

class Judgement : public Weapon
{
public:
	static Judgement* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyJudgement;

protected:
	Judgement();
	virtual ~Judgement();

private:
	typedef Weapon super;
};
