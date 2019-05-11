#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EbxPtrInitializer : public PtrInitializerBase
{
public:
	static EbxPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEbxPtrInitializerRegex;

protected:
	EbxPtrInitializer(cocos2d::ValueMap& initProperties);
	~EbxPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
