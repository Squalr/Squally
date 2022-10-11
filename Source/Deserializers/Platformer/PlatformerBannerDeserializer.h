#pragma once

#include "Engine/Deserializers/Meta/BannerDeserializer.h"

class PlatformerBannerDeserializer : public BannerDeserializer
{
public:
	static PlatformerBannerDeserializer* create();

protected:
	PlatformerBannerDeserializer();
	virtual ~PlatformerBannerDeserializer();

private:
	typedef BannerDeserializer super;
};
