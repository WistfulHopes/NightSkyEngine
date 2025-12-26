What Is A State? Part 1
===================

In Night Sky Engine, all characters have their logic built using States and Subroutines. For now, we'll focus on States.

If you're familiar with a finite state machine, the concept here is similar. A character's state machine can be in one state at a time, and there are rules for transitioning between states. However, unlike a traditional finite state machine, the Night Sky State Machine allows for more broad categorization of states, in addition to fine-tuned control over transitions.

States have two types of main conditions: Input and State Conditions. Input Conditions are based on the controller input: in other words, anything from holding a direction to doing a quarter circle forward and a button together, and even more. Meanwhile, a State Condition is a pre-determined condition for entering the state. Several examples of State Conditions are having enough meter, a Player Register being true or false, and so on.

Every state can be grouped into a "State Type", such as Standing, Jumping, Normal Attack, etc. You can broadly toggle on and off transitioning into other states. For example, by toggling on the Jumping State Type, any Jumping States can be entered when its Input and State Conditions are met. Additionally, custom State Types may be created in Blueprints.

Finally, if you need even more control over entering a state, you can override the `Can Enter State` function of a state to set custom conditions.

If you need a more specific way to transition between different states, there are two ways to handle this: Cancels and Jump to State.

A Cancel is a way to "cancel" the current state's execution and move to another state, but only when the other state's Input and State Conditions are met. There are several types of cancels, such as Jump Cancels, Special Cancels, Chain Cancels, and Whiff Cancels. For the most control, Chain and Whiff Cancels can be used.

A Chain Cancel allows transitioning to another state upon the opponent receiving or blocking an attack. Chain Cancels are on by default on all normal attacks. Meanwhile, a Whiff Cancel allows transitioning to another state at any time. However, Whiff Cancels must be enabled on a per-state basis. The state to transition to is specified by name.

Finally, a Jump to State allows bypassing all Input and State Conditions to enter another state. This is useful when a state has an automatic followup, such as landing recovery or a cinematic that only activates on hit.

The Exit State macro is a simplification of Jump to State used to return to a neutral state immediately. This is used when a state's logic has ended (like when an attack's recovery is over).

| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Getting Your Bearings](bearings.md) | [What Is A State? Part 2](state-p2.md) |