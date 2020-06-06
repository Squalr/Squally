#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

class WarpGateDM : public WarpGate
{
public:
	static WarpGateDM* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WarpGateDM(cocos2d::ValueMap& properties);
	virtual ~WarpGateDM();

private:
	typedef WarpGate super;
};
