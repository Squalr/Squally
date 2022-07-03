#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemColdWater : public HelpTotem
{
public:
	static HelpTotemColdWater* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	HelpTotemColdWater(cocos2d::ValueMap& properties);
	virtual ~HelpTotemColdWater();

private:
	typedef HelpTotem super;
};
