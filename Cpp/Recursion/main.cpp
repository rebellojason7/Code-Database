//
//  main.cpp
//  Recursion
//
//  Created by Jason Rebello on 3/8/15.
//  Copyright (c) 2015 Jason Rebello. All rights reserved.
//
//  Some Practice Recursion Problems

#include <iostream>
#include <string>

using namespace std;

void printArr(int* arr, int n)
{
    for(int i=0; i<n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Print all possible strings of length k that can be formed form a set of n characters
void StringCombination(char* set, string prefix, int n, int k)
{
    if(k==0)
    {
        cout << prefix << endl;
        return;
    }
    for(int i=0; i<n;i++)
    {
        string newPrefix = prefix + set[i];
        StringCombination(set, newPrefix, n, k-1);
    }
}

// 19) Print all possible combinations of r elements in a given array of size n
void combinations(int arr[], int data[], int start, int end, int index, int r)
{
    // Current combination is ready to be printed, print it
    if (index == r)
    {
        printArr(data, r);
        return;
    }
    
    // replace index with all possible elements. The condition
    // "end-i+1 >= r-index" makes sure that including one element
    // at index will make a combination with remaining elements
    // at remaining positions
    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinations(arr, data, i+1, end, index+1, r);
    }
}

// 17) Check if number is a palindrome
bool isPalidrome(int num, int* dupNum)
{
    if(num/10==0)
        return (num==(*dupNum)%10);
    if(!isPalidrome(num/10,dupNum))
        return false;
    *dupNum /= 10;
    return (num%10 == (*dupNum)%10);
}

// 16) print all increasing sequences containing k out of n numbers

void printSeq(int*arr, int k, int n, int& len)
{
    if(len==k)
    {
        printArr(arr,k);
        return;
    }
    
    int i=(len==0)?1:arr[len-1]+1;
    len++;
    
    while(i<=n)
    {
        arr[len-1] = i;
        printSeq(arr, k, n, len);
        i++;
    }
    len--;
    
}

// 15) Calculates a^b
int fun1(int a, int b)
{
    if (b == 0)
        return 1;
    if (b % 2 == 0)
        return fun1(a*a, b/2);
    
    return fun1(a*a, b/2)*a;
}

// 14) Multiplication of 2 numbers
int fun(int a, int b)
{
    if (b == 0)
        return 0;
    if (b % 2 == 0)
        return fun(a+a, b/2);
    
    return fun(a+a, b/2) + a;
}

// 13) Print *
void fun1(int n)
{
    int i = 0;
    if (n > 1)
        fun1(n-1);
    for (i = 0; i < n; i++)
        cout << " * ";
}

// 12) Print Binary equivalent of number. Assume n>=0
void binaryEquivalent(int n)
{
    if(n==1)
        return;
    else
    {
        binaryEquivalent(n/2);
        cout << n%2;
    }
}

// 11) Return floor or log(n) of a number. Assume n >= 1
int floorLogN(int n)
{
    if(n==1)
        return 0;
    else
        return 1+floorLogN(n/2);
}

// 10) Selection sort with recursion
int findMinIndex(int* arr, int start, int end)
{
    int index = start;
    
    for(int i = start; i <= end; i++)
    {
        if(arr[i] < arr[index])
            index = i;
    }
    
    return index;
}

void recursiveSS(int* arr, int start, int end)
{
    if(start>=end)
        return;
    int minIndex,temp;
    minIndex = findMinIndex(arr,start,end);
    swap(arr[start],arr[minIndex]);
    recursiveSS(arr,start+1,end);
}

// 9) Magic index
int distinctMagic(int* arr, int size, int start, int end)
{
    if(start < 0 || end >= size || end<start)
        return -1;
    int mid = (start+end)/2;
    if(mid == arr[mid])
        return mid;
    else if(arr[mid]<mid)
        return distinctMagic(arr, size, mid+1, end);
    else
        return distinctMagic(arr, size , start, mid-1);
}


int notDistinctMagic(int* arr, int size, int start, int end)
{
    if(start<0 || end>=size || end<start)
        return -1;
    int midIndex = start+(end-start)/2;
    int midValue = arr[midIndex];
    if(midValue==midIndex)
        return midIndex;
    int leftIndex = min(midIndex-1,midValue);
    int left = notDistinctMagic(arr, size, start, leftIndex);
    if(left>=0)
        return left;
    int rightIndex = max(midValue,midIndex+1);
    int right = notDistinctMagic(arr, size, rightIndex, end);
    return right;
}

/*
// 8) Child can jump either 1,2 or 3 steps. List possible ways of reaching n steps
int m[30];
int countWays(int n, int* m)
{
    if(n<0)
        return 0;
    if(n==0)
        return 1;
    if(m[n] > -1)
        return m[n];
    else
    {
        m[n] = countWays(n-1,m) + countWays(n-2, m) + countWays(n-3, m);
        return m[n];
    }
}
 */

// 7) Towers of hanoi problem (2^n)-1 steps
void hanoi(int n, string source, string destination, string buffer)
{
    if(n==1)
        cout << "Move disc " << n << " from " << source << " to " << destination << endl;
    else
    {
        hanoi(n-1,source,buffer,destination);
        cout << "Move disc " << n << " from " << source << " to " << destination << endl;
        hanoi(n-1,buffer,destination,source);
    }
}

// 6) Sum of digits
int sumOfDigits(int n)
{
    if(n/10==0)
        return n;
    else
        return n%10 + sumOfDigits(n/10);
}

// 5) Print array using recursion
int size = 5;

void printRev(int* arr, int n)
{
    if(n==0)
        return;
    else
    {
        printRev(arr,n-1);
        cout << arr[size-n] << " ";
    }
}

void printArray(int* arr, int n)
{
    if(n==0)
        return;
    else
    {
        cout << arr[size-n] << " ";
        printArray(arr, n-1);
    }
}

// 4) Modular Exponent x^n mod M
// (axb)%M = {(a%M)x(b%M)}%M O(logn)
int mod(int x, int n, int M)
{
    if(n==0)
        return 1;
    if(n%2==0)
    {
        int y = mod(x,n/2,M);
        return (y*y)%M;
    }
    else
        return ((x%M)*mod(x,n-1,M))%M;
}

// 3) Power of a number O(logn)
int pow(int x,int n)
{
    if(n==0)
        return 1;
    else if(n%2==0)
    {
        int y = pow(x,n/2);
        return y*y;
    }
    else
        return x*pow(x,n-1);
}

// 2) Recursion with memorization
int F[51];
int Fib(int n)
{
    if(n<=1)
        return n;
    if(F[n] != -1)
        return F[n];
    F[n] = Fib(n-1) + Fib(n-2);
    return F[n];
}

// 1) Factorial of a number O(n)
int fact(int n)
{
    if(n==0)
        return 1;
    else
        return n*fact(n-1);
}

int main(int argc, const char * argv[]) {
    
    // Factorial of a number
    int n = 3;
    cout << "Facotrial of " << n << " is " << fact(n) << endl << endl;
    
    // Ficppbonacci series
    for(int i=0; i<51; i++)
        F[i] = -1;
    n = 40;
    cout << "Fibonacci number of " << n << " is " << Fib(n);
    cout << endl << endl;
    
    // Power of a number
    int x = 5;
    n = 4;
    cout << "Power is " << pow(x,n) << endl << endl;
    
    // Print array using recursion
    int arr[] = {1,3,5,7,9};
    cout << "Array is ";
    printArray(arr,size);
    cout << endl;
    printRev(arr,size);
    cout << endl << endl;
    
    // Sum of digits
    n = 12345;
    cout << "Sum of digits of " << n << " is " << sumOfDigits(n) << endl << endl;
    
    // Towers of hanoi
    n = 3;
    cout << "Solving towers of hanoi" << endl;
    hanoi(n,"source", "destination", "buffer");
    cout << endl;
    
    // Child running up stairs
    /*
    for(int i=0; i<30; i++)
        m[i] = -1;
    n = 4;
    cout << "\nNumber of ways to move up " << n << " steps is " << countWays(n, m) << endl << endl;
     */
    
    // Magic Index
    int arr2[] = {-40,-20,-1,1,2,3,6,8,9,12,13};
    cout << "Magic index at " << distinctMagic(arr2, 11, 0, 10) << endl << endl;
    
    int arr3[] = {-10,-5,2,2,2,3,4,7,9,12,13};
    cout << "Magic index at " << notDistinctMagic(arr3,11,0,10);
    
    // Selection sort via recursion
    int arr4[] = {4,6,1,2,7};
    cout << "Original array " << endl;
    printArray(arr4, 5);
    cout << endl;
    cout << "Sorted Array " << endl;
    recursiveSS(arr4, 0, 4);
    printArray(arr4, 5);
    cout << endl << endl;
    
    // Multiplication of 2 numbers
    fun(4,3);
    
    // Print increasing sequence
    int k=3,len=0;
    n=4;
    int arr5[k];
    printSeq(arr5,k,n,len);
    cout << endl << endl;
    
    // Check if number is a palindrome
    int num=12;
    int* dupNum = new int(num);
    cout << "Is " << num << " a palindrome ? " << isPalidrome(num, dupNum) << endl << endl;
    
    // Print all r combinations of n elements
    int arr6[] = {1,2,3,4,5};
    int r = 3;
    n = sizeof(arr6)/sizeof(arr6[0]);
    int data[r];
    combinations(arr6, data, 0, n-1, 0, r);
    cout << endl ;
    
    // Print all combinations of string
    char set[] = {'a','b'};
    k = 3;
    StringCombination(set, "", 2, 2);
    return 0;
}
