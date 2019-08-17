#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemAttacking : public HelpTotem
{
public:
	static HelpTotemAttacking* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyHelpTotemAttacking;

protected:
	HelpTotemAttacking(cocos2d::ValueMap& properties);
	~HelpTotemAttacking();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef HelpTotem super;
};
