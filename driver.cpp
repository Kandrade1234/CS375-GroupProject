#include <iostream>
#include <stdio.h>
#include <vector>
#include<fstream>
using namespace std;
//Dynamic Programming Global Variables
std::vector<int> weight;
std::vector<int> profit;
int ** K = nullptr;
int Capacity;
std::vector<int> optimalItemsInBag;
int totItems;
//////////////////////////////////////

void Input(string , string);
int knapSack(int Capacity, int totItems, int ** K);
void computeOptimalSolution(int ** K);
int KSMemoazation(int n, int c);

// A utility function that will return the max of two integers
int max(int a, int b) {return (a > b)? a : b; }

//////////MEMOAZATION Global Variables/////////////////////
int ** arrMem = nullptr;
int result;

int main (int argc, char *argv[])
{

  if (argc != 3)
  {
    cout << "Invalid Input. Please Ensure Correct Format <Data.txt> <Capacity>";
    return -1;
  }
  Input(argv[1], "w");
  //Input(argv[2], "p");
  Capacity = atoi(argv[2]);
  totItems = weight.size();

  /*Initializing 2D array*/
  K = new int*[totItems+1];
  for(int row = 0; row < totItems+1; row++){
    K[row] = new int[Capacity+1];
  }
cout << "******************** DYNAMIC PROGRAMMING APPROACH ********************" << endl;
  cout << "Maximum profit is: " << knapSack(Capacity, totItems, K) << endl;
  computeOptimalSolution(K);
  cout << "The items in the bag are: " ;
  for(auto n : optimalItemsInBag)
  {
    cout <<"Item " <<  n << " ";
  }
  cout<< endl;
////////////MEMOAZATION//////////////////////////////////

arrMem = new int*[totItems+1];
for(int row = 0; row < totItems+1; row++)
{
    arrMem[row]= new int[Capacity+1];
}
for(int i = 0; i < totItems+1; i++)
{
  for(int j =0; j < Capacity+1; j++)
  {
    arrMem[i][j] = -1;
  }
}
weight.insert(weight.begin(), 0);
profit.insert(profit.begin(), 0);


cout << "******************** MEMOIZATION APPROACH ********************" << endl;
cout<< "Maximum profit is: " << KSMemoazation(totItems, Capacity) << endl;
  for(int row = 0; row < totItems+1; row++)
  {
    delete [] K[row];
    delete [] arrMem[row];
  }
  delete [] K;
  delete [] arrMem;
return 0;
}
/*
void Input(string file, string w_p)
{
  ifstream File;
  File.open(file);
  int n;
  while(File >> n){
    if(w_p == "w") weight.push_back(n);
    else profit.push_back(n);
  }
  File.close();
}*/
void Input(string file, string w_p)
{
  ifstream File;
  File.open(file);
  int n;
  while(File >> n){
   weight.push_back(n);
   if(File>>n)
    profit.push_back(n);
  }
  File.close();
}

/*
  O(nC)
*/
int knapSack(int Capacity, int totItems, int ** K){
  /*Building 2D Table in bottom up manner
    row = to the item
    col = to the current Capacity
  */
  for(int row = 0; row <= totItems; row++)
  {
    for(int col = 0; col <= Capacity; col++)
    {
      if(row == 0 || col == 0) K[row][col] = 0; //this will initialize the first row and col to zeros
      else if (weight[row-1] <= col) K[row][col] = max(profit[row-1] + K[row-1][col-weight[row-1]], K[row-1][col]); //this checks if the weight is at least equal to the capacity
      else K[row][col] = K[row-1][col]; //if the weight is higher than the current capacity just add the previous row to this index
    }
  }
  return K[totItems][Capacity];
}


/*
  Takes O(N) to compute
*/
void computeOptimalSolution(int ** K)
{
  int i = totItems;
  int c = Capacity;
  while(i > 0 and c > 0)
  {
    if(K[i][c] != K[i-1][c])
    {
        optimalItemsInBag.push_back(i);
        i-=1;
        c = c - weight[i];
    }
    else i = i-1;
  }
}

//////////MEMOAZATION//////////////
/*
  n is equal to the number of items left,
  c is equal to the capacity left
  run time is also O(nC)
*/
int KSMemoazation(int n, int c)
{
  if (arrMem[n][c] != -1) return arrMem[n][c];
  if (n == 0 || c == 0) result = 0; //base case
  else if (weight[n] > c) result = KSMemoazation(n-1,c);
  else
  {
    int temp1 = KSMemoazation(n-1, c);
    int temp2 = profit[n] + KSMemoazation(n-1, c - weight[n]);
    result = max(temp1, temp2);
  }
  arrMem[n][c]= result;
  return result;
}
