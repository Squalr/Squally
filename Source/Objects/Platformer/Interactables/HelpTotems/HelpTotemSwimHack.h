#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemSwimHack : public HelpTotem
{
public:
	static HelpTotemSwimHack* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	HelpTotemSwimHack(cocos2d::ValueMap& properties);
	virtual ~HelpTotemSwimHack();
	
	void onEnter() override;

private:
	typedef HelpTotem super;
};
