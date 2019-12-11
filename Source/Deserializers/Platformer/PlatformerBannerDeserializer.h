#pragma once

#include "Engine/Deserializers/Meta/BannerDeserializer.h"

class PlatformerBannerDeserializer : public BannerDeserializer
{
public:
	static PlatformerBannerDeserializer* create();

private:
	typedef BannerDeserializer super;

	PlatformerBannerDeserializer();
	virtual ~PlatformerBannerDeserializer();
};
