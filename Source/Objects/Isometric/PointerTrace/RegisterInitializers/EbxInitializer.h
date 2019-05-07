#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EbxInitializer : public GridObject
{
public:
	static EbxInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEbxInitializer;

protected:
	EbxInitializer(cocos2d::ValueMap& initProperties);
	~EbxInitializer();

private:
	typedef GridObject super;
};
