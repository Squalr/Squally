#pragma once
#include "cocos2d.h"

#include "Engine/Maps/ILayerDeserializer.h"
#include "Engine/Sound/SoundManager.h"

using namespace cocos2d;

class MusicDeserializer : public ILayerDeserializer
{
public:
	void onDeserializationRequest(LayerDeserializationRequestArgs* args) override;

	static const std::string KeyMusicProperty;
};
