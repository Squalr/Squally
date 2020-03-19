#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class PtrInitializerBase : public GridObject
{
protected:
	PtrInitializerBase(cocos2d::ValueMap& properties);
	virtual ~PtrInitializerBase();

	int offset;

private:
	typedef GridObject super;

	static const std::string OffsetRegex;
	static const std::string IntegerRegex;
};
