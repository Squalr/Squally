#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemRequiredLevel : public HelpTotem
{
public:
	static HelpTotemRequiredLevel* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyHelpTotemRequiredLevel;

protected:
	HelpTotemRequiredLevel(cocos2d::ValueMap& properties);
	~HelpTotemRequiredLevel();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef HelpTotem super;
};
