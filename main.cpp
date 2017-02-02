#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "fibonacciHeap.h"
#include "hashTable.h"


using namespace std;

int main(int argc, char *argv[])
{

    hashTable hashEntry;                                                /* hashEntry of type hashTable class                */
    string hashTag;
    int freq;
    string input_line;

    ifstream input_file(argv[1], ios::in);                                       /* Create an input filestream to read the files     */
    if(input_file.is_open())                                            /* Check if file is open                            */
    {
        while(getline(input_file, input_line))                          /* Read from file word by word                      */
        {
            if(input_line[0] ==  '#')                                   /* Check if word is hashTag or query for result     */
            {
                stringstream linestream(input_line);                    /* Read line word by word to separate hashTag
                                                                           and frequency of word                            */
                while(linestream >> hashTag >> freq)
                {
                    int out_val = hashEntry.findKey(hashTag);           /* Check if hashTag is already present in hashTable*/
                    if(out_val == 1)
                    {
                        hashEntry.increaseKey(hashTag, freq);           /* If already present then increase the key         */
                    }
                    else
                    {
                        hashEntry.insertKey(hashTag, freq);             /* If not then make a new entry in the hashTable    */
                    }

                }
            }
            else
            {
                if(input_line.compare("STOP") == 0)                     /* If encountered word is STOP then stop the program
                                                                            and close the file                              */
                {
                    input_file.close();
                    return 0;
                }
                else                                                    /* If query for maximum values is encountered       */
                {
                    int j = atoi(input_line.c_str());

                     hashEntry.displayMaxValues(j, "output_file.txt");

                }
            }

        }
        input_file.close();

    }
    else
    {
        cout<<"Unable to open the file"<<endl;
    }

    return 0;
}
