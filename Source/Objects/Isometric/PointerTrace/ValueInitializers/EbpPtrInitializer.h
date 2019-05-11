#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EbpPtrInitializer : public PtrInitializerBase
{
public:
	static EbpPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEbpPtrInitializerRegex;

protected:
	EbpPtrInitializer(cocos2d::ValueMap& initProperties);
	~EbpPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
