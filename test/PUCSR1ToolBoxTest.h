#ifndef PUCSR1TOOLBOXTEST_H_
#define PUCSR1TOOLBOXTEST_H_

#include "../src/algorithms/PUCSR1ToolBox.h"
#include "../src/ElementSubset.h"
#include "../src/ElementSet.h"
#include "../src/Partition.h"
#include "../src/PartitionNode.h"
#include "../src/Collection.h"
#include "../src/functions/AbsSum.h"

namespace PUCSR1ToolBoxTest
{

    bool it_should_find_the_partition_minimum ();
    bool it_should_find_an_adjacent_partition ();
    bool it_should_prune_and_walk ();
    
}

#endif /* PUCSR1TOOLBOXTEST_H_ */
