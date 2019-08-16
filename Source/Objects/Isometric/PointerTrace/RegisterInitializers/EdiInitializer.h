#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EdiInitializer : public RegisterInitializer
{
public:
	static EdiInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEdiInitializer;

protected:
	EdiInitializer(cocos2d::ValueMap& properties);
	~EdiInitializer();

private:
	typedef RegisterInitializer super;
};
