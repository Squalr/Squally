#pragma once

#include "Engine/Hackables/HackableObject.h"

class PlatformerDecorObject : public HackableObject
{
public:
	static PlatformerDecorObject* create(cocos2d::ValueMap& properties);

protected:
	PlatformerDecorObject(cocos2d::ValueMap& properties);
	virtual ~PlatformerDecorObject();

	void onHackerModeEnable() override;
	void onHackerModeDisable() override;
	
private:
	typedef HackableObject super;
};
