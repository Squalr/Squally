#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EcxPtrInitializer : public PtrInitializerBase
{
public:
	static EcxPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyEcxPtrInitializerBases;
	static const std::string MapKeyEcxPtrInitializer;

protected:
	EcxPtrInitializer(cocos2d::ValueMap& properties);
	~EcxPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
