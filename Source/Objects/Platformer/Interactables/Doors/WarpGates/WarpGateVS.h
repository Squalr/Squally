#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

class WarpGateVS : public WarpGate
{
public:
	static WarpGateVS* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WarpGateVS(cocos2d::ValueMap& properties);
	virtual ~WarpGateVS();

private:
	typedef WarpGate super;
};
