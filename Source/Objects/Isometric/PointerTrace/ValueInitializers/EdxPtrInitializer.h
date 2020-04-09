#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EdxPtrInitializer : public PtrInitializerBase
{
public:
	static EdxPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyBases;
	static const std::string MapKey;

protected:
	EdxPtrInitializer(cocos2d::ValueMap& properties);
	virtual ~EdxPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
