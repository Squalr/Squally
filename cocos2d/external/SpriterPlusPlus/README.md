# SpriterPlusPlus
a C++ Implementation for Spriter animations

## About
SpriterPlusPlus aims to be as quick as possible playing back animations, and iterating additional characters once loaded.
Additional instances are flyweights that take up less ram than the initially the loaded model.
Each flyweight instance minimizes cycles spent in random access and iteratating through containers using stored pointers and iterators wherever possible.

## Included example
Sfml for display and sound playback

Two examples for loading: TinyXml and PugiXml

## Supported Features
Basic animations
Bone animations
All curve types (Instant, Linear, Quadratic, Cubic, Quartic, Quintic, Bezier)
Points
Collision Rectangles
SubEntities
Events (Triggers)
Sounds
Variables
Tags
Character Maps
Animation Blending

## How to use

##### All necessary files are in the 'spriterengine' folder.  The other included files are for example purposes.

### Extend (All of the following can be found in spriterengine/override) :
#### FileFactory 
###### and pass to SpriterModel so it can use your own inherited versions of :
* SpriterFileDocumentWrapper (and Element and Attribute Wrappers) to create parsing code.  You can specify a separate SpriterFileDocumentWrapper for scml (xml) and scon (json), which will be automatically selected upon loading based on the file extension
* ImageFile to store shared texture/image resources to be used by sprite objects
* SoundFile to store shared sound resources to be used by sound objects, and create your custom extended version of SoundObjectInfoReference to playback and control volume of the shared sound resources

#### ObjectFactory 
###### and pass to SpriterModel to enable debug rendering:
* spriterengine/objectinfo/PointInstanceInfo 
* spriterengine/objectinfo/BoneInstanceInfo
* spriterengine/objectinfo/BoxInstanceInfo 
 
Settings.cpp has static variables to control the display of points, bones, and boxes:

* bool Settings::renderDebugPoints;
* bool Settings::renderDebugBones;
* bool Settings::renderDebugBoxes;

enableDebugBones must be true while creating a new instance in order for renderDebugBones to have an effect:
* bool Settings::enableDebugBones;

* spriterengine/objectinfo/TriggerObjectInfo if you want to be able to perform a function upon being triggering events
###### (Alternatively you can query a specific trigger for your instance using :
* getTriggerObject("triggerName")->getTriggerCount() // in case more than one event was triggered in the elapsed time




### Creating an instance :
* #include "spriterengine/spriterengine.h"
* ScmlModel scmlModel(fileName, new customFileFactory, new customObjectFactory/*optional*/);

* EntityInstance *entityInstance = scmlModel.getNewEntityInstance(entityName or entityIndex);


### Controlling playback :
* entityInstance->setCurrentAnimation(animationName); // defaults to first animation
* entityInstance->setCurrentAnimation(animationName, blendTimeInMilliseconds); // blends the current animation to the new one over time
* entityInstance->setTimeElapsed(inMilliseconds); 

* entityInstance->pausePlayback(); // playback is automatically paused at the end of a non-looping animation
* entityInstance->startResumePlayback(); // playback automatically resumes on a setCurrentAnimation() command


##### after setting the elapsed Time:
* entityInstance->render();

##### and if you're using sound and/or events:
* entityInstance->playSoundTriggers();

###### or

* entityInstance->playEventTriggers();

###### or

* entityInstance->playAllTriggers();



#### Controlling the entire character
* entityInstance->setPosition(SpriterEngine::point(x,y))
* entityInstance->setAngle(SpriterEngine::toRadians(angle));
* entityInstance->setScale(SpriterEngine::point(w,h));


#### Character Maps
* entityInstance->applyCharacterMap("charMapOne");
* entityInstance->applyCharacterMap("charMapTwo");
* entityInstance->removeCharacterMap("charMapOne");
* entityInstance->removeAllCharacterMaps();


#### Metadata
##### to retrieve a variable value from an object :
* entityInstance->getRealValue("objectName","varName"); // or getIntValue, or getStringValue

##### to retrieve a variable from the entity itself :
* entityInstance->getRealValue("varName"); // or getIntValue, or getStringValue

##### if you would like to store the variable to avoid repeated retrieval for performance reasons (should normally not be necessary):
* UniversalObjectInterface *myVariable = entityInstance->getVariable("objectName", "varName"); // to retrieve from an object or
* UniversalObjectInterface *myVariable = entityInstance->getVariable("varName"); // to retrieve from the entity itself
 
######      and then use

* myVariable->getRealValue(); // or getIntValue, or getStringValue


##### to check if a tag is active :
* bool myTagIsActive = entityInstance->tagIsActive("objectName", "tagName");

##### or if the tag is on the entity itself :
* bool myTagIsActive = entityInstance->tagIsActive("tagName");


### Additional options
#### Error output
In Settings.cpp there is a function pointer to a callback function to display error messages:
* ErrorFunctionPointer Settings::errFunction; 

Any function with the signature void myErrorFunction(const std::string &errorMessage) can be used here. 

Two basic error functions are provided:
* nullError is the default, and takes no action
* simpleError outputs the error message to std::cerr

In most cases, there should be no errors, unless you are loading an invalid file, attempting to retrieve the wrong type of data from an object or variable (myStringVariable->getIntValue()), or attempting to access a missing variable or object


	

#### Loading options
In Settings.cpp you can set loading option, if your engine requires the y, pivotY, or angle to be reversed to display properly (you attempt to load a character in your engine and the positions, pivots, or angles seem reversed).
These are all defaulted to true, which is the setting that should work correctly for most engines.

*	Settings::reverseYOnLoad;
*	Settings::reversePivotYOnLoad;
*	Settings::reverseAngleOnLoad;


## Feedback
To provide feedback, report errors, or give suggestions, please use the relevant Spriter [forum thread](http://brashmonkey.com/forum/index.php?/topic/4464-spriterplusplus-a-c-spriter-implementation/ "BrashMonkey forums").
