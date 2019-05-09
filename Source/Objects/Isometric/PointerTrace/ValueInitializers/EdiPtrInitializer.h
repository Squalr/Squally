#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EdiPtrInitializer : public GridObject
{
public:
	static EdiPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEdiPtrInitializer;

protected:
	EdiPtrInitializer(cocos2d::ValueMap& initProperties);
	~EdiPtrInitializer();

private:
	typedef GridObject super;
};
