#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemHacking : public HelpTotem
{
public:
	static HelpTotemHacking* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	HelpTotemHacking(cocos2d::ValueMap& properties);
	virtual ~HelpTotemHacking();

private:
	typedef HelpTotem super;
};
