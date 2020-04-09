#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EspPtrInitializer : public PtrInitializerBase
{
public:
	static EspPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyBases;
	static const std::string MapKey;

protected:
	EspPtrInitializer(cocos2d::ValueMap& properties);
	virtual ~EspPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
