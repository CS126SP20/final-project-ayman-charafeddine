#Likha 

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

**Author**: Ayman Charafeddine - [`aymanc2@illinois.edu`](mailto:aymanc2@illinois.edu)

####What is Likha
Likha is a trick-taking game similar to Hearts.

**Rules**: [Source]()
- Each heart card is worth 1 point, the queen of spades is worth 13 points, and the 10 of diamonds is worth 10 points. Other cards have no point value.
- The queen of spades and the 10 of diamonds are the likha cards.
- Aces are high.
- The game is played by 4 players forming two partnerships, where each player sits across from the partner, but each player receives points individually. When a player reaches 101 points, their partnership loses.
- 3 cards are passed to the right before the beginning of each round/hand. (Not yet implemented in this app).
- The player to the right of the dealer plays the first card. In each trick, play proceeds counterclockwise. Players must follow suit if able to do so. The player who played the highest card of the led suit takes the 4 cards played during the trick and begins the next trick.
- When discarding (i.e., you’ve run out of cards of the led suit and must play a card of a different suit) if you have any likhas, you must discard a likha on that trick. Otherwise, you can discard a card of your choice.
- On each round/hand other than the first, the dealer is the player who took the queen of spades on the previous hand.

**To Play**: 
- Run the run.cc source file to run the game. 
- Enter your name and press "Start Game" to begin. 
- At each trick, once it is your turn, click on the card you wish to play. 
- If you click on an invalid card, the card will not be played so choose another one (remember the rules : must play the suit that the trick was started with if you have it, and must get rid of likha when given the chance)
- Once the whole round/hand is over, a screen will appear with the current scores. Click "Start New Round" to begin next round.
- Once a round has ended and a player has more than 101 points, the game will end and a screen will tell you which team won.

The game engine cannot function by itself with just PlayerStrategies and is intended to work only inside of the CardTableApp.
####Dependencies
[Cinder](https://www.libcinder.org/) v.9.3.0 or higher, otherwise must get [ImGui Cinder Block](https://github.com/shaharz/Cinder-ImGui)
