#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EbpPtrInitializer : public GridObject
{
public:
	static EbpPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEbpPtrInitializer;

protected:
	EbpPtrInitializer(cocos2d::ValueMap& initProperties);
	~EbpPtrInitializer();

private:
	typedef GridObject super;
};
