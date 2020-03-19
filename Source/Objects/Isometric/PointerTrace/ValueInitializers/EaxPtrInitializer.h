#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EaxPtrInitializer : public PtrInitializerBase
{
public:
	static EaxPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyBases;
	static const std::string MapKey;

protected:
	EaxPtrInitializer(cocos2d::ValueMap& properties);
	virtual ~EaxPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
