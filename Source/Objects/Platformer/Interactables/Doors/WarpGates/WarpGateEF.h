#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

class WarpGateEF : public WarpGate
{
public:
	static WarpGateEF* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WarpGateEF(cocos2d::ValueMap& properties);
	virtual ~WarpGateEF();

private:
	typedef WarpGate super;
};
