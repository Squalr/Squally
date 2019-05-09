#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EdiInitializer : public RegisterInitializer
{
public:
	static EdiInitializer* create(cocos2d::ValueMap& initProperties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEdiInitializer;

protected:
	EdiInitializer(cocos2d::ValueMap& initProperties);
	~EdiInitializer();

private:
	typedef RegisterInitializer super;
};
