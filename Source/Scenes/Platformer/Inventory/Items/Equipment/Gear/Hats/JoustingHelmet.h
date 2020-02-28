#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"

class JoustingHelmet : public Hat
{
public:
	static JoustingHelmet* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	cocos2d::Vec2 getDisplayOffset() override;

	static const std::string SaveKeyJoustingHelmet;

protected:
	JoustingHelmet();
	virtual ~JoustingHelmet();

private:
	typedef Hat super;
};
