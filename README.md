# boggle

To watch a walkthrough video of the game, visit https://youtu.be/YkmDDJwP0CU.
# Getting Started

To upload your own dictionary file, be sure it satisfies the following conditions:
1. Each word is lower case in its entirety.
2. Each word is separated by its own line.
3. Each word contains characters only (no numbers, dashes, apostrophes or other special characters).

Then, replace "dictionary.txt" in main with the name of your file.

NOTE: In the video walkthrough, I executed 'make.' However, you should run the following command to execute the game:

```
gcc main.c -std=c11
```

then run

```
./a.out
```

to start the game.

# The Game

There is no limit on the board size. However, anything larger than M = 60 is not recommended because it limits
board visibiltiy. The default board size is M = 4. To change the board size, navigate to SETTINGS -> BOARD SIZE.

To change the level of difficulty, navigate to SETTINGS -> DIFFICULTY.

To view your stats, navigate to STATS. Keep in mind, the game can only store up to 5 players' stats.

To ensure you play valid words during game play, type words in all lowercase and press 'enter' before submitting an additional word.

Inputting invalid input will either exit the game or prompt you to enter the input again. 

# Citations

I "borrowed" scanner.c and scanner.h from 

wget troll.cs.ua.edu/ACP-C/scanner.h 
wget troll.cs.ua.edu/ACP-C/scanner.c

in order to ensure invalid input didn't crash my code.
