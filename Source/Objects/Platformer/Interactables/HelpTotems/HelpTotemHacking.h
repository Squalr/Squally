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
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef HelpTotem super;
};
