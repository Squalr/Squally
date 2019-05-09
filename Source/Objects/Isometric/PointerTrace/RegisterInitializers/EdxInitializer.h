#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EdxInitializer : public RegisterInitializer
{
public:
	static EdxInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEdxInitializer;

protected:
	EdxInitializer(cocos2d::ValueMap& initProperties);
	~EdxInitializer();

private:
	typedef RegisterInitializer super;
};
