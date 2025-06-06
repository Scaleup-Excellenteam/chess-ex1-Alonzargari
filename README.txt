====== ADVANCED CPP - EX1: CHESS GAME =====
name:  Alon Zargari
id: 208626515

---- Program info ----
Description

Description
This is a continuation of Exercise 1. In this task, we implemented an algorithm that suggests the top 3 best moves for the current player based on a certain depth.

Algorithm Summary
The algorithm helps the player find the 3 best moves by looking a 
few turns ahead and checking how good each move could be, based on what the opponent might do in return.
It works like this:
For each piece the player has, we check all the legal moves it can make.
For each move:
We "pretend" to make the move on the board.
Then, we let the opponent take their turn by running the same logic again (this is done using recursion).
This continues until we reach a set depth (maxDepth), which limits how far ahead we look.

Score method:
Once we reach that depth, we calculate the score for the move based on three rules:
If the move causes the piece to be threatened by an enemy with a lower rank, we subtract the enemy's rank from the score.
If the move results in capturing an opponent, we add 15 points.
If the move causes a threat to an enemy with a higher rank, we add the enemy’s rank to the score.

While the function returns from each recursive level, it subtracts the opponent’s best score from the current move’s score — so we know how risky the move is.
In the end, the algorithm returns the 3 moves with the highest scores.

Recursive Flow Example:
Depth 0: It’s White’s turn. Evaluate all White moves and call the function again for each.
Depth 1: It’s Black’s turn. Evaluate all Black moves and call the function again for each.
Depth 2: Back to White. This is the maximum depth, so return the best score White can get.
As we return from the recursion:
Black subtracts White’s score from his move.
Then White subtracts that result from his move to see how good it really is.

Time Complexity
The time complexity of this algorithm is O(b^d), where:
b = average number of possible moves per turn
d = number of turns we look ahead (the depth)
In the best case (when better moves are evaluated first), the number of calculations can be reduced, and the time complexity can drop to about O(b^(d/2)).

Exceptions:
in this exceresice i decided to implement two types of exceptions :
1. empty queue exception - if the the queue i empty we will notice the player 
2. invalid move exception - activated if one of the moves is not valid ( if the from position == to position) 


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
BestMoveCalculator.h/cpp- contain the recursive algorithem to calculate the best moves
Moves.h/cpp - the data structure to represent the move that in the priority queue
PririorityQueue.h - template implementation of priorty queue using std::list and comperator
InvalidMoveException.h/cpp - the exception that inheritance from std::exception and raise exception about invalid move in the queue
EmptyQueueException.h/cpp - the exception that inheritance from std::exception and raise exception about empty queue


---- Bugs ----

---- Notes ----
1)there might be negative score in the best move
2) Note about depth limit:
In the exercise instructions, it is stated that the checker will test the program with a depth of up to 2 (which means looking ahead up to 3 turns in total).
If the checker tries to use a higher depth, the program may take a long time to calculate the best moves, since the number of possible game states increases quickly with each level of depth.



