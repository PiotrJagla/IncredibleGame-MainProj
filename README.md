# IncredibleGame
This is a platformer game, where i implemented a bunch of intresting mechanics.

I made it with only C++ and SFML graphics library. For collision detection i used Swept AABB algorithm.

On game start, the main screen pops up
![image](https://user-images.githubusercontent.com/76881722/228047873-e9058a1b-23b2-4381-b185-1c03655a4589.png)

There are 3 main levels, with boss between each level. 
On first level you have to kill monsters. If enough monsters are killed you can go to next level. Player can attack monsters with gun. In the end of each level you have to go to the doors to get to next level.
![ezgif com-video-to-gif](https://github.com/PiotrJagla/IncredibleGame-MainProj/assets/76881722/f795e946-e229-443d-9cbe-1ac5f8ca8004)
![ezgif com-video-to-gif (1)](https://github.com/PiotrJagla/IncredibleGame-MainProj/assets/76881722/517d0791-0d73-4511-b062-b7314f428995)


Between levels there is boss. That is a big bat that is spawning smaller bats and every few seconds big bat attacks with big shock wave on visible for bat area as there is shown below
![image](https://user-images.githubusercontent.com/76881722/228293237-0c3ab8ba-d100-41f7-8e81-184266ac476e.png)

Second level is in cave, where you have to locate and destroy a nest from where birds are spawned. In this cave a shadow casting algorithm is implemented, that is calculating what you can see from your position and anything in the shadow is not visible. I implemented AI for birds so that they are tracking you with A-star path finding algorithm.
![image](https://user-images.githubusercontent.com/76881722/228293672-04deed4e-a657-4174-9d44-f8a75e4f5394.png)
![ezgif com-video-to-gif (2)](https://github.com/PiotrJagla/IncredibleGame-MainProj/assets/76881722/70b2cb50-8903-4928-a3f9-a4c67968db4e)

The last level is a parkour level where you have to collect 3 stars. 
![ezgif com-video-to-gif (3)](https://github.com/PiotrJagla/IncredibleGame-MainProj/assets/76881722/0b061a1e-2388-4655-b129-a2b847399548)


Of course there is more to it but this is just a quick overview.
