#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "fibonacciHeap.h"
#include <map>
#include <unordered_map>

class hashTable
{
    public:
        hashTable();
        virtual ~hashTable();
        void insertKey(string, int);                                    /* Function to insert the key in hash table                     */
        int findKey(string);                                            /* Function to find if the key is present in hash table         */
        void increaseKey(string, int);                                  /* Function to increase the key in hash table                   */
        void displayMaxValues(int, string);                             /* Function to find the number of max key in hash table         */

    protected:

    private:
        std::unordered_map<string, fibNode*> entry;                     /* entry of type hash table                                     */
        fibonacciHeap newEntry;                                         /* newEntry of type fibonacciHeap                               */
};

#endif // HASHTABLE_H
