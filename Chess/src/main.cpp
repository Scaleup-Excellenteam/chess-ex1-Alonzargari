// Chess 
#include "Chess.h"
#include "BoardManager.h"

int main()
{
	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
//	string board = "##########N######QK#############B#########R######n##b###r#r#k#q#";
	Chess a(board);
	int codeResponse = 0;
	string res = a.getInput();
	auto boardManger = BoardManager(board);
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
		{ // put your code here instead that code
			codeResponse=boardManger.manageMovment(res);
			cout << "code response >> ";
			//cin >> codeResponse;
		}
		/**/

		a.setCodeResponse(codeResponse);
		res = a.getInput(); 
	}

	cout << endl << "Exiting " << endl; 
	return 0;
}