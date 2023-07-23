#pragma once

#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"

class HelpTotemPotions : public HelpTotem
{
public:
	static HelpTotemPotions* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	HelpTotemPotions(cocos2d::ValueMap& properties);
	virtual ~HelpTotemPotions();

	void onInteract(PlatformerEntity* interactingEntity) override;
	
private:
	typedef HelpTotem super;
};
