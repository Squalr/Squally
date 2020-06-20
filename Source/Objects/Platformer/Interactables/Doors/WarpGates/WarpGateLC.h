#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

class WarpGateLC : public WarpGate
{
public:
	static WarpGateLC* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WarpGateLC(cocos2d::ValueMap& properties);
	virtual ~WarpGateLC();

private:
	typedef WarpGate super;
};
