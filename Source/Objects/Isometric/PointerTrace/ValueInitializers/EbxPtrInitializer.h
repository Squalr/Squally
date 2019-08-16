#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EbxPtrInitializer : public PtrInitializerBase
{
public:
	static EbxPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyEbxPtrInitializerBases;
	static const std::string MapKeyEbxPtrInitializer;

protected:
	EbxPtrInitializer(cocos2d::ValueMap& properties);
	~EbxPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
