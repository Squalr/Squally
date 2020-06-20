#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

class WarpGateDH : public WarpGate
{
public:
	static WarpGateDH* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WarpGateDH(cocos2d::ValueMap& properties);
	virtual ~WarpGateDH();

private:
	typedef WarpGate super;
};
