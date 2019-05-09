#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EspInitializer : public RegisterInitializer
{
public:
	static EspInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEspInitializer;

protected:
	EspInitializer(cocos2d::ValueMap& initProperties);
	~EspInitializer();

private:
	typedef RegisterInitializer super;
};
