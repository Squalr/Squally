#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemHacking : public HelpTotem
{
public:
	static HelpTotemHacking* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyHelpTotemHacking;

protected:
	HelpTotemHacking(cocos2d::ValueMap& properties);
	~HelpTotemHacking();

private:
	typedef HelpTotem super;
};
