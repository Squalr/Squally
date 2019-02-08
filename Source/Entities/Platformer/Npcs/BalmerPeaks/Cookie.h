////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/NpcBase.h"

class Cookie : public NpcBase
{
public:
	static Cookie* deserialize(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCookie;

private:
	Cookie(cocos2d::ValueMap& initProperties);
	~Cookie();
};
