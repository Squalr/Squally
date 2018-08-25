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
	static std::string resolveFile(std::string fileEn);
	static std::string resolveString(std::string resourceKey);
	static std::string getLanguageCode();
	static float fontSizeH1(std::string fontResource);
	static float fontSizeH2(std::string fontResource);
	static float fontSizeH3(std::string fontResource);
	static float fontSizeP(std::string fontResource);

protected:

private:
	static Localization* getInstance();

	Localization();
	~Localization();

	Document* localizationMap;

	static Localization * instance;
};
