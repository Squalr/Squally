#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemPickPocket : public HelpTotem
{
public:
	static HelpTotemPickPocket* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyHelpTotemPickPocket;

protected:
	HelpTotemPickPocket(cocos2d::ValueMap& properties);
	virtual ~HelpTotemPickPocket();
	
	void onEnter() override;

private:
	typedef HelpTotem super;
};
