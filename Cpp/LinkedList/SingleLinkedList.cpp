#include "SinglyLinkedList.h"
#include <iostream>
#include <stack>

using namespace std;

// Constructor -----------------------------------------------------------------------------------------
SLL::SLL()
{
    head = NULL;
    curr = NULL;
    temp = NULL;
}


// Adds a node at the end of the list ------------------------------------------------------------------
void SLL::addNode(int addData)
{
    length++;
    nodePtr n = new node;
    n->next = NULL;
    n->data = addData;
    
    if(head != NULL)
    {
        curr = head;
        while(curr->next != NULL)
            curr = curr->next;
        curr->next = n;
    }
    else
    {
        head = n;
    }
}

// Adds a node at the position specified ------------------------------------------------------------------
void SLL::addNodeAt(int addData, int pos)
{
    if(pos>(length+1) || pos<1)
        cout << "Cant add data " << addData << ". There are " << length << " nodes in the list" << endl;
    else
    {
        length++;
        nodePtr n = new node;
        n->data = addData;
        n->next = NULL;
        if(pos == 1)
        {
            n->next = head;
            head = n;
        }
        else
        {
            curr = head;
            for(int count=1; count<pos-1; count++)
                curr = curr->next;
            n->next = curr->next;
            curr->next = n;
        }
    }
}

// Add node in sorted order (increasing) ------------------------------------------------------------------
void SLL::addNodeSorted(int addData)
{
    length++;
    nodePtr n = new node;
    n->data = addData;
    n->next = NULL;
    if(head==NULL)
    {
        head = n;
    }
    else
    {
        if(addData < head->data)
        {
            n->next = head;
            head = n;
        }
        else
        {
            curr = head;
            while(curr->next!=NULL && curr->next->data < addData)
                curr = curr->next;
            n->next = curr->next;
            curr->next = n;
        }
    }
}

// Delete node -----------------------------------------------------------------------------------------
void SLL::delNode(int delData)
{
    nodePtr delPtr = NULL;
    curr = head;
    temp = head;
    while(curr != NULL && curr->data!= delData)
    {
        temp = curr;
        curr = curr->next;
    }
    if(curr == NULL)
    {
        cout << "The node " << delData << " was not found in the list" << endl;
        delete delPtr;
    }
    else
    {
        length--;
        delPtr = curr;
        curr = curr->next;
        temp->next = curr;
        if(delPtr == head)
            head = curr;
        delete delPtr;
        cout << "The value " << delData << " was deleted from the list" << endl;
    }
}

// Delete node At a position ------------------------------------------------------------------------------
void SLL::delNodeAt(int pos)
{
    if(pos < 1 || pos > length)
        cout << "Cannot delete node. There are " << length << " items in the list" << endl;
    else
    {
        nodePtr delPtr;
        length--;
        if(pos==1)
        {
            delPtr = head;
            head = head->next;
            delete delPtr;
        }
        else
        {
            curr = head;
            temp = head;
            for(int count=1; count<pos; count++)
            {
                temp = curr;
                curr = curr->next;
            }
            delPtr = curr;
            curr = curr->next;
            temp->next = curr;
            delete delPtr;
        }
    }
}

// print List -----------------------------------------------------------------------------------------
void SLL::printList(string direction)
{
    if(direction == "forward")
        printListPrivate(1, head);
    else if(direction == "reverse")
        printListPrivate(0, head);
    cout << endl;
}

void SLL::printListPrivate(bool forward, nodePtr ptr)
{
    if(ptr==NULL)
        return;
    else
    {
        if(forward)
        {
            cout << ptr->data << " ";
            printListPrivate(forward, ptr->next);
        }
        else
        {
            printListPrivate(forward, ptr->next);
            cout << ptr->data << " ";
        }
    }
}

// Search List iteratively ------------------------------------------------------------------------------
void SLL::searchList(int searchData)
{
    if(head == NULL)
        cout << "The list is empty" << endl;
    else
    {
        curr = head;
        int pos = 1;
        while(curr != NULL && curr->data != searchData)
            curr = curr->next;
        if(curr == NULL)
            cout << searchData << " was not found in the list" << endl;
        else
            cout << searchData << " was found at " << pos << " position" << endl;
    }
}

// Search List Recursively -------------------------------------------------------------------------------
void SLL::searchRecursive(int searchData)
{
    searchRecursivePrivate(searchData, head);
}

void SLL::searchRecursivePrivate(int searchData, nodePtr ptr)
{
    if(ptr == NULL)
    {
        cout << searchData << " was not in the list " << endl;
    }
    else if(ptr->data == searchData)
    {
        cout << searchData << " is in the list " << endl;
    }
    else
    {
        searchRecursivePrivate(searchData,ptr->next);
    }
}


// Size of List ------------------------------------------------------------------------------------------
void SLL::sizeOfList()
{
    cout << "There are " << length << " items in the list" << endl;
}

// Reverse List iteratively ------------------------------------------------------------------------------
void SLL::reverseUsingIterative()
{
    if(head == NULL)
        cout << "The list is empty" << endl;
    else
    {
        curr = head;
        nodePtr prev = NULL;
        while(curr != NULL)
        {
            temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        head = prev;
    }
}

// Reverse List Recursion ------------------------------------------------------------------------------
void SLL::reverseUsingRecursion()
{
    reverseUsingRecursionPrivate(head);
}

void SLL::reverseUsingRecursionPrivate(nodePtr ptr)
{
    if(ptr->next==NULL)
    {
        head = ptr;
        return;
    }
    else
    {
        reverseUsingRecursionPrivate(ptr->next);
        curr = ptr->next;
        curr->next = ptr;
        ptr->next = NULL;
    }
}

// Reverse List Stack ------------------------------------------------------------------------------
void SLL::reverseUsingStack()
{
    stack<nodePtr> st;
    if(head == NULL)
        cout << "The list is empty" << endl;
    else
    {
        curr = head;
        while(curr!=NULL)
        {
            st.push(curr);
            curr = curr->next;
        }
        curr = st.top();
        head = curr;
        st.pop();
        while(!st.empty())
        {
            curr->next = st.top();
            st.pop();
            curr = curr->next;
        }
        curr->next = NULL;
    }
}

// Queue Enqueue -----------------------------------------------------------------------------------------
void SLL::enqueue(int addData)
{
    nodePtr n = new node;
    n->data = addData;
    n->next = NULL;
    
    if(head == NULL && tail == NULL)
    {
        head = n;
        tail = n;
    }
    else
    {
        tail->next = n;
        tail = n;
    }
}

// Queue Dequeue -----------------------------------------------------------------------------------------
void SLL::dequeue()
{
    nodePtr delPtr;
    
    if(head == NULL)
    {
        cout << "The Queue/List is Empty " << endl;
    }
    if(head==tail)
        head=tail=NULL;
    else
    {
        delPtr = head;
        head = head->next;
        delete delPtr;
    }
}
// Queue front -----------------------------------------------------------------------------------------
int SLL::front()
{
    if(head == NULL)
        cout << "The Queue/List is empty" << endl;
    else
        return head->data;
    return 0;
}

// Queue or Stack Empty --------------------------------------------------------------------------------
bool SLL::isEmpty()
{
    if(head == NULL)
        return true;
    else
        return false;
}

// Stack Push -----------------------------------------------------------------------------------------
void SLL::push(int addData)
{
    nodePtr n = new node;
    n->data = addData;
    n->next = head;
    head = n;
}

// Stack Pop -----------------------------------------------------------------------------------------
void SLL::pop()
{
    nodePtr delPtr;
    if(head==NULL)
        return;
    else
    {
        delPtr = head;
        head = head->next;
        delete delPtr;
    }
}

// Stack Top -----------------------------------------------------------------------------------------
int SLL::top()
{
    if(head==NULL)
        return 0;
    else
    {
        return head->data;
    }
}

// Destructor -----------------------------------------------------------------------------------------
SLL::~SLL()
{
    if(head != NULL)
    {
        cout << "Deleting ";
        curr = head;
        temp = head;
        while(curr->next!=NULL)
        {
            curr=curr->next;
            cout  << temp->data << " ";
            delete temp;
            temp = curr;
        }
        cout << curr->data << endl;
        delete curr;
    }
}

// Return Head -------------------------------
SLL::nodePtr SLL::returnHead()
{
    return head;
}

// Intersection -----------------------------------------------------------------------------------------
void SLL::interect(const nodePtr n)
{
    nodePtr newList = new node;
    nodePtr tail = newList;
    newList->next = NULL;
    nodePtr temp1 = head,temp2 = n;
    while(temp1 != NULL && temp2 != NULL)
    {
        if(temp1->data == temp2->data)
        {
            addNode(temp1->data);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if(temp1->data < temp2->data)
            temp1 = temp1->next;
        else
            temp2 = temp2->next;
    }
    tail = tail->next;
    while(tail!=NULL)
    {
        cout << tail->data << " ";
        tail = tail->next;
    }
}

while(fast!=NULL && slow!= NULL)
{
    fast = fast->next;
    slow = slow->next;
    first->next = second;
    second->next = fast;
    first = fast;
    test = second;
    second = slow;
}
if(slow!=NULL)
{
    test->next = slow;
}