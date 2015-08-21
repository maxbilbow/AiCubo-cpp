//
//  Behaviour.hpp
//  RMXKit
//
//  Created by Max Bilbow on 31/07/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef Behaviour_hpp
#define Behaviour_hpp

#include <stdio.h>

#endif /* Behaviour_hpp */

#include "Object.h"
#define _(x) #x

/*!
 *   @author Max Bilbow, 15-08-04 16:08:16
 *
 *     
 *
 *   @since <#0.1#>
 */
namespace rmx {
    ///Override this to setup your receivers
    ///You must add all the receivers that were overriden.
    class Behaviour : public Object {

    protected:
        
        typedef void (*Receiver)(Object *, Any);
        void addReceiver(std::string name, Receiver receiver) {
            throw std::invalid_argument("Not implemented");
            //              this->_receivers->setValueForKey(name, receiver);
        }
    public:
        bool enabled = true;
        Behaviour(std::string name = ""):Object(name) {
            this->addReceiver("OnDestroy", OnDestroy);
            this->awake();
        }
        
        ~Behaviour(){
            this->onDestroy();
        }
        
        ///	Awake is called when the script instance is being loaded.
        virtual void awake(Any args = nullptr) {
            std::cout << "\"" << this->uniqueName() << "\" is Awake!." << std::endl;
        }
        ///	This function is called every fixed framerate frame, if the MonoBehaviour is enabled.
        virtual void fixedUpdate(Any args = nullptr) {}
        /// LateUpdate is called every frame, if the Behaviour is enabled.
        virtual void lateUpdate(Any args = nullptr) {}
        /// Callback for setting up animation IK (inverse kinematics).
        virtual void onAnimatorIK(Any args = nullptr) {}
        ///	Callback for processing animation movements for modifying root motion.
        virtual void onAnimatorMove(Any args = nullptr) {}
        ///	Sent to all game objects when the player gets or loses focus.
        virtual void onApplicationFocus(Any args = nullptr) {}
        /// Sent to all game objects when the player pauses.
        virtual void onApplicationPause(Any args = nullptr) {}
        /// Sent to all game objects before the application is quit.
        virtual void onApplicationQuit(Any args = nullptr) {}
        ///	If OnAudioFilterRead is implemented, Unity will insert a custom filter into the audio DSP chain.
        virtual void onAudioFilterRead(Any args = nullptr) {}
        ///	OnBecameInvisible is called when the renderer is no longer visible by any camera.
        virtual void onBecameInvisible(Any args = nullptr) {}
        /// OnBecameVisible is called when the renderer became visible by any camera.
        virtual void onBecameVisible(Any args = nullptr) {}
        /// OnCollisionEnter is called when this collider/rigidbody has begun touching another rigidbody/collider.
        virtual void onCollisionEnter(Any args = nullptr) {}
        /// Sent when an incoming collider makes contact with this object's collider (2D physics only).
        virtual void onCollisionEnter2D(Any args = nullptr) {}
        ///	OnCollisionExit is called when this collider/rigidbody has stopped touching another rigidbody/collider.
        virtual void onCollisionExit(Any args = nullptr) {}
        /// Sent when a collider on another object stops touching this object's collider (2D physics only).
        virtual void onCollisionExit2D(Any args = nullptr) {}
        /// OnCollisionStay is called once per frame for every collider/rigidbody that is touching rigidbody/collider.
        virtual void onCollisionStay(Any args = nullptr) {}
        ///	Sent each frame where a collider on another object is touching this object's collider (2D physics only).
        virtual void onCollisionStay2D(Any args = nullptr) {}
        /// Called on the client when you have successfully connected to a server.
        virtual void onConnectedToServer(Any args = nullptr) {}
        /// OnControllerColliderHit is called when the controller hits a collider while performing a Move.
        virtual void onControllerColliderHit(Any args = nullptr) {}
        ///	This function is called when the MonoBehaviour will be destroyed.
        virtual void onDestroy(Any args = nullptr) {
            std::cout << "\"" << this->uniqueName() << "\" was destroyed." << std::endl;
        }
        /// This function is called when the behaviour becomes disabled (Any args = nullptr) {} or inactive.
        virtual void onDisable(Any args = nullptr) {}
        /// Called on the client when the connection was lost or you disconnected from the server.
        virtual void onDisconnectedFromServer(Any args = nullptr) {}
        /// Implement OnDrawGizmos if you want to draw gizmos that are also pickable and always drawn.
        virtual void onDrawGizmos(Any args = nullptr) {}
        /// Implement this OnDrawGizmosSelected if you want to draw gizmos only if the object is selected.
        virtual void onDrawGizmosSelected(Any args = nullptr) {}
        /// This function is called when the object becomes enabled and active.
        virtual void onEnable(Any args = nullptr) {}
        /// Called on the client when a connection attempt fails for some reason.
        virtual void onFailedToConnect(Any args = nullptr) {}
        /// Called on clients or servers when there is a problem connecting to the MasterServer.
        virtual void onFailedToConnectToMasterServer(Any args = nullptr) {}
        /// OnGUI is called for rendering and handling GUI events.
        virtual void onGUI(Any args = nullptr) {}
        /// Called when a joint attached to the same game object broke.
        virtual void onJointBreak(Any args = nullptr) {}
        ///	This function is called after a new level was loaded.
        virtual void onLevelWasLoaded(Any args = nullptr) {}
        /// Called on clients or servers when reporting events from the MasterServer.
        virtual void onMasterServerEvent(Any args = nullptr) {}
        ///	OnMouseDown is called when the user has pressed the mouse button while over the GUIElement or Collider.
        virtual void onMouseDown(Any args = nullptr) {}
        /// OnMouseDrag is called when the user has clicked on a GUIElement or Collider and is still holding down the mouse.
        virtual void onMouseDrag(Any args = nullptr) {}
        /// Called when the mouse enters the GUIElement or Collider.
        virtual void onMouseEnter(Any args = nullptr) {}
        /// Called when the mouse is not any longer over the GUIElement or Collider.
        virtual void onMouseExit(Any args = nullptr) {}
        /// Called every frame while the mouse is over the GUIElement or Collider.
        virtual void onMouseOver(Any args = nullptr) {}
        /// OnMouseUp is called when the user has released the mouse button.
        virtual void onMouseUp(Any args = nullptr) {}
        /// OnMouseUpAsButton is only called when the mouse is released over the same GUIElement or Collider as it was pressed.
        virtual void onMouseUpAsButton(Any args = nullptr) {}
        /// Called on objects which have been network instantiated with Network.Instantiate.
        virtual void onNetworkInstantiate(Any args = nullptr) {}
        /// OnParticleCollision is called when a particle hits a collider.
        virtual void onParticleCollision(Any args = nullptr) {}
        /// Called on the server whenever a new player has successfully connected.
        virtual void onPlayerConnected(Any args = nullptr) {}
        /// Called on the server whenever a player disconnected from the server.
        virtual void onPlayerDisconnected(Any args = nullptr) {}
        /// OnPostRender is called after a camera finished rendering the scene.
        virtual void onPostRender(Any args = nullptr) {}
        /// OnPreCull is called before a camera culls the scene.
        virtual void onPreCull(Any args = nullptr) {}
        /// OnPreRender is called before a camera starts rendering the scene.
        virtual void onPreRender(Any args = nullptr) {}
        /// OnRenderImage is called after all rendering is complete to render image.
        virtual void onRenderImage(Any args = nullptr) {}
        /// OnRenderObject is called after camera has rendered the scene.
        virtual void onRenderObject(Any args = nullptr) {}
        /// Used to customize synchronization of variables in a script watched by a network view.
        virtual void onSerializeNetworkView(Any args = nullptr) {}
        /// Called on the server whenever a Network.InitializeServer was invoked and has completed.
        virtual void onServerInitialized(Any args = nullptr) {}
        /// This function is called when the list of children of the transform of the GameObject has changed.
        virtual void onTransformChildrenChanged(Any args = nullptr) {}
        /// This function is called when the parent property of the transform of the GameObject has changed.
        virtual void onTransformParentChanged(Any args = nullptr) {}
        /// OnTriggerEnter is called when the Collider other enters the trigger.
        virtual void onTriggerEnter(Any args = nullptr) {}
        /// Sent when another object enters a trigger collider attached to this object (2D physics only).
        virtual void onTriggerEnter2D(Any args = nullptr) {}
        /// OnTriggerExit is called when the Collider other has stopped touching the trigger.
        virtual void onTriggerExit(Any args = nullptr) {}
        /// Sent when another object leaves a trigger collider attached to this object (2D physics only).
        virtual void onTriggerExit2D(Any args = nullptr) {}
        /// OnTriggerStay is called once per frame for every Collider other that is touching the trigger.
        virtual void onTriggerStay(Any args = nullptr) {}
        /// Sent each frame where another object is within a trigger collider attached to this object (2D physics only).
        virtual void onTriggerStay2D(Any args = nullptr) {}
        /// This function is called when the script is loaded or a value is changed in the inspector (Called in the editor only).
        virtual void onValidate(Any args = nullptr) {}
        /// OnWillRenderObject is called once for each camera if the object is visible.
        virtual void onWillRenderObject(Any args = nullptr) {}
        /// Reset to default values.
        virtual void reset(Any args = nullptr) {}
        /// Start is called on the frame when a script is enabled just before any of the Update methods is called the first time.
        virtual void start(Any args = nullptr) {}
        /// Update is called every frame, if the MonoBehaviour is enabled.
        virtual void update(Any args = nullptr) {}
        ///	Awake is called when the script instance is being loaded.
        
        template <class T>
        static void Awake(T * receiver, Any args) {
           ((Behaviour*) receiver)->awake(args);
        }
        ///	This function is called every fixed framerate frame, if the MonoBehaviour is enabled.
        static void FixedUpdate(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->fixedUpdate(args);
        }
        /// LateUpdate is called every frame, if the Behaviour is enabled.
        static void LateUpdate(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->lateUpdate(args);
        }
        /// Callback for setting up animation IK (inverse kinematics).
        static void OnAnimatorIK(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onAnimatorIK(args);
        }
        ///	Callback for processing animation movements for modifying root motion.
        static void OnAnimatorMove(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onAnimatorMove(args);
        }
        ///	Sent to all game objects when the player gets or loses focus.
        static void OnApplicationFocus(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onApplicationFocus(args);
        }
        /// Sent to all game objects when the player pauses.
        static void OnApplicationPause(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onApplicationPause(args);
        }
        /// Sent to all game objects before the application is quit.
        static void OnApplicationQuit(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onApplicationQuit(args);
        }
        ///	If OnAudioFilterRead is implemented, Unity will insert a custom filter into the audio DSP chain.
        static void OnAudioFilterRead(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onAudioFilterRead(args);
        }
        ///	OnBecameInvisible is called when the renderer is no longer visible by any camera.
        static void OnBecameInvisible(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onBecameInvisible(args);
        }
        /// OnBecameVisible is called when the renderer became visible by any camera.
        static void OnBecameVisible(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onBecameVisible(args);
        }
        /// OnCollisionEnter is called when this collider/rigidbody has begun touching another rigidbody/collider.
        static void OnCollisionEnter(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onCollisionEnter(args);
        }
        /// Sent when an incoming collider makes contact with this object's collider (2D physics only).
        static void OnCollisionEnter2D(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onCollisionEnter2D(args);
        }
        ///	OnCollisionExit is called when this collider/rigidbody has stopped touching another rigidbody/collider.
        static void OnCollisionExit(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onCollisionExit(args);
        }
        /// Sent when a collider on another object stops touching this object's collider (2D physics only).
        static void OnCollisionExit2D(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onCollisionExit2D(args);
        }
        /// OnCollisionStay is called once per frame for every collider/rigidbody that is touching rigidbody/collider.
        static void OnCollisionStay(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onCollisionStay(args);
        }
        ///	Sent each frame where a collider on another object is touching this object's collider (2D physics only).
        static void OnCollisionStay2D(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onCollisionStay2D(args);
        }
        /// Called on the client when you have successfully connected to a server.
        static void OnConnectedToServer(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onConnectedToServer(args);
        }
        /// OnControllerColliderHit is called when the controller hits a collider while performing a Move.
        static void OnControllerColliderHit(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onControllerColliderHit(args);
        }
        ///	This function is called when the MonoBehaviour will be destroyed.
        static void OnDestroy(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onDestroy(args);
        }
        /// This function is called when the behaviour becomes disabled (Object * receiver, Any args = nullptr) {} or inactive.
        static void OnDisable(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onDisable(args);
        }
        /// Called on the client when the connection was lost or you disconnected from the server.
        static void OnDisconnectedFromServer(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onDisconnectedFromServer(args);
        }
        /// Implement OnDrawGizmos if you want to draw gizmos that are also pickable and always drawn.
        static void OnDrawGizmos(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onDrawGizmos(args);
        }
        /// Implement this OnDrawGizmosSelected if you want to draw gizmos only if the object is selected.
        static void OnDrawGizmosSelected(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onDrawGizmosSelected(args);
        }
        /// This function is called when the object becomes enabled and active.
        static void OnEnable(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onEnable(args);
        }
        /// Called on the client when a connection attempt fails for some reason.
        static void OnFailedToConnect(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onFailedToConnect(args);
        }
        /// Called on clients or servers when there is a problem connecting to the MasterServer.
        static void OnFailedToConnectToMasterServer(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onFailedToConnectToMasterServer(args);
        }
        /// OnGUI is called for rendering and handling GUI events.
        static void OnGUI(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onGUI(args);
        }
        /// Called when a joint attached to the same game object broke.
        static void OnJointBreak(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onJointBreak(args);
        }
        ///	This function is called after a new level was loaded.
        static void OnLevelWasLoaded(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onLevelWasLoaded(args);
        }
        /// Called on clients or servers when reporting events from the MasterServer.
        static void OnMasterServerEvent(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onMasterServerEvent(args);
        }
        ///	OnMouseDown is called when the user has pressed the mouse button while over the GUIElement or Collider.
        static void OnMouseDown(Object * receiver, Any args = nullptr) {
            ((Behaviour*)receiver)->onMouseDown(args);
        }
        /// OnMouseDrag is called when the user has clicked on a GUIElement or Collider and is still holding down the mouse.
        static void OnMouseDrag(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onMouseDrag(args); }
        
        /// Called when the mouse enters the GUIElement or Collider.
        static void OnMouseEnter(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onMouseEnter(args); }
        
        /// Called when the mouse is not any longer over the GUIElement or Collider.
        static void OnMouseExit(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onMouseExit(args); }
        
        /// Called every frame while the mouse is over the GUIElement or Collider.
        static void OnMouseOver(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onMouseOver(args); }
        
        /// OnMouseUp is called when the user has released the mouse button.
        static void OnMouseUp(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onMouseUp(args); }
        
        /// OnMouseUpAsButton is only called when the mouse is released over the same GUIElement or Collider as it was pressed.
        static void OnMouseUpAsButton(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onMouseUpAsButton(args); }
        
        /// Called on objects which have been network instantiated with Network.Instantiate.
        static void OnNetworkInstantiate(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onNetworkInstantiate(args); }
        
        /// OnParticleCollision is called when a particle hits a collider.
        static void OnParticleCollision(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onParticleCollision(args); }
        
        /// Called on the server whenever a new player has successfully connected.
        static void OnPlayerConnected(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onPlayerConnected(args); }
        
        /// Called on the server whenever a player disconnected from the server.
        static void OnPlayerDisconnected(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onPlayerDisconnected(args); }
        
        /// OnPostRender is called after a camera finished rendering the scene.
        static void OnPostRender(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onPostRender(args); }
        
        /// OnPreCull is called before a camera culls the scene.
        static void OnPreCull(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onPreCull(args); }
        
        /// OnPreRender is called before a camera starts rendering the scene.
        static void OnPreRender(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onPreRender(args); }
        
        /// OnRenderImage is called after all rendering is complete to render image.
        static void OnRenderImage(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onRenderImage(args); }
        
        /// OnRenderObject is called after camera has rendered the scene.
        static void OnRenderObject(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onRenderObject(args); }
        
        /// Used to customize synchronization of variables in a script watched by a network view.
        static void OnSerializeNetworkView(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onServerInitialized(args); }
        
        /// Called on the server whenever a Network.InitializeServer was invoked and has completed.
        static void OnServerInitialized(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onServerInitialized(args); }
        
        /// This function is called when the list of children of the transform of the GameObject has changed.
        static void OnTransformChildrenChanged(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onTransformChildrenChanged(args); }
        
        /// This function is called when the parent property of the transform of the GameObject has changed.
        static void OnTransformParentChanged(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onTransformChildrenChanged(args); }
        
        /// OnTriggerEnter is called when the Collider other enters the trigger.
        static void OnTriggerEnter(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onTriggerEnter(args); }
        
        /// Sent when another object enters a trigger collider attached to this object (2D physics only).
        static void OnTriggerEnter2D(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onTriggerEnter2D(args); }
        
        /// OnTriggerExit is called when the Collider other has stopped touching the trigger.
        static void OnTriggerExit(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onTriggerExit(args); }
        
        /// Sent when another object leaves a trigger collider attached to this object (2D physics only).
        static void OnTriggerExit2D(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onTriggerExit2D(args); }
        
        /// OnTriggerStay is called once per frame for every Collider other that is touching the trigger.
        static void OnTriggerStay(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onTriggerStay(args); }
        
        /// Sent each frame where another object is within a trigger collider attached to this object (2D physics only).
        static void OnTriggerStay2D(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onTriggerStay2D(args); }
        
        /// This function is called when the script is loaded or a value is changed in the inspector (Called in the editor only).
        static void OnValidate(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onValidate(args); }
        
        /// OnWillRenderObject is called once for each camera if the object is visible.
        static void OnWillRenderObject(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->onWillRenderObject(args); }
        
        /// Reset to default values.
        static void Reset(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->reset(args); }
        
        /// Start is called on the frame when a script is enabled just before any of the Update methods is called the first time.
        static void Start(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->start(args); }
        
        /// Update is called every frame, if the MonoBehaviour is enabled.
        static void Update(Object * receiver, Any args = nullptr) 
            {  ((Behaviour*)receiver)->update(args); }
        
    };
    
    
}

#undef _
