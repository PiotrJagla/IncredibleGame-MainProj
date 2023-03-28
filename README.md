# IncredibleGame
This is a platformer game, where i implemented a bunch of intresting mechanics.

I made it with only C++ and SFML graphics library.

On game start the main screen pops up
![image](https://user-images.githubusercontent.com/76881722/228047873-e9058a1b-23b2-4381-b185-1c03655a4589.png)

There are 3 main levels, with boss between each level. 
On first level you have to kill monsters. If enough monsters are killed you can go to next level. Player can attack monsters with gun. In the end of each level you have to go to the doors to get to next level.
![image](https://user-images.githubusercontent.com/76881722/228292301-657cd4e1-cfbf-4e48-a58a-18ecfc8fc4e7.png)

Between levels there is boss. That is a big bat that is spawning smaller bats and every few secounds big bat attacks with big shock wave on visible for bat area as there is shown below
![image](https://user-images.githubusercontent.com/76881722/228293237-0c3ab8ba-d100-41f7-8e81-184266ac476e.png)

Secound level is in cave, where you have to locate and destroy a nest from where birds are spawned. In this cave there is implemented a shadow casting algorithm, that is calculating what you can see from your position and anythind in the shadow is not visible. I implemented AI for birds so that they are tracking you withn A-start path finding algorithm.
![image](https://user-images.githubusercontent.com/76881722/228293672-04deed4e-a657-4174-9d44-f8a75e4f5394.png)

Last level is a parkour level where you have to collect 3 start. 
![image](https://user-images.githubusercontent.com/76881722/228295880-b1d8e9e5-daec-49a6-b2f5-b79c90ea1a2e.png)

Of course there is more to it but this is just a quick overview.
