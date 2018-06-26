#pragma once
#include "cocos2d.h"

#include "allocators.h"
#include "encodings.h"
#include "document.h"
#include "stringbuffer.h"
#include "writer.h"

#include "Resources.h"

using namespace cocos2d;
using namespace rapidjson;

class Localization
{
public:
	static std::string resolveDialog(std::string dialogFileEN);
	static std::string resolveString(std::string resourceKey);

private:
	static Localization* getInstance();

	Localization();
	~Localization();

	Document* localizationMap;

	static Localization * instance;
};
