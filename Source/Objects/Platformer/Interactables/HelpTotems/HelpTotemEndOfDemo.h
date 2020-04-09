#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemEndOfDemo : public HelpTotem
{
public:
	static HelpTotemEndOfDemo* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	HelpTotemEndOfDemo(cocos2d::ValueMap& properties);
	virtual ~HelpTotemEndOfDemo();

private:
	typedef HelpTotem super;
};
