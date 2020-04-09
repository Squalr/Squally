#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EdxInitializer : public RegisterInitializer
{
public:
	static EdxInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKey;

protected:
	EdxInitializer(cocos2d::ValueMap& properties);
	virtual ~EdxInitializer();

private:
	typedef RegisterInitializer super;
};
