//
//  main.cpp
//  Sorting Algorithms and Searching Algorithms
//
//  Created by Jason Rebello on 8/23/14.
//  Copyright (c) 2014 Jason Rebello. All rights reserved.
//

#include <iostream>
#include <stdlib.h>

using namespace std;

// ****************************************************************************
void displayArr(const int *a, const int n)
{
    cout << "Array contains" << endl;
    for(int i=0; i<n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

// ****************************************************************************

/*                  Quick Sort
 Best: O(nlogn)
 Avg:  O(nlogn)
 Worse:O(n^2)
 Stable: Not stable
 Space: O(1)
 Method: Recusive
 */

///*
int partition(int *arr, int start, int end)
{
    int t = start + rand() % (end-start+1);
    swap(arr[t],arr[end]);
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
    return partitionIdx;
}

void quickSort(int* arr, int start, int end)
{
    if(start<end)
    {
        int partitionIdx = partition(arr,start,end);
        quickSort(arr, start, partitionIdx-1);
        quickSort(arr, partitionIdx+1, end);
    }
}
//*/

/*
int random_partition(int* arr, int start, int end)
{
    int pivotIdx = start + rand() % (end-start+1);
    int pivot = arr[pivotIdx];
    swap(arr[pivotIdx], arr[end]); // move pivot element to the end
    pivotIdx = end;
    int i = start-1;
    
    for(int j=start; j<=end-1; j++)
    {
        if(arr[j] <= pivot)
        {
            i = i+1;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i+1], arr[pivotIdx]);
    return i+1;
}

void quickSort(int* arr, int start, int end)
{
    if(start < end) {
        int mid = random_partition(arr, start, end);
        quickSort(arr, start, mid-1);
        quickSort(arr, mid+1, end);
    }
}
*/

// ****************************************************************************

/*                  Shell Sort
 Best: O()
 Avg:  O()
 Worse:O()
 Stable:
 Space:
 Method: Exchange
 */
void shellSort(int* arr, const int n)
{
    int i,j,temp,gap;
    
    for(gap=n/2; gap>=1; gap /= 2){
        for(i=gap; i<=n-1; i++){
            temp=arr[i];
            for(j=i; j>=gap; j-=gap){
                if(temp < arr[j-gap])
                    swap(arr[j],arr[j-gap]);
                else
                    break;
            }
        }
    }
}


// ****************************************************************************

/*                      Merge Sort
 Best: O(nlogn)
 Avg:  O(nlogn)
 Worse:O(nlogn)
 Stable: yes
 Space: n
 */

void Merge(int* arr, int* L, int leftCount, int* R, int rightCount)
{
    int i,j,k;
    i=j=k=0;
    while(i<=leftCount-1 && j<= rightCount-1)
    {
        if(L[i] < R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while(i<=leftCount-1)
        arr[k++] = L[i++];
    while (j<=rightCount-1)
        arr[k++] = R[j++];
}

void mergeSort(int* arr, const int n)
{
    if(n<=1)
        return;
    int mid = n/2;
    int* L = new int[mid];
    int* R = new int[n-mid];
    for(int i=0; i<=mid-1; i++)
        L[i] = arr[i];
    for(int i=mid; i<=n-1; i++)
        R[i-mid] = arr[i];
    mergeSort(L, mid);
    mergeSort(R, n-mid);
    Merge(arr,L,mid,R,n-mid);
}

// ****************************************************************************

/*                  Selection Sort
 Best: O(n^2)
 Avg:  O(n^2)
 Worse:O(n^2)
 Stable: yes
 Space: O(1)
 Method: Exchange
 */
void selectionSort(int* arr, const int n)
{
    for(int i=0; i<=n-2; i++)
    {
        int iSmallest = i;
        for(int j=i+1; j<=n-1; j++)
        {
            if(arr[iSmallest] > arr[j])
                iSmallest = j;
        }
        swap(arr[i],arr[iSmallest]);
    }
}

// ****************************************************************************

/*                  Insertion Sort
 Best: O(n)
 Avg:  O(n^2)
 Worse:O(n^2)
 Stable: yes
 Space: O(1)
 Method: Exchange
 */
void insertionSort(int* arr, const int n)
{
    for(int i=1; i<=n-1;i++)
    {
        int j=i;
        while(j>=1 && arr[j] < arr[j-1])
        {
            swap(arr[j],arr[j-1]);
            j--;
        }
    }
}

// ****************************************************************************

/*                      Bubble Sort
 Best: O(n)
 Avg:  O(n^2)
 Worse:O(n^2)
 Stable: yes
 Space: O(1)
 Method: Exchange
 */
void bubbleSort(int *arr,const int n)
{
    int flag = 0;
    for(int i=n-1; i>=1; i--)
    {
        flag = 0;
        for(int j=0; j<=i-1 ;j++)
        {
            if(arr[j] > arr[j+1])
            {
                flag = 1;
                swap(arr[j],arr[j+1]);
            }
        }
        if(flag == 0)
            break;
    }
}

// ****************************************************************************

/*                  Binary Search
 Best: O()
 Avg:  O()
 Worse:O()
 Stable:
 Space:
 Method: Exchange
 */
void binarySearch(int* arr, const int n, const int num)
{
    cout << endl << "Binary Search" << endl;
    cout << "Searching for " << num << endl;
    mergeSort(arr, n);
    displayArr(arr, n);
    int low=0,high=n,idx;
    while(low+1 < high)
    {
        idx = (low+high) >> 1;
        if(arr[idx]>num)
            high = idx;
        else
            low = idx;
    }
    if(arr[low] == num)
        cout << "Number found at: " << low+1 << endl;
    else
        cout << "Could not find the number" << endl;
}

//O(logn)
int BinarySearch(int* arr, const int n, const int num, bool searchFirst)
{
    cout << endl << "Inside alternate BS" << endl;
    mergeSort(arr, n);
    displayArr(arr, n);
    int low = 0;
    int high = n-1;
    int result = -1; // this is used if we want to find the minimum occurence or max occurence of the element
    while(low<=high)
    {
        int mid = low + (high-low)/2; // avoids overflow
        if(num == arr[mid])
        {
            //return mid; // finds any occurence
            
            //Find min occurence
            if(searchFirst)
            {
                result = mid;
                high = mid-1;
            }
            
            //Find max occurence
            else
            {
                result = mid;
                low = mid+1;
            }
        }
        else if(num < arr[mid])
            high = mid-1;
        else
            low = mid+1;
    }
    return result;
}

// Binary Search with recursion
int binarySearchRecursive(int* arr,int low, int high, int num)
{
    if(low>high)
        return -1;
    else
    {
        int mid = low + (high-low)/2;
        if(arr[mid] == num)
            return mid;
        else if(num<arr[mid])
            binarySearchRecursive(arr, low, mid-1, num);
        else
            binarySearchRecursive(arr, mid+1, high, num);
    }
}

// ****************************************************************************

//                 Find Rotation Count
int findRotationCount(int* arr, int n)
{
    cout << endl << "Rotation Count" << endl;
    displayArr(arr, n);
    int low = 0, high=n-1;
    while(low<=high)
    {
        if(arr[low] <= arr[high])
            return low;
        int mid = low + (high-low)/2;
        int next = (mid+1)%n;
        int prev = (mid-1+n)%n;
        if(arr[mid]<=arr[prev] && arr[mid]<=arr[next])
            return mid;
        else if(arr[mid]>=low)
            low = mid+1;
        else if(arr[mid]<=high)
            high = mid-1;
    }
    return -1;
}

// ****************************************************************************

//              Search element in circular sorted array
int searchCircularSorted(int* arr, int n, int num)
{
    int low=0, high=n-1;
    while(low <= high)
    {
        int mid = low + (high-low)/2;
        if(arr[mid] == num)
            return mid;
        else if(arr[mid] <= arr[high])
        {
            if(num>arr[mid] && num<=arr[high])
                low = mid+1;
            else
                high = mid-1;
        }
        else //(arr[low] <= arr[mid])
        {
            if(num >= arr[low] && num<arr[mid])
                high = mid-1;
            else
                low = mid+1;
        }
    }
    return -1;
}

// ****************************************************************************

//              Print Spiral
void printSpiral(int arr[4][4],int m,int n)
{
    int T=0,B=m-1,L=0,R=n-1,dir=0;
    while(T<=B && L<=R)
    {
        if(dir==0)
        {
            for(int K=L; K<=R; K++)
                cout << arr[T][K] << " ";
            T++;
            cout << endl;
        }
        else if(dir==1)
        {
            for(int K=T; K<=B; K++)
                cout << arr[K][R] << " ";
            R--;
            cout << endl;
        }
        else if(dir==2)
        {
            for(int K=R; K>=L; K--)
                cout << arr[B][K] << " ";
            B--;
            cout << endl;
        }
        else if(dir==3)
        {
            for(int K=B; K>=T; K--)
                cout << arr[K][L] << " ";
            L++;
            cout << endl;
        }
        dir = (dir+1)%4;
    }
}

// ****************************************************************************

/*                  Linear Search
 Best: O(1)
 Avg:  O(n)
 Worse:O(n)
 Stable:
 Space:
 Method: Exchange
 */
void linearSearch(int* arr, const int n, const int num)
{
    bool flag=0;
    cout << endl << "Linear Search" << endl;
    cout << "Searching for " << num << endl;
    for(int i=0; i<=n-1; i++)
        if(arr[i] == num)
        {
            cout << "number found at: " << i+1 << endl;
            flag = 1;
            break;
        }
    if(flag == 0)
        cout << "Could not find the number" << endl;
}


// ****************************************************************************
int main(int argc, const char * argv[])
{
    int arr[] = {4,5,6,2,3,1,8,4,9,7};
    const int n = sizeof(arr)/sizeof(arr[0]);
    displayArr(arr,n);
    ///*
    // 1 Bubble
    int arr1[] = {4,5,6,2,3,1,8,4,9,7};
    bubbleSort(arr1,n);
    cout << endl;
    cout << "Bubble Sort" << endl;
    displayArr(arr1,n);
    
    // 2 Insertion
    int arr2[] = {4,5,6,2,3,1,8,4,9,7};
    insertionSort(arr2,n);
    cout << endl;
    cout << "Insertion Sort" << endl;
    displayArr(arr2,n);
    
    // 3 Selection
    int arr3[] = {4,5,6,2,3,1,8,4,9,7};
    selectionSort(arr3,n);
    cout << endl;
    cout << "Selection Sort" << endl;
    displayArr(arr3,n);
    
    // 4 Merge
    int arr4[] = {4,5,6,5,3,1,8,4,9,7};
    mergeSort(arr4,n);
    cout << endl;
    cout << "Merge Sort" << endl;
    displayArr(arr4,n);
    //*/
    // 5 Shell
    int arr5[] = {10,9,8,7,5,5,4,3,2,1};
    shellSort(arr5,n);
    cout << endl;
    cout << "Shell Sort" << endl;
    displayArr(arr5,n);
    
    // 6 Quick
    int arr6[] = {100,103,14,7,19,23,32,5,19,200};
    int start = 0,end = n-1;
    quickSort(arr6,start,end);
    cout << endl;
    cout << "Quick Sort" << endl;
    displayArr(arr6,n);
    
    // 1 Linear Search
    int arr7[] = {10,9,8,7,5,5,4,3,2,1};
    linearSearch(arr7, n, 5);
    
    // 2 Binary Search
    int arr8[] = {14,25,67,23,25,9,1,100,83,91};
    binarySearch(arr8, n, 100);
    
    cout << endl << "Alternate binary search" << endl;
    int arr9[] = {14,25,17,23,23,9,23,100,83,91};
    int idx;
    idx = BinarySearch(arr9, n, 23,true);
    if(idx == -1)
        cout << "number could not be found" << endl;
    else
        cout << "number found at: " << idx+1 << endl;
    
    // Find count of number using binary search
    int arr10[] = {14,25,17,23,23,9,23,100,83,91};
    int num = 91;
    int firstIndex = BinarySearch(arr10, n, num, true);
    if(firstIndex == -1)
        cout << "Count is 0 " << endl;
    else
    {
        int lastIndex = BinarySearch(arr10, n, num, false);
        cout << "Count is " << lastIndex-firstIndex+1 << endl;
    }
    
    // Find Rotation Count
    //int arr11[] = {23,34,56,67,1,4,5,9,10,17};
    int arr11[] = {1,2,3,4,5,6,7,8,9,10};
    int Index = findRotationCount(arr11,n);
    if(Index == -1)
        cout << "Invalid " << endl;
    else
    {
        cout << "Rotation Count is " << Index << endl;
    }
    
    // Find Circular Sorted
    cout << endl << "find circular sorted" << endl;
    int arr12[] = {23,34,56,67,1,4,5,9,10,17};
    int Idx = searchCircularSorted(arr12, n, 67);
    if(Idx == -1)
        cout << "Could not find element " << endl;
    else
    {
        cout << "Found at location " << Idx+1 << endl;
    }
    
    // Print Spiral
    cout << endl << "find circular sorted" << endl;
    int arr13[4][4] = {{23,34,56,67},{1,4,5,9},{10,17,7,9},{13,14,76,100}};
    printSpiral(arr13,4,4);
    
}

