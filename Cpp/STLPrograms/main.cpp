//
//  main.cpp
//  STLPrograms
//
//  Created by Jason Rebello on 3/3/15.
//  Copyright (c) 2015 Jason Rebello. All rights reserved.
//
//  Practice using STL

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>

using namespace std;

// Print functions ----------------------------------------------------------------------------------------

void printset(set<int> s)
{
    set<int>::iterator it;
    for(it=s.begin(); it!=s.end();it++)
        cout << *it << " ";
    cout << endl;
}

void printvec(vector<int> v)
{
    vector<int>::iterator it;
    for(it=v.begin(); it!=v.end();it++)
        cout << *it << " ";
    cout << endl;
}

void printList(list<int> l)
{
    list<int>::iterator j;
    for(j=l.begin(); j!=l.end(); j++)
        cout << *j << " ";
}

// Main Program ----------------------------------------------------------------------------------------

int main(int argc, const char * argv[]) {
    
    // List -----------------------------
    cout << "List ---------------------------------------" << endl;
    list<int> l;
    l.push_back(1);
    l.push_front(0);
    l.insert(l.begin(),2);
    l.insert(++++l.begin(),6);
    list<int>::iterator i, itr1,itr2;
    for(i=l.begin(); i!=l.end(); i++)
        cout << *i << " ";
    cout << endl;
    itr1 = itr2 = l.begin();
    advance(itr1,2);
    cout << *itr1 << endl;
    itr1 = l.erase(itr1);
    cout << *itr1 << endl;
    
    list<int> newlist;
    for(int i=1; i<=9; i++)
        newlist.push_back(10*i);
    printList(newlist);
    list<int>::iterator it1=newlist.begin(), it2=newlist.begin();
    it1++;
    advance(it2,5);
    newlist.erase(it1,it2);
    cout << endl;
    printList(newlist);
    itr1 = newlist.begin();
    itr1++;
    newlist.insert(itr1, 2,7);
    cout << endl;
    printList(newlist);
    cout << "-------------------------------------------------" << endl;
    
    // Vector ----------------------------------------
    cout << "Vector ---------------------------------------" << endl;
    vector<int> vec;
    if(vec.empty())
        cout << "The vector is empty" << endl;
    for(int i=0; i<9; i++)
        vec.push_back(10*i);
    cout << endl;
    printvec(vec);
    cout << "size " << vec.size() << endl;
    cout << "capacity " << vec.capacity() << endl;
    //cout << "vec at " << vec.at(100) << endl;
    vector<int>::iterator it=vec.begin(),itr;
    vec.erase(it);
    printvec(vec);
    vec.erase(vec.begin(),vec.begin()+3);
    printvec(vec);
    vec.clear();
    cout << "-------------------------------------------------" << endl;
    
    // Set ----------------------------------------
    cout << "Set ---------------------------------------" << endl;
    set<int> myset;
    set<int>::iterator setit;
    pair<set<int>::iterator,bool> ret;
    for(int i=1; i<=9; i++)
        myset.insert(10*i);
    printset(myset);
    ret = myset.insert(35);
    if(ret.second==true)
        setit = ret.first;
    int setarr[] = {7,8,9};
    myset.insert(setarr,setarr+3); // inserts a garbage value if it is +4 (out of range)
    printset(myset);
    setit = myset.find(10);
    myset.erase(setit);
    printset(myset);
    cout << "-------------------------------------------------" << endl;
    
    // Map ----------------------------------------
    cout << "Map ---------------------------------------" << endl;
    map<string,int> person;
    person["jason"] = 27;
    person.insert(pair<string,int>("ryan",22));
    person.insert(map<string,int>::value_type("colin",56));
    person.insert(make_pair(string("roselyn"), 58));
    cout << "Size " << person.size() << endl;
    for(map<string,int>::iterator it=person.begin(); it!= person.end(); it++)
    {
        cout << (*it).first << " : " << it->second << endl;
    }
    map<string,int>::iterator mapit;
    mapit = person.find("jason");
    cout << mapit->second << endl;
    cout << "-------------------------------------------------" << endl;
    return 0;
}
