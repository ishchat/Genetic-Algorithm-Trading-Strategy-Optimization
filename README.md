# Genetic-Algorithm-Trading-Strategy-Optimization
This project is a C++ solution to the problem described in link :
http://gekkoquant.com/2013/08/18/genetic-algorithm-in-r-trend-following/

I have coded the complete Genetic Algorithm from scratch in C++. We are trying to to evolve the best genes using GA for optimal stock, strategy and parameter combination.

The criterion for fitness is Sharpe ratio.

The gene below contains 4 sub gene, a stock gene to select what stock to trade, a strategy gene to select what strategy to use, paramA sets a parameter used in your strategy and paramB sets another parameter to use in your strategy.

Gene = [StockGene,StrategyGene,ParamA,ParamB]

STOCK GENE	
00	Google
01	Facebook
10	IBM
11	LinkedIn

STRATEGY GENE	
0	Simple Moving Average
1	Exponential Moving Average

PARAMA GENE – MOVING AVERAGE 1 LOOKBACK	
00	10
01	20
10	30
11	40

PARAMB GENE – MOVING AVERAGE 2 LOOKBACK	
00	15
01	25
10	35
11	45

So Gene = [01,1,00,11]
Would be stock=Facebook, strategy=Exponential Moving Average,paramA=10,paramB=45]

The trading strategy is : 
1.When short period simple moving average (or exponential moving average) becomes greater than long period simple moving average (or exponential moving average) then it signals uptrend hence go long
2.When short period simple moving average (or exponential moving average) becomes smaller than long period simple moving average (or exponential moving average) then it signals downtrend hence go short

We start with random initialization of chromosomes and then iterate through the steps of Genetic Algorithm to achieve fitter chromosomes in terms of Sharpe ratio. These terminal chromosomes would have a combination of stock, strategy, short period moving average and long period moving average which have higher Sharpe ratio than previous generations. We can us these combinations in live trading.

The steps of Genetic algortihm are :
a.Check for termination condition. If it is satisfied then stop GA else continue. The condition used here is number of generations
b.Random initialization of starting Population
c.Select half of the population based on fitness (Sharpe ratio)
d.Crossover between randomly selected chromosome pairs followed by mutation
e.Go back to step a.

Description of various classes and functions used :

/*class priceseries has structure packettype to hold the daily date and prices. 2 constructors and methods to get the private values*/
class priceseries

/*Filereader function to read yahoo finance stock data from hard drive. Argument taken by function is name of the file.*/
vector <priceseries> filereader(string filename)

/*class chromosome defined here to hold 7 bit string, maps for company name, parameter A and parameter B*/
class chromosome

/*Fitness function to find fitness of object of class chromosome. Takes chromosome and map of company name : vector priceseries as inputs*/
/*From the chromosome, the function extracts company name and from the map it uses the company name to get the vector of priceseries for that company*/
double fitness(chromosome chrom1,std::map<std::string, vector <priceseries>> prices1)
/*Signal can only be generated for overlapping portions of (Length of price history - Lookback period of parameter A) 
	  and (Length of price history - Lookback period of parameter B). Final part is alwyas overlapping. Only back part is non-overlapping. 
	  So trade can only be done for min of the two : (Length of price history - Lookback period of parameter A) 
	  and (Length of price history - Lookback period of parameter B)*/
 size_t num_trading_days = min((p->second).size() - paramA,(p->second).size() - paramB);
fitness function calculates SMA or EMA 
/*To find rolling SMA with lookback period param A*/
/*To find rolling SMA with lookback period param B*/
for (size_t i = 0; i<(num_trading_days); i++)
	{  
		/*signal generation in case of SMA. Small period SMA > Large period SMA. So upward trend and thus buy. Else sell.*/
		if (SMA_A[i]>SMA_B[i]) signal[i]=1; else signal[i]=-1;
	}
	
	 SharpeRatio=(mean/SD);
	 
vector <chromosome> initialization(int n)
/*we want to make n divisible by 4 as we will select half of population before crossover and this half should be divisible by 2 so that pairs can form*/

vector <chromosome> selectParents(vector <chromosome> population,std::map<std::string, vector <priceseries>> prices1)
 /*only top half of population to be selected with greatest fitness values*/
 
 vector <chromosome> crossoverWithmutation(vector <chromosome> subpopulation)
 	//This function would take subpopulation and randomly select 2 witout replacement during a run of the loop
	//it will do crossover and mutation on progeny
	//these two parents and mutated progeny would be added to new population
	//these 2 parents would be removed from the subpopulation and in the next run of the loop we will again randomly select 2 parents without replacement
	//...and so on


 

	 


