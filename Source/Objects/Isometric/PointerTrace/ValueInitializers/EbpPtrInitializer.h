#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EbpPtrInitializer : public PtrInitializerBase
{
public:
	static EbpPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyEbpPtrInitializerBases;
	static const std::string MapKeyEbpPtrInitializer;

protected:
	EbpPtrInitializer(cocos2d::ValueMap& properties);
	~EbpPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
