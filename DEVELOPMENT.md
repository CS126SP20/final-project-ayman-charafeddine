# Development

---

**Week 1**
- Created Card class that stores Suit and Rank enums and has getters and a function to get the point value of a card according to likha rules.
- Created Deck class that stores a stack of Card objects and has a Draw function that pops and returns the top Card as well as a size function.
- Wrote unit tests for Card and Deck classes
- Started seeing how to make the GUI work and created a function that draws cards being dealt (still needs to be worked on)
- Started to get ImGui set up

**Week 2**
- Created GameEngine class
- Made the gui a PlayerStrategy 
- Created method that takes a Card object and returns the card's image file path
- Created a method that displays the player's current hand on the gui
- Ultimately changed to not making the gui a PlayerStrategy, instead the gui app now owns the game engine and is responsible for relaying the plays of the PlayerStrategies as well as the plays that the user decides to play.

**Week 3**
- Created a CardDrawer class that can draw any card going from point A to point B, with or without rotation, to be used for all purposes including dealing and trick playing (throwing cards) and discarding cards.
- Used CardDrawers to draw card being thrown when PlayerStrategies chose a card to play.
- Implemented mouseDown() to throw the card clicked
- Enforced the rules when playing a card using mouseDown()
- Made the app complete an entire round of 13 tricks
- Used ImGui to start the game as well as start new rounds when one is over
- Used ImGui to show scores at the end of the round
- Uaed ImGui to tell you who won once the game is over