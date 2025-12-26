What Is A State? Part 2
===================

Now that you broadly know what a state is, I'll cover how state logic is defined.

States are defined in Unreal Engine's Blueprint system. If you haven't worked with Blueprints before, take a look at the official Unreal Engine documentation. All states must inherit from the C++ class called `State` at some point in its chain. This means that you cannot make a Blueprint that inherits from another UObject, or an Actor, and use it as a state.

There are two native-declared functions in States: Init and Exec. Init is called upon entering a state, and handles setup. For example, in a character's Stand State, you'd set Speed to zero, enable all State Types, and enable character flipping sides. Meanwhile, Exec is called every frame the game updates, and handles the majority of state logic. For example, you would want to put Cels only in Exec, meaning frame data is locked into the Exec function.

Another important system in States is the Event Handler system. There are several types of Events, such as Update, Exit, Landing, etc. Each Event has its own triggers, such as every frame for Update, exiting the state for Exit, touching the ground for Landing, etc. Event Handlers trigger a Blueprint Function by name when the corresponding Event fires.

Event Handlers must be initialized before they can be used. Once initialized, they will remain until the State is exited, or if removed by type. Only one Event Handler of a type may be active at once; if another Event Handler of the same type is initialized, it will overwrite the old one.

!!! warning

    If an Event Handler attempts to call a Blueprint Function that doesn't exist in the current State, nothing will happen! Make sure not to misspell the function name.

For large States, reading an Event Graph can become unwieldy. As a result, there are two main ways to clean up your Blueprint Code: Functions and Macros. I recommend using Macros to group Cels, and Functions to group non-Cel code that needs to be used often.

In the next part, I'll cover creating your first state.


| Previous          |                              Next |
|:------------------|----------------------------------:|
| [What Is A State? Part 1](state-p2.md) | [Your First State](create-state.md) |