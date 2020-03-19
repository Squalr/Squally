#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EcxInitializer : public RegisterInitializer
{
public:
	static EcxInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKey;

protected:
	EcxInitializer(cocos2d::ValueMap& properties);
	virtual ~EcxInitializer();

private:
	typedef RegisterInitializer super;
};
