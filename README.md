# boggle

To watch a walkthrough video of the game, visit https://youtu.be/YkmDDJwP0CU.
# Getting Started

To upload your own dictionary file, be sure it satisfies the following conditions:
1. Each word is lower case in its entirety.
2. Each word is separated by its own line.
3. Each word contains characters only (no numbers, dashes, apostrophes or other special characters).

Then, replace "dictionary.txt" in main with the name of your file.

Run the following command to execute the game:

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

To view your stats, navigate to SETTINGS -> STATS. Keep in mind, the game can only store up to 5 player's stats.

To ensure you enter valid words, enter  words in all lowercase and press enter before entering an additional word.

Inputting invalid input will either exit the game or prompt you to enter input once again. 

# Citations

I "borrowed" scanner.c and scanner.h from 

wget troll.cs.ua.edu/ACP-C/scanner.h 
wget troll.cs.ua.edu/ACP-C/scanner.c

in order to ensure valid input.
