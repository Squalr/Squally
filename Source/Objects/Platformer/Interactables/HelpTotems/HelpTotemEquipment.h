#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemEquipment : public HelpTotem
{
public:
	static HelpTotemEquipment* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	HelpTotemEquipment(cocos2d::ValueMap& properties);
	virtual ~HelpTotemEquipment();

private:
	typedef HelpTotem super;
};
