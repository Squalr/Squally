#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EcxInitializer : public RegisterInitializer
{
public:
	static EcxInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEcxInitializer;

protected:
	EcxInitializer(cocos2d::ValueMap& initProperties);
	~EcxInitializer();

private:
	typedef RegisterInitializer super;
};
