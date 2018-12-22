////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEntity.h"

class Professor : public PlatformerEntity
{
public:
	static Professor* deserialize(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyProfessor;

private:
	Professor(cocos2d::ValueMap* initProperties);
	~Professor();
};
