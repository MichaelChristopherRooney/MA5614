Note: best played on a black terminal due to how colours are set up.
See "screenshot.png" for an example of how the game looks.

Note: when selecting a column the game will check if the column number
is valid (ie between 0 and 6) and that the column is not full.
However the column input is not otherwise checked.
Inputting "xyz" instead of a valid number WILL cause issues.

Computer uses some simple rules to play.
Rules are followed in this order:

1) If a winning move can be made then make it.
2) If the opponent can make a winning move then block it.
3) If a winning move is two moves away then start working towards it.

These rules mean that defeating the computer requires making moves that 
give you two or more winning options at once, otherwise the computer can 
block it.

The computer can play itself, but there's a good chance it will end in a tie.
