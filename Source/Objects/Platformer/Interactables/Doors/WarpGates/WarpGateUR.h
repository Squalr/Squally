#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

class WarpGateUR : public WarpGate
{
public:
	static WarpGateUR* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WarpGateUR(cocos2d::ValueMap& properties);
	virtual ~WarpGateUR();

private:
	typedef WarpGate super;
};
