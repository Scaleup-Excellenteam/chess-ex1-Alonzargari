// Chess 
#include "Chess.h"
#include "BoardManager.h"

int main()
{
	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
//	string board = "##########N######QK#############B#########R######n##b###r#r#k#q#";
	Chess a(board);
	int codeResponse = 0;
	auto boardManger = BoardManager(board);
	int depth;
	std::cout << "enter depth to calculate best moves in this depth" << std::endl;
	cin >> depth;
	boardManger.calculateBestMoves(depth);
	string res = a.getInput([&]() {return boardManger.printBestMovesOfDepth();});
	

	while (res != "exit")
	{
		/* 
		codeResponse value : 
		Illegal movements : 
		11 - there is not piece at the source  
		12 - the piece in the source is piece of your opponent
		13 - there one of your pieces at the destination 
		21 - illegal movement of that piece 
		31 - this movement will cause you checkmate

		legal movements : 
		41 - the last movement was legal and cause check 
		42 - the last movement was legal, next turn 
		*/

		/**/ 
		{ 
			codeResponse=boardManger.manageMovment(res);
			//to prevent the algorithm to be activate if the codeResponse is invalid move
			if (codeResponse == 41 || codeResponse == 42)
			{
				boardManger.calculateBestMoves(depth);
			}			//cin >> codeResponse;
		}
		/**/
		
		a.setCodeResponse(codeResponse);
		res = a.getInput([&]() {return boardManger.printBestMovesOfDepth();});
	}

	cout << endl << "Exiting " << endl; 
	return 0;
}