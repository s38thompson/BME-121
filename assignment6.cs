#nullable enable

using System;
using System.IO;
using System.Collections.Generic;

using static System.Console;

namespace Bme121
{
    // Class to represent a water-quality sample for a New York City beach.
    // Data comes from a CSV file. One sample line is shown below, to illustrate the format.
    //     NP2109080725-1.2,09/08/2021,SOUTH BEACH,Center,53
    // The fields are sample identifier, date in mm/dd/yyyy format, beach name
    // sample location, and enterococci level in MPN/100 mL.
    
    class Sample : IComparable <Sample> // icomparable is interface- so you can use compare to method
    {
		public string SampleIdentifier		{ get; private set; }
		public string Date					{ get; private set; }
		public string BeachName				{ get; private set; }
		public string SampleLocation		{ get; private set; } 
		public double EnterococciLevel		{ get; private set; }
		
		public Sample( string input)
		{
			string[] sample = input.Split(',');
			
			SampleIdentifier = sample[0];
			Date = sample[1];
			BeachName = sample[2];
			SampleLocation = sample[3];
			EnterococciLevel = double.Parse(sample[4]);
		}
		
		public int Month 
		{
			get {return int.Parse((Date.Split("/"))[0]);}
		}
		public int Day 
		{
			get {return int.Parse((Date.Split("/"))[1]);}
		}
		public int Year 
		{
			get {return int.Parse((Date.Split("/"))[2]);}
		}
		
		public override string ToString()
		{
			return $"{SampleIdentifier}";
		}
		
		
		public int CompareTo (Sample other)
		{
			// compare strings of location string.compareto will equal -1 (this is less than other) , 0 or 1 (other is less than this)
			int nameCompare = string.Compare(this.BeachName, other.BeachName);
			if (nameCompare !=0) return nameCompare;
			
			//location
			if (this.SampleLocation == "Left" && other.SampleLocation == "Right" || this.SampleLocation == "Center" && other.SampleLocation == "Right" || this.SampleLocation == "Left" && other.SampleLocation == "Center") return -1;
			if (this.SampleLocation == "Right" && other.SampleLocation == "Left" || this.SampleLocation == "Right" && other.SampleLocation == "Center" || this.SampleLocation == "Center" && other.SampleLocation == "Left") return 1;

			//year
			if (this.Year < other.Year) return -1;
			else if (this.Year > other.Year) return 1;
			
			//month
			if (this.Month < other.Month) return -1;
			else if (this.Month > other.Month) return 1;
			
			//day
			if (this.Day < other.Day) return -1;
			else if (this.Day > other.Day) return 1;
			
			return 0;
		}
    }
    
    // Program to report New York City beach water samples where the
    // enterococci level is 5000 MPN/100 mL or more.
    
    static class Program
    {
        static void Main( )
        {
		    string path = "DOHMH_Beach_Water_Quality_Data_2.csv";
			using FileStream    file = new FileStream(path, FileMode.Open, FileAccess.Read);
            using StreamReader  sr = new StreamReader(file);
            
            List< Sample > sampleDetails = new List< Sample > ();
            
            WriteLine( );            
            
            while( ! sr.EndOfStream )
            {
                Sample specificSample = new Sample( sr.ReadLine()!);
                sampleDetails.Add(specificSample);
			}
			
			 Sample [] samples = sampleDetails.ToArray();
			Array.Sort(samples);
			
			 for ( int i = 0; i < samples.Length; i++)
			{
					Sample s = samples[i];
					
					 if (s.BeachName == "WOLFE'S POND PARK" && (s.Month == 8 || s.Month == 9) && s.Year == 2021)
					 {
						WriteLine("{0} {1} {2} {3} {4} {5} MPN/100 mL", s.Year, s.Month, s.Day, s.BeachName, s.SampleLocation, s.EnterococciLevel); 
					}
			}
                
                
	    }
	}
				
}
               
			
            
       
    
