#nullable enable
using System;
using static System.Console;

namespace Bme121
{
    static partial class Program
    {
        static void Main( )
        {
            string[ , ] game = NewBoard( rows: 8, cols: 8 );
            Console.Clear( );
            WriteLine( );
            WriteLine( " Welcome to Othello!" );
            WriteLine( );
            DisplayBoard( game );
            WriteLine( );
        }
    }
}
