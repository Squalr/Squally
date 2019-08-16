#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EspPtrInitializer : public PtrInitializerBase
{
public:
	static EspPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyEspPtrInitializerBases;
	static const std::string MapKeyEspPtrInitializer;

protected:
	EspPtrInitializer(cocos2d::ValueMap& properties);
	~EspPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
