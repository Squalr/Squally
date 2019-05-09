#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EaxPtrInitializer : public GridObject
{
public:
	static EaxPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEaxPtrInitializer;

protected:
	EaxPtrInitializer(cocos2d::ValueMap& initProperties);
	~EaxPtrInitializer();

private:
	typedef GridObject super;
};
