#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EspInitializer : public RegisterInitializer
{
public:
	static EspInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKey;

protected:
	EspInitializer(cocos2d::ValueMap& properties);
	virtual ~EspInitializer();

private:
	typedef RegisterInitializer super;
};
