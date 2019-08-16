#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EdxPtrInitializer : public PtrInitializerBase
{
public:
	static EdxPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyEdxPtrInitializerBases;
	static const std::string MapKeyEdxPtrInitializer;

protected:
	EdxPtrInitializer(cocos2d::ValueMap& properties);
	~EdxPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
