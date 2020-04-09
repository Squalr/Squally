#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EaxInitializer : public RegisterInitializer
{
public:
	static EaxInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKey;

protected:
	EaxInitializer(cocos2d::ValueMap& properties);
	virtual ~EaxInitializer();

private:
	typedef RegisterInitializer super;
};
