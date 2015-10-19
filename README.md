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
