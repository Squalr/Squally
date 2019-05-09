#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class RegisterInitializer : public GridObject
{
public:
protected:
	RegisterInitializer(cocos2d::ValueMap& initProperties);
	~RegisterInitializer();

private:
	typedef GridObject super;
};
