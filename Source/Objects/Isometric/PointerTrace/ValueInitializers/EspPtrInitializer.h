#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EspPtrInitializer : public GridObject
{
public:
	static EspPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEspPtrInitializer;

protected:
	EspPtrInitializer(cocos2d::ValueMap& initProperties);
	~EspPtrInitializer();

private:
	typedef GridObject super;
};
