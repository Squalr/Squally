#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EsiInitializer : public GridObject
{
public:
	static EsiInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEsiInitializer;

protected:
	EsiInitializer(cocos2d::ValueMap& initProperties);
	~EsiInitializer();

private:
	typedef GridObject super;
};
