#include <iostream>
#include <stdio.h>
#include <vector>
#include<fstream>
using namespace std;
using namespace std::chrono;
//Dynamic Programming Global Variables
std::vector<int> weight;
std::vector<int> profit;
int ** K = nullptr;
int Capacity;
std::vector<int> optimalItemsInBag;
int totItems;
//////////////////////////////////////
void Input(string);
int knapSackDynamic(int Capacity, int totItems);
void itemsInBag();
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
  Input(argv[1]);
  //Input(argv[2], "p");
  Capacity = atoi(argv[2]);
  totItems = weight.size();

  /*Initializing 2D array*/
  K = new int*[totItems+1];
  for(int row = 0; row < totItems+1; row++){
    K[row] = new int[Capacity+1];
  }
cout << "******************** DYNAMIC PROGRAMMING APPROACH ********************" << endl;
  cout << "Capacity: " << Capacity << endl;;
  auto start = high_resolution_clock::now();
  cout << "Maximum profit is: " << knapSackDynamic(Capacity, totItems) << endl;
  auto stop = high_resolution_clock::now();
  auto runtime = duration_cast<microseconds>(stop - start);

  cout << "Time: " << runtime.count() << "ms" << endl;

  itemsInBag();
  cout << "The items in the bag are: " ;
  for(auto n : optimalItemsInBag){
    cout <<"Item " <<  n << " ";
  }
  cout<< endl;
/*
  for(int i = 0; i < totItems+1; i++){
    for(int j =0; j < Capacity+1; j++){
      cout<< K[i][j] << " ";
    }
    cout<< endl;
  }*/
//////////////////////////////////MEMOAZATION//////////////////////////////////
/*Initializing 2D array*/
arrMem = new int*[totItems+1];
for(int row = 0; row < totItems+1; row++){
    arrMem[row]= new int[Capacity+1];
}
for(int i = 0; i < totItems+1; i++){
  for(int j =0; j < Capacity+1; j++){
    arrMem[i][j] = -1;
  }
}
weight.insert(weight.begin(), 0);
profit.insert(profit.begin(), 0);

cout << "******************** MEMOIZATION APPROACH ********************" << endl;
cout << "Capacity: " << Capacity << endl;;
auto start2 = high_resolution_clock::now();
cout << "Maximum profit is: " << KSMemoazation(totItems, Capacity) << endl;
auto stop2 = high_resolution_clock::now();
auto runtime2 = duration_cast<microseconds>(stop2 - start2);

cout << "Time: " << runtime2.count() << "ms" << endl;
/*
for(int i = 0; i < totItems+1; i++){
  for(int j =0; j < Capacity+1; j++){
    cout<< arrMem[i][j] << " ";
  }
  cout<< endl;
}
*/
//Deleting arrays to avoid memory leaks
  for(int row = 0; row < totItems+1; row++){
    delete [] K[row];
    delete [] arrMem[row];
  }
  delete [] K;
  delete [] arrMem;
return 0;
}

void Input(string file)
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

/**
  O(nC)
  solves all subproblems(repetition)
  where n is number of items and c is the capacity
  c is not a function of the number of items
  this is only good when C is relatively small in terms of n (i.e polynomial function of n rather than an exponential one)
*/
int knapSackDynamic(int Capacity, int totItems){
  /*Building 2D Table in bottom up manner
    row refers to the item
    col refers to the current Capacity
  */
  for(int row = 0; row <= totItems; row++)
  {
    for(int col = 0; col <= Capacity; col++)
    {
      //this will initialize the first row and col to zeros
      if(row == 0 || col == 0) K[row][col] = 0;
      //this checks if the weight at i is at least equal to or less than the capacity of i
      else if (weight[row-1] <= col) K[row][col] = max(profit[row-1] + K[row-1][col-weight[row-1]], K[row-1][col]);
      //if the weight at i is higher than the current capacity just add the previous row to this index
      else K[row][col] = K[row-1][col];
    }
  }
  //max profit will be stored here
  return K[totItems][Capacity];
}


/*
  Takes O(N) to compute
*/
void itemsInBag()
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
  top down
  n is equal to the number of items left,
  c is equal to the capacity left
  run time is O(nC)
  since it wont repeat problems more than twice that we have solved due to memoazation
  if every problem has to be solved once then it is not much different than dynamic programming
*/
int KSMemoazation(int n, int c)
{
  if (arrMem[n][c] != -1) return arrMem[n][c];
  if (n == 0 || c == 0) result = 0; //base case
  else if (weight[n] > c) result = KSMemoazation(n-1,c);
  else
  {
    //no
    int temp1 = KSMemoazation(n-1, c);
    //yes
    int temp2 = profit[n] + KSMemoazation(n-1, c - weight[n]);
    result = max(temp1, temp2);
  }
  arrMem[n][c]= result;
  return result;
}
