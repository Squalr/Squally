#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemRepair : public HelpTotem
{
public:
	static HelpTotemRepair* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	HelpTotemRepair(cocos2d::ValueMap& properties);
	virtual ~HelpTotemRepair();
	
	void onEnter() override;

private:
	typedef HelpTotem super;
};
