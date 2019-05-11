#pragma once

#include "Objects/Isometric/PointerTrace/ValueInitializers/PtrInitializerBase.h"

class EaxPtrInitializer : public PtrInitializerBase
{
public:
	static EaxPtrInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEaxPtrInitializerRegex;

protected:
	EaxPtrInitializer(cocos2d::ValueMap& initProperties);
	~EaxPtrInitializer();

private:
	typedef PtrInitializerBase super;
};
