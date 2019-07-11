#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class ValueInitializer : public GridObject
{
public:
	static ValueInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyValueInitializerBase;
	static const std::string MapKeyMetaValue;

protected:
	ValueInitializer(cocos2d::ValueMap& initProperties);
	~ValueInitializer();

private:
	typedef GridObject super;

	int value;

	static const std::string IntegerRegex;
};
