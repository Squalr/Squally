////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Viper : public NpcBase
{
public:
	static Viper* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyViper;

private:
	Viper(cocos2d::ValueMap* initProperties);
	~Viper();
};
