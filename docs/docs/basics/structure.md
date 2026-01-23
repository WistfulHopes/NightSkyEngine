Project Structure
===================

Night Sky Engine's project structure may feel overwhelming at first glance. This page is designed to break down what each folder's intended use is.

# Root folder
The intended filesystem for projects is to leave core implementation details in `Content/NightSkyEngine`, and put game-specific files in `Content/<Project Name>`.

## Blueprints
As one would expect, this folder contains all of the Blueprints for the given folder. Additionally, gameplay-related data assets tend to reside in this folder. Note that Widget Blueprints should be stored elsewhere.

### Battle
Universal battle elements, such as `BP_NightSkyGameState` and `BP_NightSkyPlayerController`, reside in this folder.

### Characters
Character-related elements, such as states and pawns, reside in this folder. A subfolder should be created for each character.

### CharaSelect
Character select-related elements, such as `BP_NightSkyCharaSelectGameState`, reside in this folder.

### Menu
Universal menu elements, such as `BP_MenuPlayerController`, reside in this folder.

### Transition
Used for network seamless loading.

### VSInfo
Used for the versus screen during battle loading.

### WT
Used for WT mode-related elements. Depending on your project needs, this folder may be deleted.

## CharacterAssets
Visual and audio assets for characters reside in this folder. Make a new subfolder for each character.

### Chara/Animations
For 3D characters, the character's animations should reside in this folder.

### Chara/Audio
A character's audio should reside in this folder. There should be an SE folder for sound effects, and a Voice folder for voice lines.

### Chara/Flipbooks
For 2D characters, the character's flipbooks should reside in this folder.

### Chara/Materials
The character's materials, material instances, and textures should reside in this folder.

There should be a Base folder for common parts, and a ColorXX folder for each color, where XX is the color ID.

### Chara/Meshes
For 3D characters, the character's meshes should reside in this folder.

### Chara/Sprites
For 2D characters, the character's sprites should reside in this folder.

### Chara/Particles
The character's particle effects should reside in this folder.

### Chara/Textures
For 2D characters, the character's textures should reside in this folder.

## Maps
All levels should reside in this folder.

## Shared
Common assets, such as master materials, inputs, and others should reside in this folder.

## UI
All UI elements, such as widget blueprints, should reside in this folder.

| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Basics](basics.md) | [Collision Data and Cels: Tying Frame Data, Animations, and Hitboxes Together](collision-data.md) |