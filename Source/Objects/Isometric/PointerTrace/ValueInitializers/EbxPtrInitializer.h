#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EbxPtrInitializer : public PtrInitializerBase
{
public:
	static EbxPtrInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::vector<std::string> MapKeyBases;
	static const std::string MapKey;

protected:
	EbxPtrInitializer(cocos2d::ValueMap& properties);
	virtual ~EbxPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
