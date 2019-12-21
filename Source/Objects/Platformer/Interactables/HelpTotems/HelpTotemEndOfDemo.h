#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemEndOfDemo : public HelpTotem
{
public:
	static HelpTotemEndOfDemo* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyHelpTotemEndOfDemo;

protected:
	HelpTotemEndOfDemo(cocos2d::ValueMap& properties);
	~HelpTotemEndOfDemo();

private:
	typedef HelpTotem super;
};
