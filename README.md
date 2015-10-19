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

/*class priceseries has structure packettype to hold the daily date and prices. 2 constructors and methods to get the private values*/
class priceseries

/*Filereader function to read yahoo finance stock data from hard drive. Argument taken by function is name of the file.*/
vector <priceseries> filereader(string filename)

/*class chromosome defined here to hold 7 bit string, maps for company name, parameter A and parameter B*/
class chromosome

/*Fitness function to find fitness of object of class chromosome. Takes chromosome and map of company name : vector priceseries as inputs*/
/*From the chromosome, the function extracts company name and from the map it uses the company name to get the vector of priceseries for that company*/
double fitness(chromosome chrom1,std::map<std::string, vector <priceseries>> prices1)

