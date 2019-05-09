#pragma once

#include "Objects/Isometric/PointerTrace/GridObject.h"

class EdxPtrInitializer : public GridObject
{
public:
	static EdxPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEdxPtrInitializer;

protected:
	EdxPtrInitializer(cocos2d::ValueMap& initProperties);
	~EdxPtrInitializer();

private:
	typedef GridObject super;
};
