//
//  main.cpp
//  RandomPrograms
//
//  Created by Jason Rebello on 3/3/15.
//  Copyright (c) 2015 Jason Rebello. All rights reserved.
//
//  Practice Back Tracking, Divide and Conquer and Bit Manipulation

#include <iostream>
#include <assert.h>

using namespace std;

// ----------------------------- Back Tracking -----------------------------------------------------

#define M 4
void printSolution(int board[M])
{
    for(int i=0; i<M; i++)
        cout << board[i] << " ";
    cout << endl;
}

bool isSafe(int board[M], int k, int i)
{
    for(int j=0; j<=k-1; j++)
    {
        if((board[j] == i) || abs(board[j]-i)==abs(j-k))
            return false;
    }
    return true;
}

// k = row, i = column
// x[2] = 3 ; second row contains queen in 3rd column
// initially k =0
void nQueens(int board[M], int k)
{
    bool flag = false;
    for(int i=0; i<=M-1; i++)
    {
        if(isSafe(board,k,i))
        {
            board[k] = i;
            printSolution(board);
            if(k==M-1)
            {
                cout << "Tada" << endl;
                flag = true;
                printSolution(board);
                break;
            }
            else
                nQueens(board,k+1);
        }
    }
    if(flag==true)
        return;
}

// ---------------------------- **********
int N = 4;

void printMat(int sol[4][4])
{
    for(int i=0; i<N; i++)
    {
        for(int j=0;j<N;j++)
            cout << sol[i][j] << " ";
        cout << endl;
    }
}

bool isSafe1(int arr[4][4], int i, int j)
{
    if(i>=0 && i<N && j>=0 && j<N && arr[i][j] == 1)
        return true;
    return false;
}

bool findPath(int arr[4][4], int x, int y, int sol[4][4])
{
    //printMat(sol);
    if(x==N-1 && y==N-1)
    {
        sol[x][y] = 1;
        return true;
    }
    if(isSafe1(arr,x,y)==true)
    {
        sol[x][y] = 1;
        if(findPath(arr,x+1,y,sol))
            return true;
        if(findPath(arr,x,y+1,sol))
            return true;
        sol[x][y] = 0;
        return false;
    }
    return false;
}

/*
int N = 4;
#define UNASSIGNED 0;

bool findUnassignedLoc(int grid[N][N], int row, int col)
{
    for(row=0; row<N; row++)
        for(col=0; col<N; col++)
            if(grid[row][col] == 0)
            {
                return true;
            }
    return false;
}

bool usedInRow(int grid[N][N], int row, int num)
{
    for(int col=0; col<N; col++)
        if(grid[row][col] == num)
            return true;
    return false;
}

bool usedInCol(int grid[N][N], int col, int num)
{
    for(int row=0; row<N; row++)
        if(grid[row][col] == num)
            return true;
    return false;
}

bool usedInBox(int grid[N][N], int boxStartRow, int boxStartCol)
{
    for(int row=0; row)
}

bool solveSudoku(int grid[N][N])
{
    int row, col;
    if(!findUnassignedLoc(grid,row,col))
        return true;
    for(int num=1; num<=N; num++)
    {
        if(isSafe(grid,row,col,num))
        {
            grid[row][col] = num;
            if(solveSudoku(grid))
                return true;
            grid[row][col] = UNASSIGNED;
        }
    }
    return false;
}
*/
// ----------------------------- Divide and Conquer -----------------------------------------------------

// Find gcd of 2 numbers
int gcd(int x, int y)
{
    if(x==y)
        return x;
    else if(x<y)
        return gcd(x,y-x);
    else
        return gcd(x-y,y);
}

int gcd2(int x,int y)
{
    if(x%y == 0)
        return y;
    else
        return gcd(y,x%y);
}

/*
// CLosest Pair Pseudo Code O(nlogn)
function closest_pair(l,r)
{
    Find closest pair in P[l...r] sorted by x coordinate
    mid = (l+r)/2
    midx = P[mid].x
    dl = closest_pair(l,mid)
    dr = closesr_pair(mid+1,r)
    P[l .. mid] and P[mid+1 .. r] are now wrt the y coordinate
    delta = min(dl,dr)
    Ql = select_candidates(l,mid,delta,midx)
    Qr = select_candidates(mid+1,r,delta,midx)
    dm = delta_m(Ql,Qr,delta)
    use merge to make P[l..r] sorted by y-coordinate
    merge(l,mid,r)
}
*/

// Find peak in array which is monotonically increasing and then decreasing
int findPeak(int* arr, int low, int high)
{
    if(low < high)
    {
        int mid = (low+high)/2;
        if(arr[mid-1] < arr[mid] && arr[mid+1]<arr[mid])
            return mid;
        else if(arr[mid-1] < arr[mid] && arr[mid]<arr[mid+1])
            return findPeak(arr, mid+1, high);
        else if(arr[mid-1]>arr[mid] && arr[mid]>arr[mid+1])
            return findPeak(arr, low, mid-1);
        else
            return -1;
    }
    return -1;
}

// Get min and max element in array using divide and conquer
struct s
{
    int min,max;
};

s getMinMax(int* arr, int low, int high)
{
    s minmax, mml, mmr;
    int mid;
    if(low == high)
    {
        minmax.min = minmax.max = arr[low];
        return minmax;
    }
    else if(low == high-1)
    {
        if(arr[low] < arr[high])
        {
            minmax.max = arr[high];
            minmax.min = arr[low];
        }
        else
        {
            minmax.min = arr[low];
            minmax.max = arr[high];
        }
        return minmax;
    }
    else
    {
        mid = (low+high)/2;
        mml = getMinMax(arr, low, mid);
        mmr = getMinMax(arr, mid+1, high);
        if(mml.min < mmr.min)
            minmax.min = mml.min;
        else
            minmax.min = mmr.min;
        if(mml.max > mmr.max)
            minmax.max = mml.max;
        else
            minmax.max = mmr.max;
        return minmax;
    }
        
}

// Get kth smallest element in array

void displayArr(const int *a, const int n)
{
    cout << "Array contains" << endl;
    for(int i=0; i<n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int partitionArr(int* arr, int start, int end)
{
    /*
    int pivot = arr[start];
    int i = start;
    int j = end;
    do
    {
        do{i++;}while(arr[i] <= pivot);
        do{j--;}while(arr[j] >= pivot);
        if(i>j)swap(arr[i],arr[j]);
        displayArr(arr, 6);
    }while(i<=j);
    arr[start] = arr[j];
    arr[j] = pivot;
    return j;
     */
    int pivot = arr[end];
    int partitionIdx = start;
    for(int i=start; i<=end-1; i++)
    {
        if(arr[i] <= pivot)
        {
            swap(arr[i],arr[partitionIdx]);
            partitionIdx++;
        }
    }
    swap(arr[partitionIdx],arr[end]);
    displayArr(arr, 6);
    return partitionIdx;
}

int kthSmallest(int* arr, int k, int start, int end)
{
    int partitionIdx=0;
    int sizeArr = end;
    do
    {
        partitionIdx = partitionArr(arr, start, end);
        if(k==partitionIdx+1)
            return arr[partitionIdx];
        else if(k<(partitionIdx+1))
            end = partitionIdx-1;
        else if(k>(partitionIdx+1))
            start = partitionIdx+1;
    }while(true);
}

// --------------------------------------- Bit Manipulation ---------------------------------------------
// Set, clear, toggle bit
void sct(int x, int bit, char choice)
{
    int mask;
    switch(choice)
    {
        case 's':
            mask = 1 << (bit-1);
            x = x | mask;
            break;
            
        case 'c':
            mask = ~(1 << (bit-1));
            x = x & mask;
            break;
            
        case 't':
            mask = (1 << (bit-1));
            x = x ^ mask;
            break;
    }
    
}

// Check if number is a power of 2
void pow2(int x)
{
    cout << x << " is a power of 2? : " << (x&&!(x&(x-1))) << endl;
}

// Compute Integer absolute value without branching
void absolute(int x)
{
    int mask = x>>7;
    cout << "Absolute value : " << ((x+mask)^mask) << endl;
}

// Find min and max of 2 integers without branching
void minMax(int x, int y)
{
    cout << "Max of 2 integers is : " << (x ^ ((x^y)& -(x<y))) << endl;
    cout << "Min of 2 integers is : " << (y ^ ((x^y)& -(x<y))) << endl;
}

// Determine if 2 integers are of opposite signs
void oppositeSigns(int x, int y)
{
    cout << "Opposite signs ? : " << ((x^y)<0) << endl;
}

// --------------------------------------------------------------------------------------------------------

int main(int argc, const char * argv[]) {
    
    // ---------------------- Bit Manipulation ---------------------------------------------

    oppositeSigns(0,-3);
    cout << endl;
    
    minMax(5,17);
    cout << endl;
    
    absolute(2);
    cout << endl;
    
    pow2(0);
    cout << endl;
    
    sct(10,2,'s');
    
    // ---------------------- Divide and Conquer ---------------------------------------------
    int arr1[] = {4,8,2,10,9,3};
    int k = 2;
    int sizeArr = sizeof(arr1)/sizeof(arr1[0]);
    assert(k> 0 && k<=sizeArr);
    cout << sizeArr << endl;
    cout << k << " Smallest element in " << endl;
    displayArr(arr1,sizeArr) ;
    cout << " is " << kthSmallest(arr1, k, 0, sizeArr-1) << endl;
    
    int arr[] = {1000, 11, 445, 1, 330, 3000};
    int arr_size = 6;
    s minmax = getMinMax(arr, 0, arr_size-1);
    cout << "\nMinimum element is " << minmax.min;
    cout << "\nManimum element is " << minmax.max << endl;
    
    int arr2[] = {10,13,14,20,19,13,12,11,10,9,8};
    int arr2Size = sizeof(arr2)/sizeof(arr2[0]);
    int peak = findPeak(arr2, 0, arr2Size-1);
    if(peak != -1)
        cout << "Peak is " << arr2[peak] << " and is located at " << peak+1 << endl << endl;
    
    int x=6,y=36;
    cout << "GCD of " << x << " " << y << " is " << gcd(x, y) << endl;
    
    // ---------------------- Back Tracking ---------------------------------------------
    int arr3[][4] = {{1,1,0,0},
                     {1,1,0,0},
                     {0,1,1,0},
                     {1,0,1,1}};
    int sol[4][4] = {0};
    cout << "Given mat" << endl;
    printMat(arr3);
    cout << "Path found" << endl;
    if(findPath(arr3, 0, 0, sol))
        printMat(sol);
    else
        cout << "is not found" << endl;
    
    // N Queens problem
    cout << "\nN queens Problem" << endl;
    int board[4] = {0};
    nQueens(board, 0);
    return 0;
}
