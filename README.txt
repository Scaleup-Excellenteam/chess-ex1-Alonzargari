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





🎯 סיכום אלגוריתם — שחמט: בחירת המהלך הטוב ביותר
עברית
האלגוריתם מחשב את המהלך הטוב ביותר על פי חישוב עומק רקורסיבי (depth-based recursive evaluation), עד עומק מסוים (maxDepth), תוך כדי התחשבות במהלך הטוב ביותר שהיריב יכול לעשות בתגובה.

שלבי האלגוריתם:

עבור כל חתיכה של השחקן הנוכחי, אנו מחשבים את כל המהלכים החוקיים האפשריים (evaluateAllMoves).

עבור כל מהלך:

מזיזים זמנית את החתיכה אל המיקום של המהלך.

קוראים לרקורסיה לעומק הבא (depth + 1) כאשר כעת תור היריב.

אם הגענו לעומק מקסימלי (בסיס הרקורסיה), מחזירים את הניקוד הכי גבוה שהיריב יכול להשיג.

בקיפול הרקורסיה:

אנו מחסרים את הציון הכי טוב של היריב מהציון של המהלך הנוכחי.

שומרים את המהלך שמביא לתוצאה נטו הכי גבוהה.

מחזירים את הציון נטו הכי טוב שמצאנו.

דוגמה של הרקורסיה:

עומק 0: השחקן הלבן.

בודקים מהלכים אפשריים לחתיכות הלבנות.

עבור כל מהלך של לבן, נכנסים לעומק 1.

עומק 1: תור השחור.

מחשבים מהלכים לשחור.

עבור כל מהלך של שחור נכנסים לעומק 2.

עומק 2: תור הלבן (במקרה הזה maxDepth הושג).

מחזירים את הציון הכי טוב של הלבן.

בקיפול: השחור מחסר את הציון הזה מהציון של המהלך שלו.

חוזרים לעומק 0, שם הלבן מחסר את התוצאה מהמהלך שלו כדי להבין כמה נזק היריב יכול היה לגרום.

🧠 Algorithm Summary — English
The algorithm computes the best move for a player using a depth-based recursive evaluation up to a defined maximum depth (maxDepth). The core idea is to evaluate how good each move is by subtracting the best possible counter-move the opponent can make in response.

Algorithm steps:

For each piece belonging to the current player, generate all legal moves (evaluateAllMoves).

For every possible move:

Temporarily move the piece to the destination square.

Recursively call the same function for the opponent (i.e., switch turn).

If the maximum depth has been reached (base case), return the highest score the current player can achieve from available moves.

In each recursive return (fold):

Subtract the opponent’s best possible score from the current move’s score.

Keep track of the move with the best resulting net score.

Finally, return the highest net score among all possible moves.

Recursive flow example:

Depth 0: White’s turn.

Evaluate all possible white moves.

For each move, proceed to depth 1.

Depth 1: Black’s turn.

Evaluate all possible black moves.

For each move, proceed to depth 2.

Depth 2: White’s turn again (max depth reached).

Return the highest score white can get from available moves.

In folding: black subtracts this score from his own move score.

Then white subtracts that result from his original move score to evaluate how good his original move really is.