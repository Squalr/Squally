#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EdiPtrInitializer : public PtrInitializerBase
{
public:
	static EdiPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyBases;
	static const std::string MapKey;

protected:
	EdiPtrInitializer(cocos2d::ValueMap& properties);
	virtual ~EdiPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
