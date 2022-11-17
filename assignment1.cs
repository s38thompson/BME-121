#nullable enable
using System;
using static System.Console;

namespace Bme121
{
    record Player( string Colour, string Symbol, string Name, string playerNumber );
    
    // The `record` is a kind of automatic class in the sense that the compiler generates
    // the fields and constructor and some other things just from this one line.
    // There's a rationale for the capital letters on the variable names (later).
    // For now you can think of it as roughly equivalent to a nonstatic `class` with three
    // public fields and a three-parameter constructor which initializes the fields.
    // It would be like the following. The 'readonly' means you can't change the field value
    // after it is set by the constructor method.
    
    //class Player
    //{
        //public readonly string Colour;
        //public readonly string Symbol;
        //public readonly string Name;
        
        //public Player( string Colour, string Symbol, string Name )
        //{
            //this.Colour = Colour;
            //this.Symbol = Symbol;
            //this.Name = Name;
        //}
    //}
    
    static partial class Program
    {
        // Display common text for the top of the screen.
        
        static void Welcome( )
        {
			WriteLine("Welcome to Othello. Get ready to play!");
        }
        
        // Collect a player name or default to form the player record.
        
        static Player NewPlayer( string colour, string symbol, string defaultName, string playerNumber )
        {
		// writeline and readline to set players names and then set to default if no answer
	
			WriteLine($"Enter a name for Player {playerNumber}:");
			string response = ReadLine();
			
			if (response == "")
			return new Player(colour, symbol, defaultName, playerNumber);
			WriteLine($"Your symbol is '{symbol}'.");
			
            return new Player(colour, symbol, response, playerNumber);
            WriteLine($"Your symbol is '{symbol}'.");
        }
        
        // Determine which player goes first or default.
        
        static int GetFirstTurn( Player[ ] players, int defaultFirst )
        {
			WriteLine("Enter the number of the player who wants to go first (Enter 1 or 2): ");
			int firstPlayer = int.Parse(ReadLine());
			
			if (firstPlayer > 2)
			{
				WriteLine($"An invalid player number was entered, {players[defaultFirst].Name} goes first");
				return defaultFirst;
			}
			
			WriteLine($"Number {firstPlayer} was selected, so {players[firstPlayer - 1].Name} goes first");
            return firstPlayer - 1;
        }
        
        // Get a board size (between 4 and 26 and even) or default, for one direction.
        
        static int GetBoardSize( string direction, int defaultSize )
        {
            //// enter number of direction of board, parse answer, check if within parameters, if yes then return if not then set to an automatic value
           WriteLine($"Enter your desired number of {direction} (between 4 and 26):");
           int boardSize = int.Parse(ReadLine());
           
           if (boardSize > 3 && boardSize < 27 && boardSize % 2 == 0)
           {
			   return boardSize;
		   }
           else 
           {
			   WriteLine($"Invalid number of {direction} entered. Board has automatically been set to {defaultSize} {direction}.");
			   return 8;
			}
           
        }
        
        // Get a move from a player.
        
        static string GetMove( Player player )
        {
            WriteLine($"{player.Name} you're up. Make a move.");
            string move = ReadLine();
            return move;
        }
        
        // Try to make a move. Return true if it worked.
        
        static bool TryMove( string[ , ] board, Player player, string move )
        {
           if ( move == "skip" )
           {
			   return true;
			}
			if ( move.Length != 2)
			{
				return false;
			}
			
		    int row = IndexAtLetter(move[0].ToString());
		    int col = IndexAtLetter(move[1].ToString());
		    
		    if(row == -1 || col == -1)
		    {
				return false;
			}
		    
		    int rowMax = board.GetLength(0);
		    int colMax = board.GetLength(1);
		    
		   if (row >= rowMax || col >= colMax)
		   {
			  return false; 
		   }
		   
		   if (board[row, col] != " ")
		   {
			   return false;
		   }
		   
		   bool [] passedDirection = new bool [8];

		   passedDirection[0] = TryDirection(board, player, row, -1, col, - 1); //top left
		   passedDirection[1] = TryDirection(board, player, row, -1, col, 0); // top
		   passedDirection[2] = TryDirection(board, player, row, -1, col, 1); // top right
		   passedDirection[3] = TryDirection(board, player, row, 0, col, 1); // right
		   passedDirection[4] = TryDirection(board, player, row, 1, col, 1); // bottom right
		   passedDirection[5] = TryDirection(board, player, row, 1, col, 0); // bottom
		   passedDirection[6] = TryDirection(board, player, row, 1, col, -1); // bottom left
		   passedDirection[7] = TryDirection(board, player, row, 0, col, -1); // left
		   
		   foreach (bool direction in passedDirection)
		   {
			   
			   if(direction == true)
			   {
				  board[row, col] = player.Symbol;
				  return true; 
			   }
		   }

           return false;
        }
        
        // Do the flips along a direction specified by the row and column delta for one step.
        
        static bool TryDirection( string[ , ] board, Player player,
            int moveRow, int deltaRow, int moveCol, int deltaCol )
        {
            if ( moveRow + deltaRow >= board.GetLength(0) || moveCol + deltaCol >= board.GetLength(1) || moveRow + deltaRow < 0 || moveCol + deltaCol < 0)
            return false;
            
            if (board [moveRow + deltaRow, moveCol + deltaCol ] == " " || board [moveRow + deltaRow, moveCol + deltaCol ] == player.Symbol) 
            return false;
            
            int currentRow = moveRow + deltaRow;
            int currentCol = moveCol + deltaCol;
            
            while (currentRow < board.GetLength(0) && currentCol < board.GetLength(1) && currentRow >= 0  && currentCol >= 0)
            {
				
				if ( board [currentRow, currentCol] == " ")
				return false;
				
				if ( board [currentRow, currentCol] == player.Symbol)
				{					
					int flipRow = moveRow + deltaRow;
					int flipCol = moveCol + deltaCol;
					
					while ( flipRow != currentRow || flipCol != currentCol )
					{
						board [flipRow , flipCol] = player.Symbol;
						
						flipRow = flipRow + deltaRow;
						flipCol = flipCol + deltaCol;	
						
					}
				return true;
				}
				
				currentRow = currentRow + deltaRow;
				currentCol = currentCol + deltaCol;
			}
			
			return false;
        }
        
        // Count the discs to find the score for a player.
        
        static int GetScore( string[ , ] board, Player player )
        {
            int score = 0;
            for (int i = 0; i < board.GetLength(0); i++)
            {
				for (int j = 0; j < board.GetLength(0); j++)
				{
					if(board[i,j] == player.Symbol) score++;
				}
            }
            return score;
        }
        
        // Display a line of scores for all players.
        
        static void DisplayScores( string[ , ] board, Player[ ] players )
        {
			int scoreOne = GetScore(board, players[0]);
			int scoreTwo = GetScore(board, players[1]);
			
			WriteLine($"{players[0].Name}'s score: {scoreOne}");
			WriteLine($"{players[1].Name}'s score: {scoreTwo}");
			
        }
        
        // Display winner(s) and categorize their win over the defeated player(s).
        
        static void DisplayWinners( string[ , ] board, Player[ ] players )
        {
			int finalOne = GetScore(board, players[0]);
			int finalTwo = GetScore(board, players[1]);
			int scoreDifference1 = (finalOne - finalTwo);
			int scoreDifference2 = (finalTwo - finalOne);
			
			WriteLine($" Final score: \n {players[0].Name}: {finalOne} \n {players[1].Name}: {finalTwo}");
			
			if (finalOne > finalTwo)
			{
				WriteLine($"Congratulations * ~ * {players[0].Name} * ~ *, you're the winner by {scoreDifference1} points! \nBetter luck next time {players[1].Name} :( .");
			}
			
			if (finalOne < finalTwo)
			{
				WriteLine($"Congratulations * ~ * { players[1].Name} * ~ *, you're the winner by {scoreDifference2} points! \nBetter luck next time {players[0].Name} :( .");
			}
			
			if (finalOne == finalTwo)
			{
				WriteLine($"Great game {players[0].Name} and {players[1].Name}. \nIt's a tie.");
			}
        }
        
        static void Main( )
        {
            // Set up the players and game.
            // Note: I used an array of 'Player' objects to hold information about the players.
            // This allowed me to just pass one 'Player' object to methods needing to use
            // the player name, colour, or symbol in 'WriteLine' messages or board operation.
            // The array aspect allowed me to use the index to keep track or whose turn it is.
            // It is also possible to use separate variables or separate arrays instead
            // of an array of objects. It is possible to put the player information in
            // global variables (static field variables of the 'Program' class) so they
            // can be accessed by any of the methods without passing them directly as arguments.
            
            Welcome();
            
            Player[ ] players = new Player[ ] 
            {
                NewPlayer( colour: "black", symbol: "X", defaultName: "Black", playerNumber: "One" ),
                NewPlayer( colour: "white", symbol: "O", defaultName: "White", playerNumber: "Two"),
            };
            
            int turn = GetFirstTurn( players, defaultFirst: 0 );
           
            int rows = GetBoardSize( direction: "rows",    defaultSize: 8 );
            int cols = GetBoardSize( direction: "columns", defaultSize: 8 );
            
            string[ , ] game = NewBoard( rows, cols );
            
            WriteLine($"Good luck {players[0].Name} and {players[1].Name}. Let's play!");
            
            // Play the game.
            
            bool gameOver = false;
            while( ! gameOver )
            {
            
                DisplayBoard( game ); 
                DisplayScores( game, players );
                
                string move = GetMove( players[ turn ] );
                if( move == "quit" ) gameOver = true;
                else
                {
                    bool madeMove = TryMove( game, players[ turn ], move );
                    if( madeMove ) turn = ( turn + 1 ) % players.Length;
                    else 
                    {
                        Write( " Your choice didn't work!" );
                        Write( " Press <Enter> to try again." );
                        ReadLine( ); 
                    }
                }
                WriteLine("Nice move!");
            }
            
            // Show fhe final results.
            
            DisplayWinners( game, players );
            WriteLine( );
        }
    }
}
