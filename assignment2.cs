using System;
using static System.Console;

namespace Bme121
{
    static class Program
    {
        static void Main( )
        {
            Write( "Enter an integer: " );
            int n = int.Parse( ReadLine( ) );
            
            string primality = "untested";
            
            // Initial tests handle 'n < 2' and rule out 2, 7, and 61 as factors of 'n'.
            // The strong-probable-prime tests require the base to not divide 'n' evenly.
            
            if( n < 2 ) primality = "not prime";
            else if( n == 2 || n == 7 || n == 61 ) primality = "prime";
            else if( n % 2 == 0 || n % 7 == 0 || n % 61 == 0 ) primality = "not prime";
            else
            {
                // Reduce 'n-1' using equation (1) i.e., 
                // find an odd-integer 't' and integer 's' so that 'n-1 = 2^s t'.
                // Basically, remove as many factors of 2 from 'n-1' as is possible.
                				
                
                // TO DO: Equation (1) stuff, setting correct values of 's' and 't'.
                int t; 
                t = n - 1; 
                int s;
                s = 0; 
                while( t % 2 == 0 )
                { 
					t = t / 2;
					s = s + 1;
					// WriteLine( "n-1= {0}, s={1}, t={2}", n - 1, s, t);

				}
				                
                // Testing as strong probable prime (SPP) base 2, base 7, and base 61.
                
                bool isSppAllBases = true;
                
                foreach( int b in new int[ ]{ 2, 7, 61 } )
                {
                    // First test 'b^t mod n' using Equation (2).
                    // If this is one or 'n-1', then 'n' is a strong probable prime base 'b'.
                    
                    bool test1 = false;
                
                    // TO DO: Equation (2) stuff, setting correct value of 'test1'.
                    long accumulatedProduct = 1; 
                    long currentBase = b; 
                    int e = t;
                    //~ WriteLine( "e={0}, currentBase={1}, accumulatedProduct{2}", e, currentBase, accumulatedProduct );

                    while( e > 0 )
                    {
						if( e % 2 == 0 ) // even
						{
							currentBase = ( currentBase * currentBase ) % n;
							e = e / 2;
						}
						else // odd
						{
							accumulatedProduct = ( accumulatedProduct * currentBase ) % n;
							e = e - 1; 
						}
						//~ WriteLine( "e={0}, currentBase={1}, accumulatedProduct{2}", e, currentBase, accumulatedProduct );
					}
					
					// check result 1 or n-1
					if( accumulatedProduct == 1 || accumulatedProduct == n - 1 );
					{
						test1 = true;
					}
					
					//~ WriteLine( "test1={0}", test1 );
					
				
                    
                    // Second test '(b^t)^(2^r) mod n' using equation (3).
                    // If this is 'n-1' for a positive integer 'r' less than 's',
                    // then 'n' is a strong probable-prime in base 'b'. 
                    // We already have '(b^t)' from the previous test.
                    
                    bool test2 = false;
                    if( ! test1 )
                    {
                        // TO DO: Equation (3) stuff, setting correct value of 'test2'.
                        for( int r = 1; r < s; r ++ )
                        {
							if( test2 == false )
							{
								accumulatedProduct = (accumulatedProduct * accumulatedProduct ) % n;
								if ( accumulatedProduct == n - 1 ) test2 = true;
								
								}
								// WriteLine( "r={0}, accProd={1}, test2={2}", r, accumulatedProduct, test2 );
							} 
                    }
                    
                    isSppAllBases = test1 || test2;
                    if( ! isSppAllBases ) break;
                }
                
                if( isSppAllBases ) primality = "prime"; else primality = "not prime";
            }
                
            WriteLine( "The integer {0} is {1}", n, primality );
        }
    }
}
