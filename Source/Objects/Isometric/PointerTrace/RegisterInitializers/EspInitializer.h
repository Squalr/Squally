#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EspInitializer : public GridObject
{
public:
	static EspInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEspInitializer;

protected:
	EspInitializer(cocos2d::ValueMap& initProperties);
	~EspInitializer();

private:
	typedef GridObject super;
};
