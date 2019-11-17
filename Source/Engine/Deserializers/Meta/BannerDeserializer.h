#pragma once

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"

class LocalizedString;

class BannerDeserializer : public PropertyDeserializer
{
public:
	static BannerDeserializer* create();

	void deserializeProperties(GameObject* owner, cocos2d::ValueMap properties) override;

protected:
	BannerDeserializer();
	~BannerDeserializer();
	
	std::map<std::string, std::function<LocalizedString*()>> deserializers;

private:
	typedef PropertyDeserializer super;

	static const std::string MapKeyBanner;
};
