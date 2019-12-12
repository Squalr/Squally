#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemHexusCards : public HelpTotem
{
public:
	static HelpTotemHexusCards* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyHelpTotemHexusCards;

protected:
	HelpTotemHexusCards(cocos2d::ValueMap& properties);
	~HelpTotemHexusCards();

private:
	typedef HelpTotem super;
};
