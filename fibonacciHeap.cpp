#include "fibonacciHeap.h"
#include "hashTable.h"
#include <cstddef>
#include <math.h>
#include <limits>
#include <iostream>
#include <cmath>
#include <cstdlib>

/* Constructor */
fibonacciHeap::fibonacciHeap()
{
    //ctor
    head = nullptr;             /*Node with max value*/
    nH = 0;                     /*Total number of nodes in fibonacci Heap*/
}

/* Destructor */
fibonacciHeap::~fibonacciHeap()
{
    //dtor
}


/* Create a Node to be inserted into fibonacci Heap */
fibNode* fibonacciHeap::createNode(int key, string hashTag)
{
    fibNode *x  = new fibNode;                              /* New node to be inserted                                      */
    x->key      = key;                                      /* Freq to be entered to be used as key                         */
    x->keyValue = hashTag;                                  /* Hashtag to used to identify the node                         */
    x->child    = nullptr;                                  /* Child pointer of the current Node                            */
    x->parent   = x;                                        /* Parent pointer of the current Node                           */
    x->left     = nullptr;                                  /* Left pointer of the current Node pointing to left sibling    */
    x->right    = nullptr;                                  /* Right pointer of the current Node pointing to right sibling  */
    x->degree   = 0;                                        /* Degree gives number of children of the current Node          */
    x->mark     = false;                                    /* Child cut mark of the current Node                           */

    return x;
}


/* Insert a Node to be inserted into fibonacci Heap */
fibNode* fibonacciHeap::insertNode(struct fibNode *x)
{
    /* If no node in heap then insert node fibonacci Heap and make it head Else If node is
    present in heap then insert node into Heap and make one with highest key as head */
    if(head == nullptr)
    {
        x->left = x;
        x->right = x;
        x->parent = x;
        x->child = nullptr;
        x->mark = false;
        x->degree = 0;
        head = x;
    }
    else
    {
        head->left->right = x;
        x->left = head->left;
        head->left = x;
        x->right = head;

        x->parent = x;
        x->child = nullptr;
        x->mark = false;
        x->degree = 0;

        if(x->key > head->key)
        {
            head = x;
        }
    }
    nH = nH + 1;
    return head;
}

/* Extract node with max value in the fibonacci Heap */
fibNode* fibonacciHeap::extractMax()
{
    struct fibNode *h, *b, *next;                           /* node pointer to be used for iterating the circular lists         */
    struct fibNode **childList;                             /* Array of pointers of fibNode to be inserted into toplevel list   */

    h = head;
    if(h != nullptr)
    {
        b = h->child;
        if(b!= nullptr)
        {
            childList = new fibNode*[h->degree];
            next = b;
            for(int i =0; i<(int)h->degree; i++)
            {
                childList[i] = next;
                childList[i]->parent = childList[i];
                childList[i]->mark = false;
                next = next->right;
            }
            for(int j = 0; j< (int)h->degree; j++)
            {
                b = childList[j];
                head->left->right = b;
                b->left = head->left;
                head->left = b;
                b->right = head;

                b->parent = b;
                b->mark = false;

            }
            delete [] childList;

        }


        /* Remove the node with max value   */
        h->left->right = h->right;
        h->right->left = h->left;

        /* Make a new head pointer          */
        /* Consolidate the nodes and complete the delayed work of making pairwise combines if there are
            more nodes in top level list*/
        if(h == h->right)
        {
            head = nullptr;
        }
        else
        {
            head = h->right;
            consolidate();
        }
        nH--;

    }
    return h;
}

/* Increase the key of node if it is present in the fibonacci Heap */
void fibonacciHeap::increaseKey(struct fibNode *x, int newkey)
{
    struct fibNode *temp;                                   /* Node pointer to be used for storing parent value         */
    if(x->key > ((int)(x->key) + (int)(newkey)))
    {
        return;
    }

    x->key = ((int)(x->key) + (int)(newkey));
    temp = x->parent;

    /* Call cut to remove the current node from under its parent and also to check for childcut field*/
    if(temp!= x && x->key > temp->key)
    {
        cut(x, temp);
    }

    if(x->key > head->key)
    {
        head = x;
    }

}

/* Cut the node from its parent and check for Child cut field of parent         */
void fibonacciHeap::cut(struct fibNode *x, struct fibNode *y)
{
    /* Remove child node from parents sibling list  */
    x->right->left = x->left;
    x->left->right = x->right;

    /* Update the new child if any more nodes present in child list of parent   */
    if(y->child->left == x)
    {
        y->child = nullptr;
    }
    else
    {
        y->child = x->left;
    }
    y->degree--;

    x->left = nullptr;
    x->right = nullptr;

    /* To check if parents Child cut mark is violated now, If true then need to cut it
    and check for grandparents Child cut mark and further on until we find a node with
    false mark or we reach the root node*/
    cascading_cut(y);

    head->right->left = x;
    x->right = head->right;
    head->right = x;
    x->left = head;

    x->parent = x;
    x->mark = false;



    if(x->key > head->key)
    {
        head = x;
    }


}

/* Cascading cut to check the child cut field of parent */
void fibonacciHeap::cascading_cut(struct fibNode *y)
{
    struct fibNode *y_Par;

    y_Par = y->parent;
    if(y_Par!= y)
    {
        if(y->mark == false)
        {
            y->mark = true;
        }
        else
        {
            cut(y, y_Par);
        }
    }
}


/* To combine two nodes with the node with higher key becoming the parent of other node with lower key*/
void fibonacciHeap::pairwiseCombine(struct fibNode *newChild, struct fibNode *newParent)
{
    newChild->left->right = newChild->right;
    newChild->right->left = newChild->left;

    if(newParent->child != nullptr)
    {
        newParent->child->left->right = newChild;
        newChild->left = newParent->child->left;
        newParent->child->left = newChild;
        newChild->right = newParent->child;
    }
    else
    {
        newParent->child = newChild;
        newChild->right = newChild;
        newChild->left  = newChild;
    }
    newChild->parent = newParent;
    newParent->degree++;
    newChild->mark = false;

}

/* Finding the degree which gives us max range of children any node could have in the fibonacci heap    */
int fibonacciHeap::initializeDegreeTable()
{
    int max_degree = static_cast<int>(floor(log(static_cast<double>(nH))/log(static_cast<double>(1 + sqrt(static_cast<double>(5)))/2)));
    return max_degree;
}

/* To remove any arbitrary node */
void fibonacciHeap::arbitrary_remove(struct fibNode *x)
{
    increaseKey(x, std::numeric_limits<int>::max());
    struct fibNode* arbitrary_removed_node = extractMax();
    delete arbitrary_removed_node;
}

/* To get the node with max key in the fibonacci heap   */
fibNode* fibonacciHeap::getMax()
{
    return head;
}

/* To find the total number of nodes in the fibonacci heap  */
int fibonacciHeap::getNumNodes()
{
    return (int)nH;
}

/* To consolidate the nodes present in the top level list using pairwise combine    */
void fibonacciHeap::consolidate()
{

    struct fibNode *t, *u, *v;                                      /* Temporary nodes to be used during consolidate            */
    struct fibNode *next, *temp;                                    /* Temporary nodes to be used during consolidate            */

    struct fibNode **A, **rootlist;                                 /* Array of the nodes which we need to combine             */

    int deg, root_size;
    int max_degree = initializeDegreeTable();


    A = new fibNode*[max_degree+2];

    for (int i = 0; i < (max_degree+2); i++)                        /* Initialize array of the nodes which we need to combine  */
    {
        A[i] = nullptr;
    }

    t = head;
    root_size = 0;
    next = t;


    do                                                              /* Calculate the top level circular list size              */
    {
        root_size++;
        next = next->right;
    }while(next!=t);

    rootlist = new fibNode*[root_size];

    for(int i = 0; i<root_size; i++)
    {
        rootlist[i] = next;
        next = next->right;
    }

    for(int i = 0; i<root_size; i++)                                /* Perform pariwise combine of nodes in the top level circular list size*/
    {
        t = rootlist[i];
        u = t;
        deg = u->degree;
        while(A[deg]!= nullptr)
        {
            v = A[deg];
            if(u->key < v->key)
            {
                temp    = u;
                u       = v;
                v       = temp;
            }
            pairwiseCombine(v, u);

            A[deg] = nullptr;
            deg++;
        }
        A[deg] = u;

    }

    delete [] rootlist;                                             /* Free the array of node pointers                          */

    head = nullptr;

    for(int i = 0; i< max_degree+2; i++)                            /* Recreate the top level circular list with new head pointing to node with max key */
    {
        if(A[i]!=nullptr)
        {
            if(head == nullptr)
            {
                A[i]->left = A[i];
                A[i]->right = A[i];
                head =  A[i];
            }
            else
            {
                head->left->right = A[i];
                A[i]->left = head->left;
                head->left = A[i];
                A[i]->right = head;

                if(A[i]->key > head->key)
                {
                    head = A[i];
                }
            }
        }

    }
    delete [] A;
}

