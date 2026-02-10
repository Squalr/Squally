/****************************************************************************
Copyright (c) 2010      Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCCONFIGURATION_H__
#define __CCCONFIGURATION_H__

#include <string>

#include "base/CCRef.h"
#include "base/CCValue.h"
#include "platform/CCGL.h"

/**
 * @addtogroup base
 * @{
 */
NS_CC_BEGIN

class EventCustom;

/** @class Configuration
 * @brief Configuration contains some openGL variables
 * @since v0.99.0
 * @js NA
 */
class CC_DLL Configuration : public Ref
{
public:
    
    /** Returns a shared instance of Configuration.
     * 
     * @return An autoreleased Configuration object.
     */
    static Configuration *getInstance();

    /** Purge the shared instance of Configuration.
     */
    static void destroyInstance();

public:
    /** Destructor
     * @js NA
     * @lua NA
     */
	virtual ~Configuration();

    /** OpenGL Max texture size.
     * 
     * @return The OpenGL Max texture size.
     */
	int getMaxTextureSize() const;

    /** Whether or not the GPU supports NPOT (Non Power Of Two) textures.
     OpenGL ES 2.0 already supports NPOT (iOS).
     * 
     * @return Is true if supports NPOT.
     * @since v0.99.2
     */
	bool supportsNPOT() const;

    /** Whether or not shareable VAOs are supported.
     *
     * @return Is true if supports shareable VAOs.
     * @since v2.0.0
     */
	bool supportsShareableVAO() const;

    /** Whether or not glMapBuffer() is supported.
     *
     * On Desktop it returns `true`.
     * On Mobile it checks for the extension `GL_OES_mapbuffer`
     *
     * @return Whether or not `glMapBuffer()` is supported.
     * @since v3.13
     */
    bool supportsMapBuffer() const;
    
    /** Max support directional light in shader, for Sprite3D.
     *
     * @return Maximum supports directional light in shader.
     * @since v3.3
     */
    int getMaxSupportDirLightInShader() const;
    
    /** Max support point light in shader, for Sprite3D.
     *
     * @return Maximum supports point light in shader.
     * @since v3.3
     */
    int getMaxSupportPointLightInShader() const;
    
    /** Max support spot light in shader, for Sprite3D.
     *
     * @return Maximum supports spot light in shader.
     * @since v3.3
     */
    int getMaxSupportSpotLightInShader() const;
    
    /** Returns whether or not an OpenGL is supported. 
     *
     * @param searchName A given search name.
     * @return Is true if an OpenGL is supported.
     */
    bool checkForGLExtension(const std::string &searchName) const;

    /** Initialize method.
     *
     * @return Is true if initialize success.
     */
    bool init();

	/** Returns the value of a given key as a double.
     *
     * @param key A given key.
     * @param defaultValue if not find the value, return the defaultValue.
     * @return 
     */
	const Value& getValue(const std::string& key, const Value& defaultValue = Value::Null) const;

	/** Sets a new key/value pair  in the configuration dictionary.
     *
     * @param key A given key.
     * @param value A given value.
     */
	void setValue(const std::string& key, const Value& value);

    /** Returns the Configuration info.
     *
     * @return The Configuration info.
     */
    std::string getInfo() const;

	/** Gathers OpenGL / GPU information.
     */
	void gatherGPUInfo();

	/** Loads a config file. If the keys are already present, then they are going to be replaced. Otherwise the new keys are added.
     * 
     * @param filename Config file name.
     */
	void loadConfigFile(const std::string& filename);
    
    static const char* CONFIG_FILE_LOADED;

private:
    Configuration(void);
    static Configuration    *s_sharedConfiguration;
	static std::string		s_configfile;
    
protected:
    GLint           _maxTextureSize;
    bool            _supportsNPOT;
    bool            _supportsShareableVAO;
    
    GLint           _maxSamplesAllowed;
    char *          _glExtensions;
    int             _maxDirLightInShader; //max support directional light in shader
    int             _maxPointLightInShader; // max support point light in shader
    int             _maxSpotLightInShader; // max support spot light in shader
	
	ValueMap        _valueDict;
    
    EventCustom*    _loadedEvent;
};


NS_CC_END
// end of base group
/// @}

#endif // __CCCONFIGURATION_H__
