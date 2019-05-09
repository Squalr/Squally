#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EbxPtrInitializer : public GridObject
{
public:
	static EbxPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEbxPtrInitializer;

protected:
	EbxPtrInitializer(cocos2d::ValueMap& initProperties);
	~EbxPtrInitializer();

private:
	typedef GridObject super;
};
