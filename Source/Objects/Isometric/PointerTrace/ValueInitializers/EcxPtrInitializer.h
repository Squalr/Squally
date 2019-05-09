#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EcxPtrInitializer : public GridObject
{
public:
	static EcxPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEcxPtrInitializer;

protected:
	EcxPtrInitializer(cocos2d::ValueMap& initProperties);
	~EcxPtrInitializer();

private:
	typedef GridObject super;
};
