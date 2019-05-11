#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EsiPtrInitializer : public PtrInitializerBase
{
public:
	static EsiPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEsiPtrInitializerRegex;

protected:
	EsiPtrInitializer(cocos2d::ValueMap& initProperties);
	~EsiPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
