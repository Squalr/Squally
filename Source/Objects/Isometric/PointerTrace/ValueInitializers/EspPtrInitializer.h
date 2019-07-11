#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EspPtrInitializer : public PtrInitializerBase
{
public:
	static EspPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyEspPtrInitializerBases;
	static const std::string MapKeyEspPtrInitializer;

protected:
	EspPtrInitializer(cocos2d::ValueMap& initProperties);
	~EspPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
