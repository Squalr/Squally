#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EcxPtrInitializer : public PtrInitializerBase
{
public:
	static EcxPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEcxPtrInitializerRegex;

protected:
	EcxPtrInitializer(cocos2d::ValueMap& initProperties);
	~EcxPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
