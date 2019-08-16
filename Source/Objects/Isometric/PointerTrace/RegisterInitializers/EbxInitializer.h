#pragma once

#include "Objects/Isometric/PointerTrace/RegisterInitializers/RegisterInitializer.h"

class EbxInitializer : public RegisterInitializer
{
public:
	static EbxInitializer* create(cocos2d::ValueMap& properties);

	void setGridIndex(int gridIndex) override;

	static const std::string MapKeyEbxInitializer;

protected:
	EbxInitializer(cocos2d::ValueMap& properties);
	~EbxInitializer();

private:
	typedef RegisterInitializer super;
};
