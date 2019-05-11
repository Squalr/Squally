#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EspPtrInitializer : public PtrInitializerBase
{
public:
	static EspPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEspPtrInitializerRegex;

protected:
	EspPtrInitializer(cocos2d::ValueMap& initProperties);
	~EspPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
