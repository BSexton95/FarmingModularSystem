# Farming Modular System
This modular system is a start to any farming system that would be needed in a game. The developer 
can pick up a seed, plant it on a plot, wait for the plant to grow, and harvest the plant.

## How To Use
As a template, code can be modified to fit the developer's game.
### Player Character
The player character is the third person Farming Modular System Character. The C++ script holds the functionality for the player
to move around, look around, and jump along with a key binding to E for the interaction with the plot. The player has an array
that holds seeds and can hold a max amount of 4. This is a temporary inventory that can be replaced with the developers
desired inventory system.
### Seed
The seed is an actor that can be placed anywhere in the scene. A data asset, which i've named seed data, can be placed on the seed, this holds what type of seed it is
and how long it takes for it to grow. The seed also holds the functionality of when a player collides with the seed it is 
added to the players array of seeds.
### Seed Data Asset
The seed data holds the information of the seed. This can be modified in the script such as adding a mesh to it rather than on the seed itself 
or maybe how much this seed, when a fully grown plant and harvested, will cost. These seed datas can be added to any seed actor.
### Plot
The plot is an actor that can be placed anywhere in the scene. The plot script takes care of most of the growth of the seed. When a player 
has overlapped with a plot, they can press E to plant a seed if there is one in their inventory. The developer most likely will want meshes 
to represent the plant growth but for now the plot starts with the being a color red and turns green when the seed has grown into a healthy plant.
After the seed has been planted a timer is created and takes the time of growth from the seed data and once that time is up the plot turns green.
The player can reset the plot by overlapping with the plot and pressing E, this turns the plot back to red and it is ready for another seed.
### Timer
The timer is created in the plot when a seed is planted. The timer script takes the seeds data of how long it takes the plant to grow and sets
that as it's limit. When the time is up the timer will call the plots OnHavest function to let the player know the plant is ready to be harvested.

## Controls
| Key | Description |
|-----|-------------|
| WASD | Walk Around |
| Mouse | Look Around |
| E | Plant Seed and Harvest Seed |

## Known Bugs
When the player presses E to plant and harvest a seed all while overlapping with the plot, the player will not be able to press E again if they are still overlapping with the plot. The player must walk away from the plot and walk back up to the plot to be able to plant on that same plot again.

The seed script is using an overlap begin so if the player wants another of the same seed the player must walk away from the seed and walk up to it again.
