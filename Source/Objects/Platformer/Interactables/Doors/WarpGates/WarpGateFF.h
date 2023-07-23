#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

class WarpGateFF : public WarpGate
{
public:
	static WarpGateFF* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WarpGateFF(cocos2d::ValueMap& properties);
	virtual ~WarpGateFF();

private:
	typedef WarpGate super;
};
