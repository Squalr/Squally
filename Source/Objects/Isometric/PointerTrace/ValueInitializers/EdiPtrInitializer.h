#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EdiPtrInitializer : public PtrInitializerBase
{
public:
	static EdiPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyEdiPtrInitializerBases;
	static const std::string MapKeyEdiPtrInitializer;

protected:
	EdiPtrInitializer(cocos2d::ValueMap& properties);
	~EdiPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
