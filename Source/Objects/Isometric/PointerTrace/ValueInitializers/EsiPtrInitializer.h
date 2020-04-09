#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EsiPtrInitializer : public PtrInitializerBase
{
public:
	static EsiPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyBases;
	static const std::string MapKey;

protected:
	EsiPtrInitializer(cocos2d::ValueMap& properties);
	virtual ~EsiPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
