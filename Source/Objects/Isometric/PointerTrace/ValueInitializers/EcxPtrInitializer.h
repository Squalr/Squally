#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EcxPtrInitializer : public PtrInitializerBase
{
public:
	static EcxPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyBases;
	static const std::string MapKey;

protected:
	EcxPtrInitializer(cocos2d::ValueMap& properties);
	virtual ~EcxPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
