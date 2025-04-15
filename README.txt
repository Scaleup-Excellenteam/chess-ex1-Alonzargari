====== ADVANCED CPP - EX1: CHESS GAME =====
name:  Alon Zargari
id: 208626515

---- Program info ----
Description
This program implements the logic for a simple chess game. Based on the player's
input (the move), the program returns a response code indicating whether the move
 is legal or violates any rules.

The checks include:
Whether the piece being moved belongs to the opponent.
Whether the destination square is occupied by the player's own piece.
Whether the move is legal according to the piece's rules.
Whether the path is blocked by another piece.
Whether the move results in the player's own king being in check.
A simple graphical engine is already provided, and it will perform or ignore the move 
based on the response code returned.

Response Codes
 Illegal Move Codes:
11 – No piece on the source square.
12 – The piece on the source square belongs to the opponent.
13 – The destination square contains one of the player's own pieces.
21 – The move is not valid for the piece (e.g., a rook moving diagonally) or the piece is blocked.
31 – The move would result in the player's own king being in check.

Legal Move Codes:
42 – Legal move. The piece will be moved from the source square to the destination, and the turn will switch.
41 – Legal move that causes check. The piece will be moved, the turn will change, and a message will show that check occurred.


---- Files In Chess Directory ----

directory designPatterns:
--------------------------
directory factory:
------------------
PieceFactory.h/cpp- Implements the Factory design pattern.
Responsible for creating Piece objects based on char on the board. 

------------------
BoardManager.h/cpp- manage the movment of the pieces according to the rules 
using polymorphic vector
Piece.h/cpp- the base class of al the pices in the game contain virtual functions
King.h/cpp-contain king movments inheritance from piece
Knight.h/cpp-contain Knight movments inheritance from piece - register himself to factory map- Bonus Piece!
Rook.h/cpp-contain Rook movments inheritance from piece- register himself to factory map
Queen.h/cpp-contain Queen movments inheritance from piece- register himself to factory map
Runner.h/cpp-contain Runner movments inheritance from piece- register himself to factory map

---- Bugs ----

---- Notes ----
1) I implemented the knight piece -BOUNUS PIECE
2) No Pawn