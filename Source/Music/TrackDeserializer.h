#pragma once

#include "Engine/Events/SoundEvents.h"
#include "Engine/GlobalNode.h"

class Music;

class TrackDeserializer : public GlobalNode
{
public:
	static TrackDeserializer* getInstance();
	static void RegisterGlobalNode();

	void deserialize(SoundEvents::RequestMusicDeserializationArgs args);

protected:
	TrackDeserializer();
	virtual ~TrackDeserializer();
	
	void initializeListeners() override;

private:
	typedef GlobalNode super;

	std::map<std::string, std::function<Music*(cocos2d::ValueMap&)>> deserializers;

	static TrackDeserializer* Instance;
};
