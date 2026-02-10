/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2009      Valentin Milea
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011      Zynga Inc.
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

#ifndef __CCNODE_H__
#define __CCNODE_H__

#include <cstdint>
#include "base/ccMacros.h"
#include "base/CCVector.h"
#include "base/CCProtocols.h"
#include "math/CCAffineTransform.h"
#include "math/CCMath.h"

NS_CC_BEGIN

class GridBase;
class Action;
class LabelProtocol;
class Scheduler;
class ActionManager;
class EventDispatcher;
class Scene;
class Renderer;
class Director;
class GLProgram;
class GLProgramState;
class Material;
class Camera;

/**
 * @addtogroup _2d
 * @{
 */

enum {
	kNodeOnEnter,
	kNodeOnReenter,
    kNodeOnExit,
    kNodeOnEnterTransitionDidFinish,
    kNodeOnExitTransitionDidStart,
    kNodeOnCleanup
};

class EventListener;

/** @class Node
* @brief Node is the base element of the Scene Graph. Elements of the Scene Graph must be Node objects or subclasses of it.
 The most common Node objects are: Scene, Layer, Sprite, Menu, Label.

 The main features of a Node are:
 - They can contain other Node objects (`addChild`, `removeChild`, etc)
 - They can schedule periodic callback (`schedule`, `unschedule`, etc)
 - They can execute actions (`runAction`, `stopAction`, etc)

 Subclassing a Node usually means (one/all) of:
 - overriding init to initialize resources and schedule callbacks
 - create callbacks to handle the advancement of time
 - overriding `draw` to render the node

 Properties of Node:
 - position (default: x=0, y=0)
 - scale (default: x=1, y=1)
 - rotation (in degrees, clockwise) (default: 0)
 - anchor point (default: x=0, y=0)
 - contentSize (default: width=0, height=0)
 - visible (default: true)

 Limitations:
 - A Node is a "void" object. If you want to draw something on the screen, you should use a Sprite instead. Or subclass Node and override `draw`.

 */

class CC_DLL Node : public Ref
{
public:
    /** Default tag used for all the nodes */
    static const int INVALID_TAG = -1;

    enum {
        FLAGS_TRANSFORM_DIRTY = (1 << 0),
        FLAGS_CONTENT_SIZE_DIRTY = (1 << 1),

        FLAGS_DIRTY_MASK = (FLAGS_TRANSFORM_DIRTY | FLAGS_CONTENT_SIZE_DIRTY),
    };
    /// @{
    /// @name Constructor, Destructor and Initializers

    /**
     * Allocates and initializes a node.
     * @return A initialized node which is marked as "autorelease".
     */
    static Node * create();
public:
    
    /**
     * Gets the description string. It makes debugging easier.
     * @return A string
     * @js NA
     * @lua NA
     */
    virtual std::string getDescription() const;

    /// @} end of initializers



    /// @{
    /// @name Setters & Getters for Graphic Properties

    /**
     LocalZOrder is the 'key' used to sort the node relative to its siblings.

     The Node's parent will sort all its children based on the LocalZOrder value.
     If two nodes have the same LocalZOrder, then the node that was added first to the children's array will be in front of the other node in the array.
     
     Also, the Scene Graph is traversed using the "In-Order" tree traversal algorithm ( http://en.wikipedia.org/wiki/Tree_traversal#In-order )
     And Nodes that have LocalZOrder values < 0 are the "left" subtree
     While Nodes with LocalZOrder >=0 are the "right" subtree.
     
     @see `setGlobalZOrder`
     @see `setVertexZ`
     *
     * @param localZOrder The local Z order value.
     */
    virtual void setLocalZOrder(std::int32_t localZOrder);
    
    /* 
     Helper function used by `setLocalZOrder`. Don't use it unless you know what you are doing.
     @js NA
     */
    virtual void _setLocalZOrder(std::int32_t z);

    /** !!! ONLY FOR INTERNAL USE
    * Sets the arrival order when this node has a same ZOrder with other children.
    *
    * A node which called addChild subsequently will take a larger arrival order,
    * If two children have the same Z order, the child with larger arrival order will be drawn later.
    *
    * @warning This method is used internally for localZOrder sorting, don't change this manually
    *
    * @param orderOfArrival   The arrival order.
    */
    void updateOrderOfArrival();

    /**
     * Gets the local Z order of this node.
     *
     * @see `setLocalZOrder(int)`
     *
     * @return The local (relative to its siblings) Z order.
     */

    virtual std::int32_t getLocalZOrder() const { return _localZOrder; }

    /**
     * Sets the scale (x) of the node.
     *
     * It is a scaling factor that multiplies the width of the node and its children.
     *
     * @param scaleX   The scale factor on X axis.
     *
     * @warning The physics body doesn't support this.
     */
    virtual void setScaleX(float scaleX);
    /**
     * Returns the scale factor on X axis of this node
     *
     * @see setScaleX(float)
     *
     * @return The scale factor on X axis.
     */
    virtual float getScaleX() const;


    /**
     * Sets the scale (y) of the node.
     *
     * It is a scaling factor that multiplies the height of the node and its children.
     *
     * @param scaleY   The scale factor on Y axis.
     *
     * @warning The physics body doesn't support this.
     */
    virtual void setScaleY(float scaleY);
    /**
     * Returns the scale factor on Y axis of this node
     *
     * @see `setScaleY(float)`
     *
     * @return The scale factor on Y axis.
     */
    virtual float getScaleY() const;

    /**
     * Sets the scale (x,y,z) of the node.
     *
     * It is a scaling factor that multiplies the width, height and depth of the node and its children.
     *
     * @param scale     The scale factor for both X and Y axis.
     *
     * @warning The physics body doesn't support this.
     */
    virtual void setScale(float scale);

    virtual void setScale(const Vec2& scale);

    /**
     * Gets the scale factor of the node,  when X and Y have the same scale factor.
     *
     * @warning Assert when `_scaleX != _scaleY`
     * @see setScale(float)
     *
     * @return The scale factor of the node.
     */
    virtual float getScale() const;

     /**
     * Sets the scale (x,y) of the node.
     *
     * It is a scaling factor that multiplies the width and height of the node and its children.
     *
     * @param scaleX     The scale factor on X axis.
     * @param scaleY     The scale factor on Y axis.
     *
     * @warning The physics body doesn't support this.
     */
    virtual void setScale(float scaleX, float scaleY);

    /**
     * Sets the position (x,y) of the node in its parent's coordinate system.
     *
     * Usually we use `Vec2(x,y)` to compose Vec2 object.
     * This code snippet sets the node in the center of screen.
     @code
     Size size = Director::getInstance()->getWinSize();
     node->setPosition(size.width/2, size.height/2);
     @endcode
     *
     * @param position  The position (x,y) of the node in OpenGL coordinates.
     */
    virtual void setPosition(const Vec2 &position);

    /** Sets the position (x,y) using values between 0 and 1.
     The positions in pixels is calculated like the following:
     @code
     // pseudo code
     void setNormalizedPosition(Vec2 pos) {
       Size s = getParent()->getContentSize();
       _position = pos * s;
     }
     @endcode
     *
     * @param position The normalized position (x,y) of the node, using value between 0 and 1.
     */
    virtual void setPositionNormalized(const Vec2 &position);
    // FIXME: should get deprecated in v4.0
    virtual void setNormalizedPosition(const Vec2 &position) { setPositionNormalized(position); }

    /**
     * Gets the position (x,y) of the node in its parent's coordinate system.
     *
     * @see setPosition(const Vec2&)
     *
     * @return The position (x,y) of the node in OpenGL coordinates.
     * @code
     * In js and lua return value is table which contains x,y.
     * @endcode
     */
    virtual const Vec2& getPosition() const;

    Vec2* getPositionPtr();
    
    float* getPositionZPtr();

    /** Returns the normalized position.
     * 
     * @return The normalized position.
     */
    virtual const Vec2& getPositionNormalized() const;
    // FIXME: should get deprecated in v4.0
    virtual const Vec2& getNormalizedPosition() const { return getPositionNormalized(); }

    /**
     * Sets the position (x,y) of the node in its parent's coordinate system.
     *
     * Passing two numbers (x,y) is much efficient than passing Vec2 object.
     * This method is bound to Lua and JavaScript.
     * Passing a number is 10 times faster than passing a object from Lua to c++.
     *
     @code
     // sample code in Lua
     local pos  = node::getPosition()  -- returns Vec2 object from C++.
     node:setPosition(x, y)            -- pass x, y coordinate to C++.
     @endcode
     *
     * @param x     X coordinate for position.
     * @param y     Y coordinate for position.
     */
    virtual void setPosition(float x, float y);
    /**
     * Gets position in a more efficient way, returns two number instead of a Vec2 object.
     *
     * @see `setPosition(float, float)`
     * In js,out value not return.
     *
     * @param x To receive x coordinate for position.
     * @param y To receive y coordinate for position.
     */
    virtual void getPosition(float* x, float* y) const;
    /**
     * Gets/Sets x or y coordinate individually for position.
     * These methods are used in Lua and Javascript Bindings
     */
    /** Sets the x coordinate of the node in its parent's coordinate system.
     *
     * @param x The x coordinate of the node.
     */
    virtual void  setPositionX(float x);
    /** Gets the x coordinate of the node in its parent's coordinate system.
     *
     * @return The x coordinate of the node.
     */
    virtual float getPositionX(void) const;
    /** Sets the y coordinate of the node in its parent's coordinate system.
     *
     * @param y The y coordinate of the node.
     */
    virtual void  setPositionY(float y);
    /** Gets the y coordinate of the node in its parent's coordinate system.
     *
     * @return The y coordinate of the node.
     */
    virtual float getPositionY(void) const;

    /**
     * Sets the position (X, Y, and Z) in its parent's coordinate system.
     * 
     * @param position The position (X, Y, and Z) in its parent's coordinate system.
     * @js NA
     */
    virtual void setPosition3D(const Vec3& position);
    /**
     * Returns the position (X,Y,Z) in its parent's coordinate system.
     *
     * @return The position (X, Y, and Z) in its parent's coordinate system.
     * @js NA
     */
    virtual Vec3 getPosition3D() const;

    /**
     * Sets the 'z' coordinate in the position. It is the OpenGL Z vertex value.
     *
     * The OpenGL depth buffer and depth testing are disabled by default. You need to turn them on.
     * In order to use this property correctly.
     *
     * `setPositionZ()` also sets the `setGlobalZValue()` with the positionZ as value.
     *
     * @see `setGlobalZValue()`
     *
     * @param positionZ  OpenGL Z vertex of this node.
     * @js setVertexZ
     */
    virtual void setPositionZ(float positionZ);

    /**
     * Gets position Z coordinate of this node.
     *
     * @see setPositionZ(float)
     *
     * @return The position Z coordinate of this node.
     * @js getVertexZ
     */
    virtual float getPositionZ() const;

    /**
     * Sets the anchor point in percent.
     *
     * anchorPoint is the point around which all transformations and positioning manipulations take place.
     * It's like a pin in the node where it is "attached" to its parent.
     * The anchorPoint is normalized, like a percentage. (0,0) means the bottom-left corner and (1,1) means the top-right corner.
     * But you can use values higher than (1,1) and lower than (0,0) too.
     * The default anchorPoint is (0,0), so it starts in the lower left corner of the node.
     * @note If node has a physics body, the anchor must be in the middle, you can't change this to other value.
     *
     * @param anchorPoint   The anchor point of node.
     */
    virtual void setAnchorPoint(const Vec2& anchorPoint);

    /**
     * Returns the anchor point in percent.
     *
     * @see `setAnchorPoint(const Vec2&)`
     *
     * @return The anchor point of node.
     */
    virtual const Vec2& getAnchorPoint() const;

    /**
     * Returns the anchorPoint in absolute pixels.
     *
     * @warning You can only read it. If you wish to modify it, use anchorPoint instead.
     * @see `getAnchorPoint()`
     *
     * @return The anchor point in absolute pixels.
     */
    virtual const Vec2& getAnchorPointInPoints() const;

    /**
     * Sets the untransformed size of the node.
     *
     * The contentSize remains the same no matter the node is scaled or rotated.
     * All nodes has a size. Layer and Scene has the same size of the screen.
     *
     * @param contentSize   The untransformed size of the node.
     */
    virtual void setContentSize(const CSize& contentSize);

    /**
     * Returns the untransformed size of the node.
     *
     * @see `setContentSize(const CSize&)`
     *
     * @return The untransformed size of the node.
     */
    virtual const CSize& getContentSize() const;

    /**
     * Sets whether the node is visible.
     *
     * The default value is true, a node is default to visible.
     *
     * @param visible   true if the node is visible, false if the node is hidden.
     */
    virtual void setVisible(bool visible);

    /**
     * Determines if the node is visible.
     *
     * @see `setVisible(bool)`
     *
     * @return true if the node is visible, false if the node is hidden.
     */
    virtual bool isVisible() const;

    virtual void makeDirty();

    /**
     * Sets the rotation (angle) of the node in degrees.
     *
     * 0 is the default rotation angle.
     * Positive values rotate node clockwise, and negative values for anti-clockwise.
     *
     * @param rotation     The rotation of the node in degrees.
     */
    virtual void setRotation(float rotation);
    /**
     * Returns the rotation of the node in degrees.
     *
     * @see `setRotation(float)`
     *
     * @return The rotation of the node in degrees.
     */
    virtual float getRotation() const;
    
    /**
     * Set rotation by quaternion. You should make sure the quaternion is normalized.
     *
     * @param quat The rotation in quaternion, note that the quat must be normalized.
     * @js NA
     */
    virtual void setRotationQuat(const Quaternion& quat);
    
    /**
     * Return the rotation by quaternion, Note that when _rotationZ_X == _rotationZ_Y, the returned quaternion equals to RotationZ_X * RotationY * RotationX,
     * it equals to RotationY * RotationX otherwise.
     *
     * @return The rotation in quaternion.
     * @js NA
     */
    virtual Quaternion getRotationQuat() const;

    /**
     * Sets whether the anchor point will be (0,0) when you position this node.
     *
     * This is an internal method, only used by Layer and Scene. Don't call it outside framework.
     * The default value is false, while in Layer and Scene are true.
     *
     * @param ignore    true if anchor point will be (0,0) when you position this node.
     */
    virtual void setIgnoreAnchorPointForPosition(bool ignore);
    
    /**
     * Gets whether the anchor point will be (0,0) when you position this node.
     *
     * @see `setIgnoreAnchorPointForPosition(bool)`
     *
     * @return true if the anchor point will be (0,0) when you position this node.
     */
    virtual bool isIgnoreAnchorPointForPosition() const;

    /// @}  end of Setters & Getters for Graphic Properties


    /// @{
    /// @name Children and Parent

	/**
	 * Adds a child to the container with z-order as 0.
	 *
	 * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
	 *
	 * @param child A child node.
	 */
	virtual void addChild(Node * child);
	/**
	 * Adds a child to the container with z-order as 0.
	 *
	 * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
	 *
	 * @param child A child node.
	 */
	virtual void addChildAsReentry(Node * child);
	/**
	 * Adds a child to the container with z-order as the index. Sorts all nodes.
	 *
	 * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
	 *
	 * @param child A child node.
	 */
	virtual void addChildInsert(Node * child, int index, bool isReentry = false);
    /**
     * Adds a child to the container with a local z-order.
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node.
     * @param localZOrder    Z order for drawing priority. Please refer to `setLocalZOrder(int)`.
     */
    virtual void addChild(Node * child, int localZOrder);

    /**
     * Adds a child to the container with z order and tag
     *
     * If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
     *
     * @param child     A child node.
     * @param localZOrder    Z order for drawing priority. Please refer to `setLocalZOrder(int)`.
     * @param name      A string to identify the node easily. Please refer to `setName(int)`.
     *
     */
    virtual void addChild(Node* child, int localZOrder, const std::string &name);
    /**
     * Returns the array of the node's children.
     *
     * @return the array the node's children.
     */
    virtual Vector<Node*>& getChildren() { return _children; }
    virtual const Vector<Node*>& getChildren() const { return _children; }
    
    /** 
     * Returns the amount of children.
     *
     * @return The amount of children.
     */
    virtual ssize_t getChildrenCount() const;

    /**
     * Sets the parent node.
     *
     * @param parent    A pointer to the parent node.
     */
    virtual void setParent(Node* parent);
    /**
     * Returns a pointer to the parent node.
     *
     * @see `setParent(Node*)`
     *
     * @returns A pointer to the parent node.
     */
    virtual Node* getParent() { return _parent; }
    virtual const Node* getParent() const { return _parent; }


    ////// REMOVES //////

    /**
     * Removes this node itself from its parent node with a cleanup.
     * If the node orphan, then nothing happens.
     * @see `removeFromParentAndCleanup(bool)`
     */
    virtual void removeFromParent();
    /**
     * Removes this node itself from its parent node.
     * If the node orphan, then nothing happens.
     * @param cleanup   true if all actions and callbacks on this node should be removed, false otherwise.
     * @js removeFromParent
     * @lua removeFromParent
     */
    virtual void removeFromParentAndCleanup(bool cleanup);

    virtual void removeChildNoExit(Node* child);

    /**
     * Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
     *
     * @param child     The child node which will be removed.
     * @param cleanup   True if all running actions and callbacks on the child node will be cleanup, false otherwise.
     */
    virtual void removeChild(Node* child, bool cleanup = true);

    /**
     * Removes all children from the container with a cleanup.
     *
     * @see `removeAllChildrenWithCleanup(bool)`
     */
    virtual void removeAllChildren();
    /**
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @param cleanup   True if all running actions on all children nodes should be cleanup, false otherwise.
     * @js removeAllChildren
     * @lua removeAllChildren
     */
    virtual void removeAllChildrenWithCleanup(bool cleanup);

    /**
     * Reorders a child according to a new z value.
     *
     * @param child     An already added child node. It MUST be already added.
     * @param localZOrder Z order for drawing priority. Please refer to setLocalZOrder(int).
     */
    virtual void reorderChild(Node * child, int localZOrder);

    /**
     * Sorts the children array once before drawing, instead of every time when a child is added or reordered.
     * This approach can improves the performance massively.
     * @note Don't call this manually unless a child added needs to be removed in the same frame.
     */
    virtual void sortAllChildren();

    /**
    * Sorts helper function
    *
    */
    template<typename _T> inline
    static void sortNodes(cocos2d::Vector<_T*>& nodes)
    {
        std::sort(std::begin(nodes), std::end(nodes), [](_T* n1, _T* n2)
        {
            return (n1->_localZOrder == n2->_localZOrder && n1->_orderOfArrival < n2->_orderOfArrival) || n1->_localZOrder < n2->_localZOrder;
        });
    }

    /// @} end of Children and Parent
    
    /// @{
    /// @name Tag & User data
    
    /** Returns a string that is used to identify the node.
     * @return A string that identifies the node.
     * 
     * @since v3.2
     */
    virtual const std::string& getName() const;

    /** Changes the name that is used to identify the node easily.
     * @param name A string that identifies the node.
     *
     * @since v3.2
     */
    virtual void setName(const std::string& name);


    /// @{
    /// @name GLProgram
    /**
     * Return the GLProgram (shader) currently used for this node.
     *
     * @return The GLProgram (shader) currently used for this node.
     */
    GLProgram* getGLProgram() const;

    /**
     * Sets the shader program for this node
     *
     * Since v2.0, each rendering node must set its shader program.
     * It should be set in initialize phase.
     @code
     node->setGLProgram(GLProgramCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
     @endcode
     *
     * @param glprogram The shader program.
     */
    virtual void setGLProgram(GLProgram *glprogram);
    
    /**
     * Return the GLProgramState currently used for this node.
     *
     * @return The GLProgramState currently used for this node.
     */
    GLProgramState *getGLProgramState() const;
    /**
     * Set the GLProgramState for this node.
     *
     * @param glProgramState The GLProgramState for this node.
     */
    virtual void setGLProgramState(GLProgramState *glProgramState);
    
    /// @} end of Shader Program


    /**
     * Returns whether or not the node is "running".
     *
     * If the node is running it will accept event callbacks like onEnter(), onExit(), update().
     *
     * @return Whether or not the node is running.
     */
    virtual bool isRunning() const;

    /// @}  end Script Bindings


    /// @{
    /// @name Event Callbacks

	/**
	 * Event callback that is invoked every time when Node enters the 'stage'.
	 * If the Node enters the 'stage' with a transition, this event is called when the transition starts.
	 * During onEnter you can't access a "sister/brother" node.
	 * If you override onEnter, you shall call its parent's one, e.g., Node::onEnter().
	 * @lua NA
	 */
	virtual void onEnter();

	/**
	 * Event callback that is invoked every time when Node enters the 'stage'.
	 * If the Node enters the 'stage' with a transition, this event is called when the transition starts.
	 * During onEnter you can't access a "sister/brother" node.
	 * If you override onEnter, you shall call its parent's one, e.g., Node::onEnter().
	 * @lua NA
	 */
	virtual void onReenter();

    /** Event callback that is invoked when the Node enters in the 'stage'.
     * If the Node enters the 'stage' with a transition, this event is called when the transition finishes.
     * If you override onEnterTransitionDidFinish, you shall call its parent's one, e.g. Node::onEnterTransitionDidFinish()
     * @lua NA
     */
    virtual void onEnterTransitionDidFinish();

    /**
     * Event callback that is invoked every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this event is called when the transition finishes.
     * During onExit you can't access a sibling node.
     * If you override onExit, you shall call its parent's one, e.g., Node::onExit().
     * @lua NA
     */
    virtual void onExit();

    /**
     * Event callback that is called every time the Node leaves the 'stage'.
     * If the Node leaves the 'stage' with a transition, this callback is called when the transition starts.
     * @lua NA
     */
    virtual void onExitTransitionDidStart();

    /// @} end of event callbacks.


    /**
     * Stops all running actions and schedulers
     */
    virtual void cleanup();

    /**
     * Override this method to draw your own node.
     * The following GL states will be enabled by default:
     * - `glEnableClientState(GL_VERTEX_ARRAY);`
     * - `glEnableClientState(GL_COLOR_ARRAY);`
     * - `glEnableClientState(GL_TEXTURE_COORD_ARRAY);`
     * - `glEnable(GL_TEXTURE_2D);`
     * AND YOU SHOULD NOT DISABLE THEM AFTER DRAWING YOUR NODE
     * But if you enable any other GL state, you should disable it after drawing your node.
     * 
     * @param renderer A given renderer.
     * @param transform A transform matrix.
     * @param flags Renderer flag.
     */
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    virtual void draw() final;

    /**
     * Visits this node's children and draw them recursively.
     *
     * @param renderer A given renderer.
     * @param parentTransform A transform matrix.
     * @param parentFlags Renderer flag.
     */
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags);
    virtual void visit() final;


    /** Returns the Scene that contains the Node.
     It returns `nullptr` if the node doesn't belong to any Scene.
     This function recursively calls parent->getScene() until parent is a Scene object. The results are not cached. It is that the user caches the results in case this functions is being used inside a loop.
     *
     * @return The Scene that contains the node.
     */
    virtual Scene* getScene() const;

    /**
     * Returns an AABB (axis-aligned bounding-box) in its parent's coordinate system.
     *
     * @return An AABB (axis-aligned bounding-box) in its parent's coordinate system
     */
	virtual CRect getBoundingBox() const;
	virtual CRect getBoundingBoxNoTransform() const;
    
    /** Get the event dispatcher of scene.
     *
     * @return The event dispatcher of scene.
     */
    virtual EventDispatcher* getEventDispatcher() const { return _eventDispatcher; };

    /// @{
    /// @name Actions

    /**
     * Sets the ActionManager object that is used by all actions.
     *
     * @warning If you set a new ActionManager, then previously created actions will be removed.
     *
     * @param actionManager     A ActionManager object that is used by all actions.
     */
    virtual void setActionManager(ActionManager* actionManager);
    /**
     * Gets the ActionManager object that is used by all actions.
     * @see setActionManager(ActionManager*)
     * @return A ActionManager object.
     */
    virtual ActionManager* getActionManager() { return _actionManager; }
    virtual const ActionManager* getActionManager() const { return _actionManager; }

    /**
     * Executes an action, and returns the action that is executed.
     *
     * This node becomes the action's target. Refer to Action::getTarget().
     * @warning Actions don't retain their target.
     *
     * @param action An Action pointer.
     */
    virtual Action* runAction(Action* action);

    /**
     * Stops and removes all actions from the running action list .
     */
    void stopAllActions();

    /**
     * Stops and removes an action from the running action list.
     *
     * @param action    The action object to be removed.
     */
    void stopAction(Action* action);

    /**
     * Returns the numbers of actions that are running plus the ones that are schedule to run (actions in actionsToAdd and actions arrays).
     *
     * Composable actions are counted as 1 action. Example:
     *    If you are running 1 Sequence of 7 actions, it will return 1.
     *    If you are running 7 Sequences of 2 actions, it will return 7.
     *
     * @return The number of actions that are running plus the ones that are schedule to run.
     */
    ssize_t getNumberOfRunningActions() const;

    /// @} end of Actions


    /// @{
    /// @name Scheduler and Timer

    /**
     * Sets a Scheduler object that is used to schedule all "updates" and timers.
     *
     * @warning If you set a new Scheduler, then previously created timers/update are going to be removed.
     * @param scheduler     A Scheduler object that is used to schedule all "update" and timers.
     */
    virtual void setScheduler(Scheduler* scheduler);
    /**
     * Gets a Scheduler object.
     *
     * @see setScheduler(Scheduler*)
     * @return A Scheduler object.
     */
    virtual Scheduler* getScheduler() { return _scheduler; }
    virtual const Scheduler* getScheduler() const { return _scheduler; }

    /**
     * Checks whether a lambda function is scheduled.
     *
     * @param key      key of the callback
     * @return Whether the lambda function selector is scheduled.
     * @js NA
     * @lua NA
     */
    bool isScheduled(const std::string &key) const;

    /**
     * Schedules the "update" method.
     *
     * It will use the order number 0. This method will be called every frame.
     * Scheduled methods with a lower order value will be called before the ones that have a higher order value.
     * Only one "update" method could be scheduled per node.
     * @lua NA
     */
    void scheduleUpdate(void);

    /*
     * Unschedules the "update" method.
     * @see scheduleUpdate();
     */
    void unscheduleUpdate(void);
    
    /**
     * Schedules a lambda function.
     *
     * @param callback  The lambda function to be schedule.
     * @param interval  Tick interval in seconds. 0 means tick every frame.
     * @param repeat    The selector will be executed (repeat + 1) times, you can use CC_REPEAT_FOREVER for tick infinitely.
     * @param delay     The amount of time that the first tick will wait before execution.
     * @param key       The key of the lambda function. To be used if you want to unschedule it.
     * @lua NA
     */
    void schedule(const std::function<void(float)>& callback, const std::string& key, float interval = 0.0f, unsigned int repeat = CC_REPEAT_FOREVER);

    /**
     * Unschedules a lambda function.
     *
     * @param key      The key of the lambda function to be unscheduled.
     * @lua NA
     */
    void unschedule(const std::string &key);

    /**
     * Unschedule all scheduled selectors and lambda functions: custom selectors, and the 'update' selector and lambda functions.
     * Actions are not affected by this method.
     * @lua NA
     */
    void unscheduleAllCallbacks();

	virtual bool isPaused(void);
    /**
     * Resumes all scheduled selectors, actions and event listeners.
     * This method is called internally by onEnter.
     */
    virtual void resume(void);
    /**
     * Pauses all scheduled selectors, actions and event listeners.
     * This method is called internally by onExit.
     */
    virtual void pause(void);

    /**
     * Update method will be called automatically every frame if "scheduleUpdate" is called, and the node is "live".
     * @param delta In seconds.
     */
    virtual void update(float delta);

    /// @} end of Scheduler and Timer

    /// @{
    /// @name Transformations

    /**
     * Calls children's updateTransform() method recursively.
     *
     * This method is moved from Sprite, so it's no longer specific to Sprite.
     * As the result, you apply SpriteBatchNode's optimization on your customed Node.
     * e.g., `batchNode->addChild(myCustomNode)`, while you can only addChild(sprite) before.
     */
    virtual void updateTransform();

    /**
     * Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     * The matrix is in Pixels.
     *
     * @return The transformation matrix.
     */
    virtual const Mat4& getNodeToParentTransform() const;
    virtual AffineTransform getNodeToParentAffineTransform() const;

    /**
     * Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     * The matrix is in Pixels.
     * Note: If ancestor is not a valid ancestor of the node, the API would return the same value as @see getNodeToWorldTransform
     *
     * @param ancestor The parent's node pointer.
     * @since v3.7
     * @return The transformation matrix.
     */
    virtual Mat4 getNodeToParentTransform(Node* ancestor) const;

    /**
     * Returns the affine transform matrix that transform the node's (local) space coordinates into the parent's space coordinates.
     * The matrix is in Pixels.
     *
     * Note: If ancestor is not a valid ancestor of the node, the API would return the same value as @see getNodeToWorldAffineTransform
     *
     * @param ancestor The parent's node pointer.
     * @since v3.7
     * @return The affine transformation matrix.
     */
    virtual AffineTransform getNodeToParentAffineTransform(Node* ancestor) const;

    /** 
     * Sets the transformation matrix manually.
     *
     * @param transform A given transformation matrix.
     */
    virtual void setNodeToParentTransform(const Mat4& transform);

    /**
     * Returns the matrix that transform parent's space coordinates to the node's (local) space coordinates.
     * The matrix is in Pixels.
     *
     * @return The transformation matrix.
     */
    virtual const Mat4& getParentToNodeTransform() const;
    virtual AffineTransform getParentToNodeAffineTransform() const;

    /**
     * Returns the world affine transform matrix. The matrix is in Pixels.
     *
     * @return transformation matrix, in pixels.
     */
    virtual Mat4 getNodeToWorldTransform() const;
    virtual AffineTransform getNodeToWorldAffineTransform() const;

    /**
     * Returns the inverse world affine transform matrix. The matrix is in Pixels.
     *
     * @return The transformation matrix.
     */
    virtual Mat4 getWorldToNodeTransform() const;
    virtual AffineTransform getWorldToNodeAffineTransform() const;

    /// @} end of Transformations


    /// @{
    /// @name Coordinate Converters

    /**
     * Converts a Vec2 to node (local) space coordinates. The result is in Points.
     *
     * @param worldPoint A given coordinate.
     * @return A point in node (local) space coordinates.
     */
    Vec2 convertToNodeSpace(const Vec2& worldPoint) const;
	Vec3 convertToNodeSpace3(const Vec3& nodePoint) const;

    /**
     * Converts a Vec2 to world space coordinates. The result is in Points.
     *
     * @param nodePoint A given coordinate.
     * @return A point in world space coordinates.
     */
	Vec2 convertToWorldSpace(const Vec2& nodePoint) const;
	Vec3 convertToWorldSpace3(const Vec3& nodePoint) const;

    /**
     * Converts a Vec2 to node (local) space coordinates. The result is in Points.
     * treating the returned/received node point as anchor relative.
     *
     * @param worldPoint A given coordinate.
     * @return A point in node (local) space coordinates, anchor relative.
     */
    Vec2 convertToNodeSpaceAR(const Vec2& worldPoint) const;

    /**
     * Converts a local Vec2 to world space coordinates.The result is in Points.
     * treating the returned/received node point as anchor relative.
     *
     * @param nodePoint A given coordinate.
     * @return A point in world space coordinates, anchor relative.
     */
    Vec2 convertToWorldSpaceAR(const Vec2& nodePoint) const;

    /// @} end of Coordinate Converters

    // overrides
    /**
     * Return the node's opacity.
     * @return A GLubyte value.
     */
    virtual GLubyte getOpacity() const;
    /**
     * Return the node's display opacity.
     * The difference between opacity and displayedOpacity is:
     * The displayedOpacity is what's the final rendering opacity of node.
     * @return A GLubyte value.
     */
    virtual GLubyte getDisplayedOpacity() const;
    /**
     * Change node opacity.
     * @param opacity A GLubyte opacity value.
     */
    virtual void setOpacity(GLubyte opacity);
    /**
     * Update the displayed opacity of node with it's parent opacity;
     * @param parentOpacity The opacity of parent node.
     */
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);
    /**
     * Whether cascadeOpacity is enabled or not.
     * @return A boolean value.
     */
    virtual bool isCascadeOpacityEnabled() const;
    /**
     * Change node's cascadeOpacity property.
     * @param cascadeOpacityEnabled True to enable cascadeOpacity, false otherwise.
     */
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);

    /**
     * Query node's color value.
     * @return A Color3B color value.
     */
    virtual const Color3B& getColor() const;
    /**
     * Query node's displayed color.
     * @return A Color3B color value.
     */
    virtual const Color3B& getDisplayedColor() const;
    /**
     * Change the color of node.
     * @param color A Color3B color value.
     */
    virtual void setColor(const Color3B& color);
    /**
     * Update node's displayed color with its parent color.
     * @param parentColor A Color3B color value.
     */
    virtual void updateDisplayedColor(const Color3B& parentColor);
    /**
     * Query whether cascadeColor is enabled or not.
     * @return Whether cascadeColor is enabled or not.
     */
    virtual bool isCascadeColorEnabled() const;
    /**
     * If you want node's color affect the children node's color, then set it to true.
     * Otherwise, set it to false.
     * @param cascadeColorEnabled A boolean value.
     */
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);

    /**
     *  If you want the opacity affect the color property, then set to true.
     * @param value A boolean value.
     */
    virtual void setOpacityModifyRGB(bool value);
    /**
     * If node opacity will modify the RGB color value, then you should override this method and return true.
     * @return A boolean value, true indicates that opacity will modify color; false otherwise.
     */
    virtual bool isOpacityModifyRGB() const;

    // Nodes should be created using create();
    Node();
    virtual ~Node();

    virtual bool init();

protected:
    /// helper that reorder a child
    void insertChild(Node* child, int z);

    /// Removes a child, call child->onExit(), do cleanup, remove it from children array.
    void detachChild(Node *child, ssize_t index, bool doCleanup);

    /// Convert cocos2d coordinates to UI windows coordinate.
    Vec2 convertToWindowSpace(const Vec2& nodePoint) const;

    virtual void updateCascadeOpacity();
    virtual void disableCascadeOpacity();
    virtual void updateCascadeColor();
    virtual void disableCascadeColor();
    virtual void updateColor() {}
    
    // update quaternion from Rotation
    void updateRotationQuat();

private:
    void addChildHelper(Node* child, int localZOrder, const std::string &name, bool isReentry = false);
    
protected:
    float _rotationX;               ///< rotation on the X-axis
    
    Quaternion _rotationQuat;       ///rotation using quaternion, if _rotationZ_X == _rotationZ_Y, _rotationQuat = RotationZ_X * RotationY * RotationX, else _rotationQuat = RotationY * RotationX

    float _scaleX;                  ///< scaling factor on x-axis
    float _scaleY;                  ///< scaling factor on y-axis
    
    Vec2 _position;                 ///< position of the node
    float _positionZ;               ///< OpenGL real Z position

    Vec2 _normalizedPosition;
    bool _usingNormalizedPosition;
    bool _normalizedPositionDirty;

    Vec2 _anchorPointInPoints;      ///< anchor point in points
    Vec2 _anchorPoint;              ///< anchor point normalized (NOT in points)

    CSize _contentSize;              ///< untransformed size of the node
    
    // "cache" variables are allowed to be mutable
    Mat4 _modelViewTransform;       ///< ModelView transform of the Node.
    mutable Mat4 _transform;        ///< transform
    mutable bool _transformDirty;   ///< transform dirty flag
    mutable Mat4 _inverse;          ///< inverse transform
    mutable bool _inverseDirty;     ///< inverse transform dirty flag
    uint32_t _selfFlags;    ///< Whether or not the Transform object was updated since the last frame < whether or not the contentSize is dirty

    union
    {
        struct
        {
            std::uint32_t _orderOfArrival;
            std::int32_t _localZOrder;
        };
        std::int64_t _localZOrder$Arrival;
    };

    static std::uint32_t s_globalOrderOfArrival;

    Vector<Node*> _children;        ///< array of children nodes
    Node *_parent;                  ///< weak reference to parent node
    Director* _director;            //cached director pointer to improve rendering performance
    std::string _name;              ///<a string label, an user defined string to identify this node
    GLProgramState *_glProgramState; ///< OpenGL Program State
    Scheduler *_scheduler;          ///< scheduler used to schedule timers and updates
    ActionManager *_actionManager;  ///< a pointer to ActionManager singleton, which is used to handle all the actions
    EventDispatcher* _eventDispatcher;  ///< event dispatcher used to dispatch all kinds of events

    bool _running;                  ///< is running
	bool _paused;                  ///< is paused
    bool _visible;                  ///< is this node visible
    bool _ignoreAnchorPointForPosition; ///< true if the Anchor Vec2 will be (0,0) when you position the Node, false otherwise.
                                          ///< Used by Layer and Scene.
    bool _reorderChildDirty;          ///< children order dirty flag
    bool _isTransitionFinished;       ///< flag to indicate whether the transition was finished
    
    // opacity controls
    GLubyte     _displayedOpacity;
    GLubyte     _realOpacity;
    Color3B     _displayedColor;
    Color3B     _realColor;
    bool        _cascadeColorEnabled;
    bool        _cascadeOpacityEnabled;
    
    std::function<void()> _onEnterCallback;
    std::function<void()> _onExitCallback;
    std::function<void()> _onEnterTransitionDidFinishCallback;
    std::function<void()> _onExitTransitionDidStartCallback;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Node);
};

/**
 * This is a helper function, checks a GL screen point is in content rectangle space.
 *
 * The content rectangle defined by origin(0,0) and content size.
 * This function convert GL screen point to near and far planes as points Pn and Pf,
 * then calculate the intersect point P which the line PnPf intersect with content rectangle.
 * If P in content rectangle means this node be hit.
 *
 * @param pt        The point in GL screen space.
 * @param camera    Which camera used to unproject pt to near/far planes.
 * @param w2l       World to local transform matrix, used to convert Pn and Pf to rectangle space.
 * @param rect      The test rectangle in local space.
 * @parma p         Point to a Vec3 for store the intersect point, if don't need them set to nullptr.
 * @return true if the point is in content rectangle, false otherwise.
 */
bool CC_DLL isScreenPointInRect(const Vec2 &pt, const Camera* camera, const Mat4& w2l, const CRect& rect, Vec3 *p);

// NodeRGBA

/** @class __NodeRGBA
 * @brief __NodeRGBA is a subclass of Node that implements the RGBAProtocol protocol.
 
 All features from Node are valid, plus the following new features:
 - opacity
 - RGB colors
 
 Opacity/Color propagates into children that conform to the RGBAProtocol if cascadeOpacity/cascadeColor is enabled.
 @since v2.1
 @js NA
 */
class CC_DLL __NodeRGBA : public Node, public __RGBAProtocol
{
public:
    // overrides
    virtual GLubyte getOpacity() const override { return Node::getOpacity(); }
    virtual GLubyte getDisplayedOpacity() const  override { return Node::getDisplayedOpacity(); }
    virtual void setOpacity(GLubyte opacity) override { return Node::setOpacity(opacity); }
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override { return Node::updateDisplayedOpacity(parentOpacity); }
    virtual bool isCascadeOpacityEnabled() const  override { return Node::isCascadeOpacityEnabled(); }
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled) override { return Node::setCascadeOpacityEnabled(cascadeOpacityEnabled); }

    virtual const Color3B& getColor(void) const override { return Node::getColor(); }
    virtual const Color3B& getDisplayedColor() const override { return Node::getDisplayedColor(); }
    virtual void setColor(const Color3B& color) override { return Node::setColor(color); }
    virtual void updateDisplayedColor(const Color3B& parentColor) override { return Node::updateDisplayedColor(parentColor); }
    virtual bool isCascadeColorEnabled() const override { return Node::isCascadeColorEnabled(); }
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled) override { return Node::setCascadeColorEnabled(cascadeColorEnabled); }

    virtual void setOpacityModifyRGB(bool bValue) override { return Node::setOpacityModifyRGB(bValue); }
    virtual bool isOpacityModifyRGB() const override { return Node::isOpacityModifyRGB(); }
    
    __NodeRGBA();
    virtual ~__NodeRGBA() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(__NodeRGBA);
};

// end of _2d group
/// @}

NS_CC_END

#endif // __CCNODE_H__
