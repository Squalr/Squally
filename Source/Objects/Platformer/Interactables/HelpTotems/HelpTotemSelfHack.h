#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemSelfHack : public HelpTotem
{
public:
	static HelpTotemSelfHack* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyHelpTotemSelfHack;

protected:
	HelpTotemSelfHack(cocos2d::ValueMap& properties);
	~HelpTotemSelfHack();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef HelpTotem super;
};
