#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EaxInitializer : public GridObject
{
public:
	static EaxInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEaxInitializer;

protected:
	EaxInitializer(cocos2d::ValueMap& initProperties);
	~EaxInitializer();

private:
	typedef GridObject super;
};
