#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EbpInitializer : public RegisterInitializer
{
public:
	static EbpInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKey;

protected:
	EbpInitializer(cocos2d::ValueMap& properties);
	virtual ~EbpInitializer();

private:
	typedef RegisterInitializer super;
};
