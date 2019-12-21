#pragma once

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class LocalizedString;
class MapTitleBanner;

class BannerDeserializer : public PropertyDeserializer
{
public:
	static BannerDeserializer* create();

	MapTitleBanner* deserializeProperties(cocos2d::ValueMap properties);
	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;

	static const std::string MapKeyBanner;

protected:
	BannerDeserializer();
	virtual ~BannerDeserializer();
	
	std::map<std::string, std::function<LocalizedString*()>> deserializers;

private:
	typedef PropertyDeserializer super;
};
