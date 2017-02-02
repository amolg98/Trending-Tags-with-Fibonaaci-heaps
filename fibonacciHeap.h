#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

/* Structure of fibNode             */
struct fibNode
{
    int key;                                            /* frequency of hashTag in the hashTable                */
    string keyValue;                                    /* name of hashTag in the hashTable                     */
    int degree;                                         /* Total no of children of node in the heap             */
    bool mark;                                          /* Child cut mark of node in the heap                   */
    struct fibNode *child;                              /* Child pointer of node in the heap                    */
    struct fibNode *parent;                             /* Parent pointer of node in the heap                   */
    struct fibNode *left;                               /* Left sibling pointer of node in the heap             */
    struct fibNode *right;                              /* Right sibling pointer of node in the heap            */
};

class fibonacciHeap
{
    public:
        fibonacciHeap();
        virtual ~fibonacciHeap();

        fibNode* createNode(int, string);                       /* Create a node passing frequency and hashTag as parameters    */
        fibNode* insertNode(struct fibNode *);                  /* Insert a node passing created node as parameters             */
        void increaseKey(struct fibNode *, int);                /* Increase the value of key                                    */
        void cut(struct fibNode*, struct fibNode*);             /* Cut the node from its parent and check for Child cut field of parent*/
        void cascading_cut(struct fibNode*);                    /* Cascading cut to check the child cut field of parent         */
        void arbitrary_remove(struct fibNode *);                /* To remove any arbitrary node                                 */
        fibNode* extractMax();                                  /* Extract node with max value in the fibonacci Heap            */
		int getNumNodes();                                      /* To find the total number of nodes in the fibonacci heap      */
		fibNode* getMax();                                      /* To get the node with max key in the fibonacci heap           */
        void pairwiseCombine(struct fibNode*, struct fibNode*); /* To combine two nodes with the node with higher key becoming the parent of other node with lower key*/
        void consolidate();                                     /* To consolidate the nodes present in the top level list using pairwise combine    */
		int initializeDegreeTable();                            /* Finding the degree which gives us max range of children any
                                                                    node could have in the fibonacci heap    */

    protected:

    private:
        fibNode* head;                                          /* Denotes the node with maximum value                          */
        int nH;                                                 /* Total number of nodes in fibonacci heap                      */
};

#endif // FIBONACCIHEAP_H
