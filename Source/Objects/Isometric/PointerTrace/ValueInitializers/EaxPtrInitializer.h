#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EaxPtrInitializer : public PtrInitializerBase
{
public:
	static EaxPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyEaxPtrInitializerBases;
	static const std::string MapKeyEaxPtrInitializer;

protected:
	EaxPtrInitializer(cocos2d::ValueMap& properties);
	~EaxPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
