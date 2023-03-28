# IncredibleGame
This is a platformer game, where i implemented a bunch of intresting mechanics.

I made it with only C++ and SFML graphics library.

On game start the main screen pops up
![image](https://user-images.githubusercontent.com/76881722/228047873-e9058a1b-23b2-4381-b185-1c03655a4589.png)

There are 3 main levels, with boss between each level. 
On first level you have to kill monsters. If enough monsters are killed you can go to next level. Player can attack monsters with gun
![image](https://user-images.githubusercontent.com/76881722/228292301-657cd4e1-cfbf-4e48-a58a-18ecfc8fc4e7.png)

Between levels there is boss. That is a big bat that is spawning smaller bats and every few secounds big bat attacks with big shock wave on visible for bat area as there is shown below
![image](https://user-images.githubusercontent.com/76881722/228293237-0c3ab8ba-d100-41f7-8e81-184266ac476e.png)


Secound level is in cave, where you have to locate and destroy a nest from where birds are spawned that are tracking you with A-star pathfinding algorithm.
In this cave there is implemented a shadow casting algorithm, that is calculating what you can see from your position and anythind in the shadow is not visible.
![image](https://user-images.githubusercontent.com/76881722/228293672-04deed4e-a657-4174-9d44-f8a75e4f5394.png)


