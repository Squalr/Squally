#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EdxPtrInitializer : public PtrInitializerBase
{
public:
	static EdxPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEdxPtrInitializerRegex;

protected:
	EdxPtrInitializer(cocos2d::ValueMap& initProperties);
	~EdxPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
