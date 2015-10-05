/*
This code uses Genetic Algorithm to fing good combination of Company, strategy and parameters to get the best performance.
*/

// ishancpp1.cpp : main project file.

#include "stdafx.h"
/* Precompiled header is a (C or C++) header file that is compiled into an intermediate form that is faster to process for the compiler. 
If you include #include "stdafx.h" before other headers includes then the compiler will find the compiled header files from stdafx.h and does not compiled it from scratch. but if compiler doesn't find any compiled header files from stdafx.h then first it compiles that files and then stores its compiled version in stdafx.h. So that it can be use for next time compilation.*/

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <sstream>
#include <fstream>
#include <vector>
#include <typeinfo>
#include <map>
#include <algorithm>

using namespace std;

/*class priceseries has structure packettype to hold the daily date and prices. 2 constructors and methods to get the private values*/
class priceseries
{	
//http://stackoverflow.com/questions/10130755/classes-get-function-return-more-than-one-value
//http://stackoverflow.com/questions/16930296/accessing-member-of-structure-within-a-class
	struct packettype
{
	std::string Date;
	std::string Open, Close;
	//double Open, Close;
	//packettype();
};
	packettype packet;
	
public:
	//priceseries(std::string, double, double);
	//priceseries(void);
	priceseries(void);
	priceseries(std::string, std::string, std::string);
	std::string get_date(void);
	std::string get_open(void);
	std::string get_close(void);
};

/*
priceseries::priceseries(std::string string1, double double1, double double2)
{
	packet.Date = string1;
	packet.Open = double1;
    packet.Close = double2;
}

priceseries::priceseries(void)
{
	packet.Date = "";
	packet.Open = 0.0;
    packet.Close = 0.0;
}
*/
/*Constructor for assigning private members with values from users*/
priceseries::priceseries(std::string string1, std::string string2, std::string string3)
{
	packet.Date = string1;
	packet.Open = string2;
    packet.Close = string3;
}

/*Constructor for assigning private members with default blank values*/
priceseries::priceseries(void)
{
	packet.Date = "";
	packet.Open = "";
    packet.Close = "";
}

/*Following 3 methods return the members from the private structure*/
std::string priceseries::get_date(void)
{
	return packet.Date;
}
std::string priceseries::get_open(void)
{
	return packet.Open;
}
std::string priceseries::get_close(void)
{
	return packet.Close;
}

/*Defining filereader function to read yahoo finance stock data from hard drive. Argument taken by function is name of the file.*/
vector <priceseries> filereader(string filename)
{
	vector <priceseries> data1;

	int num_of_lines_count = 0;
	std::string line_;
	std::string token;

	/*The term stream is a general abstraction (concept) of any construct that allows you to simply send any number of bytes, or to receive any number of bytes.*/
	/*istringstream is Input stream class to operate on strings.*/
	istringstream iss(line_);

	/*ifstream is input stream class to operate on files.*/
	ifstream file_("C:/Users/Ishan/Downloads/" + filename + ".csv");

	if(file_.is_open())
	{   
		/**/
	 vector <vector <string> > data;
	 //vector <priceseries> data1;
     ifstream infile("C:/Users/Ishan/Downloads/" + filename + ".csv");

	 /*to read the stock prices file*/
  while (infile)
  {
    string s;
    if (!getline( infile, s )) break;

	/*s will hold 1 field from the file from a line*/
    istringstream ss( s );

	/*to hold a single day's record corresponding to 1 line of the file*/
   vector <string> record;

	while (ss)
    {
      string s;
      if (!getline( ss, s, ';' )) break;
      record.push_back( s );
	}	
	  //cout<<"record 0 1 2 are "<<record[0]<<endl<<record[1]<<endl<<record[4]<<endl;
	/*recordobject is an object of priceseries type to hold any day's date, open and close*/
	  priceseries recordobject(record[0],record[1],record[4]);
	  std::string date1=recordobject.get_date();
	  std::string open1=recordobject.get_open();
	  std::string close1=recordobject.get_close();
	  //cout<<"date1 open1 and close1 are "<<date1<<open1<<close1<<endl;

	  /*data is a vector <vector <string>> where each vector<string> holds the full line (all fields from the stock file)*/
   data.push_back( record );

   /*data1 is a vector <priceseries> to hold each day's date, open and close in a vector of priceseries class*/
   data1.push_back(recordobject);
  }

  //priceseries ps = data1[10];
  //cout<<"10th row's elements are "<< ps.get_date()<<ps.get_open()<<ps.get_close()<<endl; 

  /*After the while(infile) loop this is  an additional check to ensure that the eof has been reached*/
  if (!infile.eof())
  {
    cerr << "Fooey!\n";
  } 

	} // end of if(file_.is_open())

	else 
	{
			std::cout<<"file is not open"<< '\n';
	}

	/*
	int* a = NULL;   // Pointer to int, initialize to nothing.
    // cin >> num_of_lines_count;        // Read in the size

//http://www.cplusplus.com/doc/tutorial/dynamic/
/*There may be cases where the memory needs of a program can only be determined during runtime. For example, when the memory needed depends on user input. On these cases, programs need to dynamically allocate memory, for which the C++ language integrates the operators new and delete.
Ex. - int * foo; foo = new int [5]; In first statement foo is declared as an integer pointer. Then in second statement, a block of size sufficient to hold 5 
integers is allocated during runtime on the heap and address of first element is stored in foo*/

    a = new int[num_of_lines_count];  // Allocate n ints and save ptr in a.
    for (int i=0; i<num_of_lines_count; i++) {
    a[i] = 0;    // Initialize all elements to zero.
    }

    // Use a as a normal array
    delete [] a;  // When done, free memory pointed to by a.
    a = NULL;     // Clear a to prevent using invalid memory reference. 

	//return statement of filereader function
	return data1;

}

/*class chromosome defined here to hold 7 bit string, maps for company name, parameter A and parameter B*/
class chromosome
{
	/*7 bit string. First 2 bits hold company name, 3rd bit holds strategy (SMA or EMA), 4-5th bits hold parameter A, 6-7th bits hold paraemeter B*/
        string bits;
	
        //The bits above and the 3 maps below will get defined in the default constructor of the class
	//Map for first 2 bits which would hold company 
	std::map<std::string, std::string> map_companies;
	//Map for parameter A	
	std::map<std::string, int> map_paramA;
	//Map for parameter B
	std::map<std::string, int> map_paramB;

public:

	/*Public function to get company name of object from 1st 2 bits of private string bits. Iterator on map_companies used for the same*/
std::string get_company(void)
{
	
	std::string company=bits.substr(0,2);
	
        /* http://www.cplusplus.com/reference/iterator/ */
       /*An iterator is any object that, pointing to some element in a range of elements (such as an array or a container), 
        has the ability to iterate through the elements of that range using a set of operators (with at least the increment (++) 
        and dereference (*) operators).The most obvious form of iterator is a pointer: A pointer can point to elements in an array,
        and can iterate through them using the increment operator (++). But other kinds of iterators are possible.*/
       /*http://www.cplusplus.com/reference/map/map/find/ 
         std::map::find - public member function  iterator find (const key_type& k);
Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.*/
	//http://www.java2s.com/Tutorial/Cpp/0600__STL-Algorithms-Iterator/Findavalueinmapbykey.htm
	map<std::string, std::string>::iterator p;
	p = map_companies.find(company);
  if(p != map_companies.end()) 
     return (p->second);/* will return value corresponding to key company*/
  else
    return "Error!";
}

/*Public function to get strategy name of object from 3rd bit of private string bits*/
std::string get_strategy(void)
{
	if (bits.substr(2,1)=="0") return "SMA";
	else if (bits.substr(2,1)=="1") return "EMA";
	else return "Error!";
}

/*Public function to get parameter A of object from 4-5th bits of private string bits. Iterator on map_paramA used for the same*/
int get_paramA(void)
{
	std::string paramA=bits.substr(3,2);
	
	//http://www.java2s.com/Tutorial/Cpp/0600__STL-Algorithms-Iterator/Findavalueinmapbykey.htm
	map<std::string, int>::iterator p;
	p = map_paramA.find(paramA);
  if(p != map_paramA.end()) 
     return (p->second);
  else
    return 0;

}

/*Public function to get parameter B of object from 6-7th bits of private string bits. Iterator on map_paramB used for the same*/
int get_paramB(void)
{	
	std::string paramB=bits.substr(5,2);
	
	//http://www.java2s.com/Tutorial/Cpp/0600__STL-Algorithms-Iterator/Findavalueinmapbykey.htm
	map<std::string, int>::iterator p;
	p = map_paramB.find(paramB);
  if(p != map_paramB.end()) 
     return (p->second);
  else
    return 0;
}

/*Public function to get full private string bits*/
std::string get_chromosome(void)
{
	return bits;
}

/*Public function to change full private string bits*/
void change_chromosome(std::string string1)
{
	bits = string1;
}

/*Default construvtor of class chromosome to initialize private string bits and the 3 maps. Would run each time an object of class chromosome is 
declared*/
chromosome(void)
{
	bits ="0000000";	

	map_companies.insert(std::pair<std::string, std::string>("00", "Google"));
	map_companies.insert(std::pair<std::string, std::string>("01", "Facebook"));
	map_companies.insert(std::pair<std::string, std::string>("10", "IBM"));
	map_companies.insert(std::pair<std::string, std::string>("11", "LinkedIn"));
		
	map_paramA.insert(std::pair<std::string, int>("00", 10));
	map_paramA.insert(std::pair<std::string, int>("01", 20));
	map_paramA.insert(std::pair<std::string, int>("10", 30));
	map_paramA.insert(std::pair<std::string, int>("11", 40));
	
	map_paramB.insert(std::pair<std::string, int>("00", 15));
	map_paramB.insert(std::pair<std::string, int>("01", 25));
	map_paramB.insert(std::pair<std::string, int>("10", 35));
	map_paramB.insert(std::pair<std::string, int>("11", 45));
}

}; //end of class chromosome

/*Function to find fitness of object of class chromosome. Takes chromosome and map of company name : vector priceseries as inputs*/
/*From the chromosome, the function extracts company name and from the map it uses the company name to get the vector of priceseries for that company*/
double fitness(chromosome chrom1,std::map<std::string, vector <priceseries>> prices1)
{
    std::string company = chrom1.get_company();
	std::string strategy = chrom1.get_strategy();
	int paramA = chrom1.get_paramA();
	int paramB = chrom1.get_paramB();
		
	//cout<<"strategy "<<strategy;

	//http://www.java2s.com/Tutorial/Cpp/0600__STL-Algorithms-Iterator/Findavalueinmapbykey.htm
	map<std::string, vector <priceseries>>::iterator p;
	p = prices1.find(company);
  if(p != prices1.end())
  {
	  /*Signal can only be generated for overlapping portions of (Length of price history - Lookback period of parameter A) 
	  and (Length of price history - Lookback period of parameter B). Final part is alwyas overlapping. Only back part is non-overlapping. 
	  So trade can only be done for min of the two : (Length of price history - Lookback period of parameter A) 
	  and (Length of price history - Lookback period of parameter B)*/

	  size_t num_trading_days = min((p->second).size() - paramA,(p->second).size() - paramB);

	  /*num_trading_days is found during run-time. So this is a method to dynamically allocate array during run-time using pointer*/
	  int* signal;// Pointer to int, initialize to nothing.
	  signal = new int[num_trading_days];// Allocate n ints and save ptr in a.

	  if (strategy == "SMA")
   {
	  double* SMA_A = NULL;
	  double* SMA_B = NULL;   // Pointer to int, initialize to nothing.
    SMA_A = new double[num_trading_days];// Allocate n ints and save ptr in a
	SMA_B = new double[num_trading_days];// Allocate n ints and save ptr in a
		
	//cout<<"strategy "<<strategy<<"num_trading_days "<<num_trading_days;
	
	/*To find rolling SMA with lookback period param A*/
    for (size_t i = 0; i<num_trading_days; i++)
	{   double sumA = 0;
	    for (size_t j = i; j < i + paramA; j++)
		{
			sumA=sumA+std::stod((p->second)[j].get_open());
		}
		SMA_A[i] = sumA/paramA;
		//cout<<"SMA_A["<<i<<"]"<<SMA_A[i];
	}
	
		/*To find rolling SMA with lookback period param B*/
	for (size_t i = 0; i<num_trading_days; i++)
	{   double sumB = 0;
	    for (size_t j = i; j < i + paramB; j++)
		{
			sumB=sumB+std::stod((p->second)[j].get_open());
			
		}
		SMA_B[i] = sumB/paramB;
		//cout<<"SMA_B["<<i<<"]"<<SMA_B[i];
	}
	
	for (size_t i = 0; i<(num_trading_days); i++)
	{  
		/*signal generation in case of SMA. Small period SMA > Large period SMA. So upward trend and thus buy. Else sell.*/
		if (SMA_A[i]>SMA_B[i]) signal[i]=1; else signal[i]=-1;
	}

    delete [] SMA_A;  // When done, free memory pointed to by a.
	delete [] SMA_B;  // When done, free memory pointed to by b.
    SMA_A = SMA_B = NULL;     // Clear a to prevent using invalid memory reference. 
   }
	  else if (strategy == "EMA")
   {
	  double* EMA_A = NULL;
	  double* EMA_B = NULL;   // Pointer to int, initialize to nothing.

    EMA_A = new double[num_trading_days];// Allocate n ints and save ptr in a.
	EMA_B = new double[num_trading_days];// Allocate n ints and save ptr in a.
	EMA_A[0]=std::stod((p->second)[0].get_open());
	EMA_B[0]=std::stod((p->second)[0].get_open());

	double alpha_A=2/(1+paramA);
	double alpha_B=2/(1+paramB);
	
	//cout<<"strategy "<<strategy<<"num_trading_days "<<num_trading_days;

    for (size_t i = 1; i<(num_trading_days); i++)
	{   
	    	//http://www.investopedia.com/articles/trading/10/simple-exponential-moving-averages-compare.asp
			EMA_A[i] = std::stod((p->second)[i].get_open())*alpha_A + EMA_A[i-1]*(1-alpha_A);
			//cout<<"EMA_A["<<i<<"]"<<EMA_A[i];
	}
	
	for (size_t i = 1; i<(num_trading_days); i++)
	{  
			//http://www.investopedia.com/articles/trading/10/simple-exponential-moving-averages-compare.asp
			EMA_B[i] = std::stod((p->second)[i].get_open())*alpha_A + EMA_B[i-1]*(1-alpha_A);
			//cout<<"EMA_B["<<i<<"]"<<EMA_B[i];
	}
	
	for (size_t i = 0; i<(num_trading_days); i++)
	{  
		/*signal generation in case of EMA*/
		if (EMA_A[i]>EMA_B[i]) signal[i]=1; else signal[i]=-1;
		//cout<<"signal["<<i<<"]"<<signal[i];
	}
	
	delete [] EMA_A;  // When done, free memory pointed to by a.
	delete [] EMA_B;  // When done, free memory pointed to by b.
    EMA_A = EMA_B = NULL;  // Clear a to prevent using invalid memory reference.

   }
   else
   {
		cout << company <<" strategy invalid";
		return 0.0;
   }
	  	 // Create the DailyReturns array
	 double* DailyReturns = NULL; // Pointer to double, initialize to nothing
	 DailyReturns = new double[num_trading_days]; // Allocate n ints and save ptr in a

	 for (size_t i = 0; i<(num_trading_days); i++)
	{  
		DailyReturns[i]=signal[i]*(std::stod((p->second)[i].get_close())-std::stod((p->second)[i].get_open()));
		//cout<<"DailyReturns["<<i<<"]"<<DailyReturns[i];
	}

	 //calculate mean of daily returns

	 double sumformean=0.0;

	 for (size_t i = 0; i<(num_trading_days); i++)
	{  
		sumformean=sumformean+DailyReturns[i];
	}

	 double mean=sumformean/num_trading_days;

	  double sumforSD=0.0;

	  for (size_t i = 0; i<(num_trading_days); i++)
	{  
		sumforSD=sumforSD+(DailyReturns[i]-mean)*(DailyReturns[i]-mean);
	}
	 double SD=sumforSD/(num_trading_days-1);

	 /*Sharpe Ratio is used as fitness function*/
	 double SharpeRatio;
	 SharpeRatio=(mean/SD);
	 //cout<<"SharpeRatio "<<SharpeRatio;
	 return SharpeRatio;
  }
  else
    {
		cout << company <<" prices not found";
		return 0.0;
    }
}


vector <chromosome> initialization(int n)
{
	/*we want to make n divisible by 4 as we will select half of population before crossover and this half should be divisible by 2 so that pairs can form*/
	if (n%4 == 1) n=n+3;
	else  if (n%4 == 2) n=n+2;
	else  if (n%4 == 3) n=n+1;
	
  	//Random number generator
	random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<> dist(0,1); // distribute results between 0 and 1 inclusive.

	vector <chromosome> VecOfChrom;

	for (int i=0;i<n;i++)
	{
	chromosome chrom1;
	//cout<<endl<<chrom1.get_company()<<endl<<chrom1.get_strategy()<<endl<<chrom1.get_paramA()<<endl<<chrom1.get_paramB()<<endl;

    std::string bit_values="";
	for (int j=0;j<7;j++)
	{
	cout << dist(gen);
	if (dist(gen)==1) bit_values=bit_values+'1';
	else bit_values=bit_values+'0';
	}
	chrom1.change_chromosome(bit_values);
	VecOfChrom.push_back(chrom1);
	//cout<<endl<<chrom1.get_company()<<endl<<chrom1.get_strategy()<<endl<<chrom1.get_paramA()<<endl<<chrom1.get_paramB()<<endl;
    }
	
	return VecOfChrom;
}

vector <chromosome> selectParents(vector <chromosome> population,std::map<std::string, vector <priceseries>> prices1)
{	
	std::vector <double> fitness_vector;

	for(size_t i=0;i<population.size();i++)
	{		
		fitness_vector.push_back(fitness(population.at(i),prices1));
		//cout<<"fitness_vector[i]"<<fitness_vector.at(i);
	}
	//http://stackoverflow.com/questions/10158756/using-stdmax-element-on-a-vectordouble
  //http://en.cppreference.com/w/cpp/language/auto
  //http://www.cplusplus.com/reference/algorithm/max_element/
  //std::cout << "The smallest element is " << *std::min_element(std::begin(fitness_vector), std::end(fitness_vector)) << '\n';
  //std::cout << "The largest element is "  << *std::max_element(std::begin(fitness_vector), std::end(fitness_vector)) << '\n';
  
  vector <chromosome> subpopulation;
  vector <double> subpopulationfitness;

  for(size_t i=0;i<population.size()/2;i++) //only top half of population to be selected with greatest fitness values
  {
  auto biggest = std::max_element(std::begin(fitness_vector), std::end(fitness_vector));
  //std::cout << "Max element is " << *biggest << " at position " << std::distance(std::begin(fitness_vector), biggest) << std::endl;
  
  subpopulation.push_back(population[std::distance(std::begin(fitness_vector), biggest)]);
  subpopulationfitness.push_back(fitness_vector[std::distance(std::begin(fitness_vector), biggest)]);

  
  fitness_vector[std::distance(std::begin(fitness_vector), biggest)]= -99999;
  }

  for(size_t i=0;i<population.size()/2;i++) //only top half of population to be selected with greatest fitness values
  {
	  //cout<<"subpopulationfitness[i] is"<<subpopulationfitness[i];
	  //cout<<"subpopulation[i] is"<<(subpopulation.at(i)).get_company();
  }
    
	return subpopulation;
		
}

vector <chromosome> crossoverWithmutation(vector <chromosome> subpopulation)
{
	//This function would take subpopulation and randomly select 2 witout replacement during a run of the loop
	//it will do crossover and mutation on progeny
	//these two parents and mutated progeny would be added to new population
	//these 2 parents would be removed from the subpopulation and in the next run of the loop we will again randomly select 2 parents without replacement
	//...and so on

	//Another way is to do random_shuffle : http://stackoverflow.com/questions/18085633/c-generating-random-numbers-without-repetition-output-screen-is-just-blank-wi
	
	//Just generate the numbers 1 to 9, then shuffle them randomly using std::random_shuffle.

//int nums[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//std::random_shuffle(nums, nums + 9);
//This will leave nums with the numbers from 1 to 9 in random order, with no repetitions.
	
	vector <int> ordered_index; 
	vector <chromosome> subpopulation_copy=subpopulation;

	for(size_t i=0;i<subpopulation.size();i++)
        {
                ordered_index.push_back(i);
				//cout<<endl<<"ordered_index:"<<endl<<ordered_index.at(i);
        }

    std::random_shuffle (ordered_index.begin(), ordered_index.end());
	
	for(size_t i=0;i<subpopulation.size();i++)
        {
				//cout<<endl<<"ordered_index:"<<endl<<ordered_index.at(i);
        }

	for(size_t i=0;i<subpopulation.size();i=i+2)
	{
		string parent1 = subpopulation.at(ordered_index.at(i)).get_chromosome();
		string parent2 = subpopulation.at(ordered_index.at(i+1)).get_chromosome();

		//cout<<endl<<"parent1"<<parent1<<" parent2"<<parent2;
				
  	//Random number generator
	random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<> dist(0,5); // distribute results between 0 and 6 inclusive.
		
	    chromosome progeny1;
		chromosome progeny2;

		int point_of_crossover = dist(gen);
		
		//crossover
	std::string string1 = parent1.substr(0,point_of_crossover+1)+parent2.substr(point_of_crossover+1,7-point_of_crossover-1);	
	std::string string2 = parent2.substr(0,point_of_crossover+1)+parent1.substr(point_of_crossover+1,7-point_of_crossover-1);

	progeny1.change_chromosome(string1);
	progeny2.change_chromosome(string2);
		
	//mutation
	uniform_int_distribution<> distinct(0,5);//to determine position where mutation may occur
	std::uniform_real_distribution<double> distribution(0.0,1.0);//to incorporate probability of mutation

	//mutation for progeny 1
	if  (distribution(gen) < .05) {
		int position_mutation_progeny1 = distinct(gen);
		if (string1[position_mutation_progeny1]=='1') string1[position_mutation_progeny1] = '0';
		else if (string1[position_mutation_progeny1]=='0') string1[position_mutation_progeny1] = '1';
	}
	
	//mutation for progeny 2
	if  (distribution(gen) < .05) {
		int position_mutation_progeny2 = distinct(gen);
		if (string2[position_mutation_progeny2]=='1') string2[position_mutation_progeny2] = '0';
		else if (string2[position_mutation_progeny2]=='0') string2[position_mutation_progeny2] = '1';
	}

	progeny1.change_chromosome(string1);
	progeny2.change_chromosome(string2);

	subpopulation_copy.push_back(progeny1); //adding daughter genes to subpopulation_copy
	subpopulation_copy.push_back(progeny2); //adding daughter genes to subpopulation_copy
	}

	return subpopulation_copy;
}


double avgfitnessgeneration(vector <chromosome> a_population, std::map<std::string, vector <priceseries>> prices1)//to be applied in calculating average fitness of a generation
{
        double sum_of_elems=0;
        for(size_t i=0;i<a_population.size();i++)
        {
                sum_of_elems+=fitness(a_population.at(i), prices1);
				//cout<<endl<<"from avgfitnessgeneration function:"<<endl<<"sum_of_elems"<<sum_of_elems;
        }
        double avgfitnessgeneration = sum_of_elems/a_population.size();
		//cout<<endl<<"avgfitnessgeneration "<<avgfitnessgeneration<<endl;
		
        return (avgfitnessgeneration);
}



double avgofvector(vector <double> AvgFitnessGeneration)//to be applied in calculating average fitness of last 20 generations or lesser
{
	if (AvgFitnessGeneration.size() < 20)
	{
	double sum_of_elems=0;
	for(size_t i=0;i<AvgFitnessGeneration.size();i++)
	{
		sum_of_elems+=AvgFitnessGeneration.at(i);
	}
	double AvgLastTwentyOrLess=sum_of_elems/AvgFitnessGeneration.size();
	
	return (AvgLastTwentyOrLess);
	}
	else 
	{
	double sum_of_elems=0;
	for(size_t i=AvgFitnessGeneration.size()-20;i<AvgFitnessGeneration.size();i++)
	{
		sum_of_elems+=AvgFitnessGeneration.at(i);
	}
	double AvgLastTwentyOrLess=sum_of_elems/20;
	
	return (AvgLastTwentyOrLess);
	}
}

int main()
{   
	vector <priceseries> data2;
	std::map<std::string, vector <priceseries>> prices;

    data2=filereader("Google");//remove first line with variable names from csv file or else error will occur
	prices.insert(std::pair<std::string, vector <priceseries>>("Google", data2));	
    data2=filereader("Facebook");//remove first line with variable names from csv file or else error will occur
	prices.insert(std::pair<std::string, vector <priceseries>>("Facebook", data2));
	data2=filereader("IBM");
	prices.insert(std::pair<std::string, vector <priceseries>>("IBM", data2));
	data2=filereader("LinkedIn");
	prices.insert(std::pair<std::string, vector <priceseries>>("LinkedIn", data2));
	
	chromosome chrom1;
	//cout<<endl<<chrom1.get_company()<<endl<<chrom1.get_strategy()<<endl<<chrom1.get_paramA()<<endl<<chrom1.get_paramB()<<endl;
	chrom1.change_chromosome("0011111");
	//cout<<endl<<chrom1.get_company()<<endl<<chrom1.get_strategy()<<endl<<chrom1.get_paramA()<<endl<<chrom1.get_paramB()<<endl;
		
	//cout<<endl<<"Initialization function:";
	vector <chromosome> population = initialization(3);
	vector <chromosome> subpopulation;

	vector <double> AvgFitnessGeneration;
	int NumberOfGenerations=0;

	while(NumberOfGenerations < 10 /*|| avgofvector(AvgFitnessGeneration)>AvgFitnessGeneration.at(NumberOfGenerations)*/)
	{
		AvgFitnessGeneration.push_back(avgfitnessgeneration(population, prices));
		cout<<"NumberOfGenerations:"<<endl<<NumberOfGenerations<<endl<<"AvgFitnessGeneration at"<< NumberOfGenerations<<": "<<AvgFitnessGeneration.at(NumberOfGenerations)<<endl;
		//cout<<"avgofvector(AvgFitnessGeneration):"<<endl<<avgofvector(AvgFitnessGeneration)<<endl;
		vector <chromosome> subpopulation = selectParents(population,prices);
		population=crossoverWithmutation(subpopulation);
		cout<<endl<<"subpopulation.size()"<<subpopulation.size();
		//double d=crossoverWithmutation(subpopulation);
		NumberOfGenerations+=1;
	}
	cout<<"end of code";
	std::cin.get();
	return 0;
} 
