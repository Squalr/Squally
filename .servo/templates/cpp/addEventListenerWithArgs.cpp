this->addEventListener(EventListenerCustom::create(EventClass::EventName, [=](EventCustom* eventCustom)
	{
		EventClass::ArgsClass* args = static_cast<EventClass::ArgsClass*>(eventCustom->getUserData());

		if (args != nullptr)
		{
		}
	}));