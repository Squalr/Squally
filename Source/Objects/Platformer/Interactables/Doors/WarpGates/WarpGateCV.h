#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/WarpGates/WarpGate.h"

class WarpGateCV : public WarpGate
{
public:
	static WarpGateCV* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WarpGateCV(cocos2d::ValueMap& properties);
	virtual ~WarpGateCV();

private:
	typedef WarpGate super;
};
