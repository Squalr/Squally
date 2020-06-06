#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

class WarpGateBP : public WarpGate
{
public:
	static WarpGateBP* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WarpGateBP(cocos2d::ValueMap& properties);
	virtual ~WarpGateBP();

private:
	typedef WarpGate super;
};
