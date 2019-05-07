#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EdxInitializer : public GridObject
{
public:
	static EdxInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEdxInitializer;

protected:
	EdxInitializer(cocos2d::ValueMap& initProperties);
	~EdxInitializer();

private:
	typedef GridObject super;
};
