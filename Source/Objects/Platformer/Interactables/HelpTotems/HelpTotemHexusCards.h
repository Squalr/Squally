#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemHexusCards : public HelpTotem
{
public:
	static HelpTotemHexusCards* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	HelpTotemHexusCards(cocos2d::ValueMap& properties);
	virtual ~HelpTotemHexusCards();

private:
	typedef HelpTotem super;
};
