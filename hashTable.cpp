#include <iostream>
#include "hashTable.h"
#include "fibonacciHeap.h"
#include <sstream>
#include <fstream>
#include <string>


hashTable::hashTable()
{
    //ctor
}

hashTable::~hashTable()
{
    //dtor
}

/* To insert a new entry in the hash Table  */
void hashTable::insertKey(string key, int freq)
{

    fibNode *node = newEntry.createNode(freq, key);
    newEntry.insertNode(node);
    entry[key] = node;
}

/* To find entry in the hash Table          */
int hashTable::findKey(string key)
{
    if(entry.find(key)!= entry.end())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* To increase value of entry already present in the hash Table     */
void hashTable::increaseKey(string key, int newValue)
{
    std::unordered_map<string, fibNode*>::iterator i = entry.find(key);
    if(i != entry.end())
    {
        fibNode *node = i->second;
        newEntry.increaseKey(node, newValue);
    }

}

/* To display number of maxValues in the hash Table                 */
void hashTable::displayMaxValues(int totalValueToDisplay, string outputFilename)
{
    fibNode **listOfValues;
    int count_val = 0;
    listOfValues = new fibNode*[totalValueToDisplay];
    ofstream output_file;
    output_file.open(outputFilename, ios::out | ios::app);

    for(int i = 0; i<totalValueToDisplay ; i++)
    {
        listOfValues[i] = newEntry.extractMax();
        if(listOfValues[i]!= nullptr)
        {
            string outVal = listOfValues[i]->keyValue;
            output_file<<outVal.substr(1,(outVal.length()-1));
            if(i<(totalValueToDisplay-1))
            {
                output_file<<",";
            }
            count_val++;
        }
        else
        {
            break;
        }

    }
    output_file<<endl;
    output_file.close();

    for(int i = 0; i<count_val ; i++)
    {
        newEntry.insertNode(listOfValues[i]);
    }

}
