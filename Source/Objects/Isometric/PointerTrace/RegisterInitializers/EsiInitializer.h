#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EsiInitializer : public RegisterInitializer
{
public:
	static EsiInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKey;

protected:
	EsiInitializer(cocos2d::ValueMap& properties);
	virtual ~EsiInitializer();

private:
	typedef RegisterInitializer super;
};
