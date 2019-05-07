#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EcxInitializer : public GridObject
{
public:
	static EcxInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEcxInitializer;

protected:
	EcxInitializer(cocos2d::ValueMap& initProperties);
	~EcxInitializer();

private:
	typedef GridObject super;
};
