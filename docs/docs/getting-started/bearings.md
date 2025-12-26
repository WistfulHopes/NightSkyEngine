Getting Your Bearings
===================

Night Sky Engine is very powerful, but it may take some getting used to in order to unlock the full power of the framework. This page will explain some basic concepts of the framework. More detailed information will be brought up as the guide continues.

## Night Sky Game State
The Night Sky Game State is a class that extends Unreal's Game State Base. Everything related to battle code can be traced back to the code written in this class, such as all objects, the battle camera, and cinematics.

When using Blueprint scripting, you most likely won't touch the code of this class. However, you can set fields like the round format (such as first to one round), the round start position, screen and stage boundaries, and more.

## Battle and Player Objects
If the Night Sky Game State is the foundation of the battle scene, then a Battle Object is the main building block of the battle scene. Every actor that can influence the battle directly is either a Battle Object or inherits from a Battle Object. It stores all sorts of data, from position and speed to frame data and hit values. Regular Battle Objects tend to be used as projectiles or other non-player entities that should be updated.

On the other hand, Player Objects are a specialized version of Battle Objects intended for use with player characters. In other words, you directly control Player Objects. These contain even more data, such as health, meter, a state machine, and more.

## The State Machine
Player Objects have access to a primary state machines. This state machine contains states the Player Object has access to, and methods for changing state. You will most likely never need to modify the state machine itself, as the transition logic lies in the Player Object itself. The state machine's purpose is to keep track of the current state and contain all other states.

There's also an advanced, experimental feature for additional state machines. These states run in tandem with the primary state machine, and can be used to run background code independent of the main states. For more experimental games, this is useful for blending logic of multiple states together.

## States
In Night Sky Engine, a state is a Blueprint that contains logic for how a Battle Object should behave. They can informally be divided between object states and player states.

An object state is attached to a created Battle Object to set properties (such as an attached particle or values for hit) and frame data, or to run code. Object states are one-and-done; once the state is over, the Battle Object is removed.

A player state is attached to a Player Object's state machine for much the same reason as an object state. Unlike an object state, a player state will transition into another state upon ending, either via the Exit State macro (which will return the Player Object to a neutral state) or via the Jump to State function (which will forcibly enter a new state). Additionally, conditions can be set for entering the state, such as an input sequence or a variable.

## Cels
Frame data and anything else that should only update at a specific point of a state is handled by the Cel system. Cels are a two-part system: one part being the Cel Gate, and the other part being in the Player Object's Collision Data.

By using a Cel Gate macro in a state, you can create a "divider" of sorts for your state code. Code connected to the On Enter line will execute immediately upon a Cel's activation, and code connected to the On Update line will execute otherwise. The Duration parameter of the macro sets how long a Cel lasts. Once a Cel's duration elapses, the Next Cel line will activate, thereby creating a frame data system. All Cel Gates should be connected via the Next Cel line.

For the Collision Data part, Cels can be connected to animation frames and collision data via the Set Cel Name function. By setting the current Battle Object's Cel name to the corresponding entry in the Collision Data, the Battle Object's animation and collision data will be updated.

Under normal circumstances, there is no need to directly interact with a Cel Gate. Instead, it is recommended to use the Set Cel macro, or the Set Cel and Blend Cel macro for blended animations.

As an example, say we have a Set Cel macro for the first 8 frames of a player's standing state. The Cel Name is set to `Manny.Stand.00`. In the Collision Data, `Manny.Stand.00` is connected to the first frame of the standing animation and collision data. Upon entering the standing state, the player will immediately set its Cel name, then wait 8 frames. Upon its duration elapsing, the next Cel hooked up to Skip will activate, and so on.

When scripting in Blueprints, Cels will be the main way you interact with a state.

| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Installing Night Sky Engine](installing.md) | [What Is A State? Part 1](state-p1.md) |