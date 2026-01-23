State Data Asset
===================

Even though you just learned how to make a state, you didn't learn much about what goes into making one. The following few pages will go a little bit more into what you're doing, and how to make something that's truly your own. First, we'll start with the `State Data Asset`.

## Organization
As you have just learned, states are individual Blueprint assets, meaning they're self-contained and don't directly link to your character. This is where the `State Data Asset` comes in: It contains a collection of states.

Every character uses three `State Data Assets`: `Common Object State Data`, `Object State Data`, and `Chara State Data`. `Chara State Data` is used to hold your character's states. In other words, any action performed by the character itself - such as standing, walking, or attacking - should be held here. Meanwhile, Object State Data is used to contain states that will be applied to Battle Objects. For example, projectiles, visual effects that you want to spawn and get a reference to later, or anything else that needs to be in the game world but *isn't* your character belongs here.

The difference between `Common Object State Data` and `Object State Data` is that `Common` refers to something that all characters in the game need, whereas regular `Object State Data` is character-specific. You are allowed to set a different `State Data Asset` with its own states to `Common Object State Data` if, for whatever reason, you wish to override the behavior of a common state.

## Priority
For `Chara State Data`, there's more than just containing states the character can use. It's also a hierarchy of priorities. As an example, if you had a punch and a fireball that both require pressing the button A, but the fireball also has a quarter circle, how would you guarantee that the fireball is what happens *instead* of the punch? With the `Chara State Data`, if the punch comes **before** the fireball in the list, the fireball is considered higher priority. **Remember this: the closer to the bottom of the list, the higher priority the state.**

There are even more advanced ways to manipulate the `State Data Asset`, but those are for another day. For the basics, this is all you need to know on this topic.

| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Your First State](create-state.md) | [Basics](../basics/basics.md) |