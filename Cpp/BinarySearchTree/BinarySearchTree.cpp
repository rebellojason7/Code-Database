#include <iostream>
#include <queue>
#include "BinarySearchTree.h"

using namespace std;

// Constructor (Initialize tree) -------------------------------------------------------------------------
BST::BST()
{
    root = NULL;
}

// Create leaf ---------------------------------------------------------------------------------------
BST::nodePtr BST::createLeaf(int key)
{
    nodePtr n = new node;
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// Add leaf to tree ---------------------------------------------------------------------------------------
void BST::addLeaf(int key)
{
    addLeafPrivate(key, root);
}

void BST::addLeafPrivate(int key, nodePtr ptr)
{
    if(root == NULL)
    {
        root = createLeaf(key);
    }
    else if(key < ptr->key)
    {
        if(ptr->left != NULL)
            addLeafPrivate(key, ptr->left);
        else
            ptr->left = createLeaf(key);
    }
    else if(key > ptr->key)
    {
        if(ptr->right != NULL)
            addLeafPrivate(key, ptr->right);
        else
            ptr->right = createLeaf(key);
    }
    else
        cout << "The tree already has a value of " << key << endl;
}

// BFS (Level order) --------------------------------------------------------------------------------------
void BST::printLevelOrder()
{
    printLevelOrderPrivate(root);
}

void BST::printLevelOrderPrivate(nodePtr ptr)
{
    if(ptr == NULL)
        cout << "The tree is empty" << endl;
    else
    {
        queue<nodePtr> q;
        q.push(root);
        while(!q.empty())
        {
            curr = q.front();
            cout << curr->key << " ";
            if(curr->left != NULL)
                q.push(curr->left);
            if(curr->right != NULL)
                q.push(curr->right);
            q.pop();
        }
    }
}

// DFS (In order) ---------------------------------------------------------------------------------------

void BST::printInOrder()
{
    printInOrderPrivate(root);
}

void BST::printInOrderPrivate(nodePtr ptr)
{
    if(ptr == NULL)
        return;
    else
    {
        printInOrderPrivate(ptr->left);
        cout << ptr-> key << " ";
        printInOrderPrivate(ptr->right);
    }
}

// DFS (Pre order) ---------------------------------------------------------------------------------------

void BST::printPreOrder()
{
    printPreOrderPrivate(root);
}

void BST::printPreOrderPrivate(nodePtr ptr)
{
    if(ptr == NULL)
        return;
    else
    {
        cout << ptr-> key << " ";
        printPreOrderPrivate(ptr->left);
        printPreOrderPrivate(ptr->right);
    }
}

// DFS (Post order) ---------------------------------------------------------------------------------------

void BST::printPostOrder()
{
    printPostOrderPrivate(root);
}

void BST::printPostOrderPrivate(nodePtr ptr)
{
    if(ptr == NULL)
        return;
    else
    {
        printPostOrderPrivate(ptr->left);
        printPostOrderPrivate(ptr->right);
        cout << ptr-> key << " ";
    }
}

// Return Node of Key -------------------------------------------------------------------------------------

BST::nodePtr BST::returnNode(int key)
{
    return returnNodePrivate(key, root);
}

BST::nodePtr BST::returnNodePrivate(int key, nodePtr ptr)
{
    if(ptr != NULL)
    {
        if(ptr->key == key)
            return ptr;
        else
        {
            if(key < ptr->key)
                return returnNodePrivate(key, ptr->left);
            else
                return returnNodePrivate(key, ptr->right);
        }
    }
    else
        return NULL;
}

// Return Root Key ---------------------------------------------------------------------------------------

int BST::returnRootKey()
{
    if(root != NULL)
        return root->key;
    else
        return INT32_MIN;
}

// Print Children of Key ----------------------------------------------------------------------------------

void BST::printChildren(int key)
{
    nodePtr ptr = returnNode(key);
    if(ptr != NULL)
    {
        cout << "Parent node = " << ptr->key << endl;
        
        ptr->left == NULL ?
        cout << "Left Child = NULL" << endl:
        cout << "Left child :" << ptr->left->key << endl;
        
        ptr->right == NULL ?
        cout << "Right Child = NULL" << endl:
        cout << "Right child :" << ptr->right->key << endl;
    }
    else
        cout << "Key " << key << " was not found in the tree" << endl;
}

// Find Smallest Key --------------------------------------------------------------------------------------

int BST::findSmallest()
{
    return findSmallestPrivate(root);
}

int BST::findSmallestPrivate(nodePtr ptr)
{
    if(root == NULL)
    {
        cout << "The tree is empty" << endl;
        return INT32_MIN;
    }
    else
    {
        if(ptr->left != NULL)
        {
            return findSmallestPrivate(ptr->left);
        }
        else
            return ptr->key;
    }
}

// Remove Node ---------------------------------------------------------------------------------------

void BST::removeNode(int key)
{
    removeNodePrivate(key, root);
}

void BST::removeNodePrivate(int key, nodePtr parent)
{
    if(root!=NULL)
    {
        if(root->key == key)
            removeRootMatch();
        else
        {
            if(key < parent->key && parent->left != NULL)
            {
                parent->left->key==key?
                removeMatch(parent,parent->left,true):
                removeNodePrivate(key,parent->left);
            }
            else if(key>parent->key && parent->right != NULL)
            {
                parent->right->key==key?
                removeMatch(parent,parent->right,false):
                removeNodePrivate(key, parent->right);
            }
            else
                cout << "The key " << key << " was not found in the tree" << endl;
        }
    }
    else
        cout << "The tree is empty " << endl;
}

// Remove Root ---------------------------------------------------------------------------------------

void BST::removeRootMatch()
{
    if(root!=NULL)
    {
        nodePtr delPtr = root;
        int rootKey = root->key;
        int smallestInRightSubtree;
        
        // No Children
        if(root->left == NULL && root->right == NULL)
        {
            root = NULL;
            delete delPtr;
        }
        
        // Only Right child
        else if(root->left==NULL and root->right!=NULL)
        {
            root = root->right;
            delPtr->right = NULL;
            delete delPtr;
            cout << "The root node with key " << rootKey << " was deleted. The new root key is " << root->key << endl;
        }
        
        // Only Left child
        else if(root->right==NULL and root->left!=NULL)
        {
            root = root->left;
            delPtr->left = NULL;
            delete delPtr;
            cout << "The root node with key " << rootKey << " was deleted. The new root key is " << root->key << endl;
        }
        
        // Both children
        else
        {
            smallestInRightSubtree = findSmallestPrivate(root->right);
            removeNodePrivate(smallestInRightSubtree, root);
            root->key = smallestInRightSubtree;
            cout << "The root key containing key " << rootKey << " was overwritten with key " << root->key << endl;
        }
    }
    else
        cout << "Cannot remove node. The tree is empty" << endl;
}

void BST::removeMatch(nodePtr parent, nodePtr match, bool left)
{
    if(root != NULL)
    {
        nodePtr delPtr;
        int matchKey = match->key;
        int smallestInRightSubtree;
        
        if(match->left==NULL && match->right==NULL)
        {
            delPtr = match;
            left==true ? parent->left = NULL : parent->right = NULL;
            delete delPtr;
            cout << "THe node containing key " << matchKey << " was removed";
        }
        
        else if(match->left==NULL && match->right!=NULL)
        {
            left==true ? parent->left=match->right : parent->right = match->right;
            match->right = NULL;
            delPtr = match;
            delete delPtr;
            cout << "THe node containing key " << matchKey << " was removed";
        }
        
        else if(match->left!=NULL && match->right==NULL)
        {
            left==true ? parent->left=match->left : parent->right = match->left;
            match->left = NULL;
            delPtr = match;
            delete delPtr;
            cout << "THe node containing key " << matchKey << " was removed";
        }
        
        else
        {
            smallestInRightSubtree = findSmallestPrivate(match->right);
            removeNodePrivate(smallestInRightSubtree, match);
            match->key = smallestInRightSubtree;
        }
    }
    else
        cout << "Cannot remove match. The tree is empty" << endl;
}

// Destructor ---------------------------------------------------------------------------------------

BST::~BST()
{
    removeSubtree(root);
}

void BST::removeSubtree(nodePtr ptr)
{
    if(ptr != NULL)
    {
        if(ptr->left != NULL)
            removeSubtree(ptr->left);
        if(ptr->right != NULL)
            removeSubtree(ptr->right);
        cout << "Deleting the node with key " << ptr->key << endl;
        delete ptr;
    }
}

// Print Min Element --------------------------------------------------------------------------------------

void BST::printMin()
{
    if(root==NULL)
    {
        cout << "The tree is empty" << endl;
    }
    else
    {
        nodePtr ptr = root;
        while(ptr->left != NULL)
            ptr = ptr->left;
        cout << "Min element in tree is " << ptr->key << endl;
    }
}

// Print Max Element --------------------------------------------------------------------------------------

void BST::printMax()
{
    if(root==NULL)
    {
        cout << "The tree is empty" << endl;
    }
    else
    {
        nodePtr ptr = root;
        while(ptr->right != NULL)
            ptr = ptr->right;
        cout << "Max element in tree is " << ptr->key << endl;
    }
}

// Find Height of Tree ------------------------------------------------------------------------------------

int BST::findHeight()
{
    return findHeightPrivate(root);
}

int BST::findHeightPrivate(nodePtr ptr)
{
    if(ptr==NULL)
        return -1;
    else
        return max(findHeightPrivate(ptr->left),findHeightPrivate(ptr->right))+1;
}

// Test if Tree is BST ------------------------------------------------------------------------------------

bool BST::isBinarySearchTree()
{
    return isBinarySearchTreePrivate(root, INT_MIN, INT_MAX);
}

bool BST::isBinarySearchTreePrivate(nodePtr ptr, int minValue, int maxValue)
{
    if(ptr == NULL)
        return true;
    else
    {
        if(ptr->key > minValue
           && ptr->key < maxValue
           && isBinarySearchTreePrivate(ptr->left, minValue, ptr->key)
           && isBinarySearchTreePrivate(ptr->right, ptr->key, maxValue))
            return true;
        else
            return false;
    }
}

void BST::deleteNode(int data)
{
    deleteNodePrivate(root, data);
}

BST::nodePtr BST::deleteNodePrivate(nodePtr ptr, int data)
{
    if(ptr==NULL)
        return ptr;
    else if(data < ptr->key)
        ptr->left = deleteNodePrivate(ptr->left, data);
    else if(data > ptr->key)
        ptr->right = deleteNodePrivate(ptr->right, data);
    else
    {
        if(ptr->left == NULL && ptr->right == NULL)
        {
            delete ptr;
            ptr = NULL;
        }
        else if(ptr->left == NULL)
        {
            nodePtr temp = ptr;
            ptr = ptr->right;
            delete temp;
        }
        else if(ptr->right == NULL)
        {
            nodePtr temp = ptr;
            ptr = ptr->left;
            delete temp;
        }
        else
        {
            nodePtr temp = returnNodePrivate(findSmallestPrivate(ptr->right),ptr->right);
            ptr->key = temp->key;
            ptr->right = deleteNodePrivate(ptr->right, temp->key);
        }
    }
    return ptr;
}

// Find Successor --------------------------------------------------------------------------------------

void BST::getSuccessor(int data)
{
    getSuccessorPrivate(root, data);
}

BST::nodePtr BST::getSuccessorPrivate(nodePtr ptr, int data)
{
    nodePtr curr = returnNodePrivate(data, root); // O(h)
    if(curr == NULL)
        return NULL;
    // Case 1: Node has right subtree
    if(curr->right != NULL) //O(h)
    {
        nodePtr temp = curr->right;
        while(temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }
    
    // Case 2: No right subtree O(h)
    else
    {
        nodePtr successor = NULL;
        nodePtr ancestor = root;
        while(ancestor != curr)
        {
            if(curr->key < ancestor->key)
            {
                successor = ancestor; // so far this is the deepest node for which current node is left
                ancestor = ancestor->left;
            }
            else
                ancestor = ancestor->right;
        }
        return successor;
    }
}