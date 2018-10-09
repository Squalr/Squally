/*
Tiniest Analytics - v1.1 - MIT License (i.e. can use it for whatever purpose)

Version history:
v1.1 - 2017/12/15 - changed to C-style C++

Original authors:
Mihai Dragomir, email:dmc@pixelshard.com
Mihai Gosa, email:pintea@inthekillhouse.com  twitter: @gosamihai

*/

#ifndef INCLUDE_TANALYTICS_H
#define INCLUDE_TANALYTICS_H

// 'uniqueClientId' should be unique for each user, e.g. the Steam UID or a randomly generated 32/64bit value
// e.g. Init("UA-12345678-1", steamClientId)
bool TAnalytics_Init(const char* trackingId, const char* uniqueClientId);

// call when exiting app
void TAnalytics_Shutdown();

// call at most once per frame
void TAnalytics_Update();

// read this https://support.google.com/analytics/answer/1033068?hl=en
// e.g. Event("GameStart", "linux")
// e.g. Event("WeaponClicked", "RocketLauncher")
// e.g. Event("MapStarted", "SinglePlayer", "MapName.map")
void TAnalytics_Event(const char* category, const char* action);
void TAnalytics_Event(const char* category, const char* action, const char* label);
void TAnalytics_Event(const char* category, const char* action, const char* label, unsigned int value);

#endif
