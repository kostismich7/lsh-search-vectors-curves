#include <iostream>
#include <iomanip>
#include <limits>
#include "HashTableStruct.h"
#include "Dataset.h"
#include "ui.h"
#include "parse_files.h"
#include "utils.h"
#include "LSH.h"
#include "hasher.h"
#include "distance.h"
#include "search.h"


LSH* lsh;

int main(int argc, char* argv[]){

    lsh = new LSH;

    /**
     * read arguments
     */
    readArgumentsLSH(lsh, argc, argv);

    /**
     * ask input filename (if not given as an argument)
     */
    if(!lsh->isInputFileGiven())
        lsh->setInputFilename(askInputFile());

    /**
     * parse input file into memory
     */
    lsh->setData(parseInputFilePoints(lsh->getInputFilename()));
    cout << lsh->getDataset()->getMean() << endl;
    //test_print_data(lsh->getData());

    /**
     * insert data into hash tables
     */
    cout << "Constructing hash table..." << endl;
    lsh->setHashTableStruct(new PointHashTableStruct(lsh->getNumOfHashTables(), lsh->getDataset()->getSize(),lsh->getNumOfFunctions(),lsh->getDataset()->getDimension(),lsh->getDataset()->getMean()));
    auto points = lsh->getDataset()->getData();
    for (auto & point : points)
        lsh->getHashTableStruct()->addToAllHashTables(point);
    //lsh->getHashTableStruct()->test_print_hashtable();

    /**
     * ask query filename and output filename (if not given as arguments)
     */
    if(!lsh->isQueryFileGiven())
        lsh->setQueryFilename(askQueryFile());
    if(!lsh->isOutputFileGiven())
        lsh->setOutputFilename(askOutputFile());

    /**
     * parse query file into memory
     */
    lsh->setQueryData(parseQueryFilePoints(lsh->getQueryFilename()));
    //test_print_query_data(lsh->getQueryData());

    /**
     * search
     */
    search_points_LSH_vs_BruteForce(lsh);

    //ask user if he wants another one

    // +check memory leaks

    return 0;
}


