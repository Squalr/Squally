#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EsiPtrInitializer : public GridObject
{
public:
	static EsiPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEsiPtrInitializer;

protected:
	EsiPtrInitializer(cocos2d::ValueMap& initProperties);
	~EsiPtrInitializer();

private:
	typedef GridObject super;
};
