#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EaxInitializer : public RegisterInitializer
{
public:
	static EaxInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEaxInitializer;

protected:
	EaxInitializer(cocos2d::ValueMap& initProperties);
	~EaxInitializer();

private:
	typedef RegisterInitializer super;
};
