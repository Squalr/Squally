#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EdxInitializer : public RegisterInitializer
{
public:
	static EdxInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEdxInitializer;

protected:
	EdxInitializer(cocos2d::ValueMap& properties);
	~EdxInitializer();

private:
	typedef RegisterInitializer super;
};
