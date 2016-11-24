#include "PUCSR1ToolBox.h"

namespace PUCSR1ToolBox 
{

    PartitionModel * get_part_set (ElementSubset * part, 
        ElementSet * original_set)
    {
        // unsigned int nof_fx_elm = part->get_set_cardinality ();
        // ElementSubset * sel = new ElementSubset ("", original_set);
        // ElementSubset * non_sel = new ElementSubset ("", original_set);
        // for (unsigned int i = 0; i < nof_fx_elm; i++)
        // {
        //     if (part->has_element (i))
        //         sel->add_element (i);
        //     else
        //         non_sel->add_element (i);
        // }
        // PartitionModel * part_model = new PartitionModel (sel, non_sel);
        // delete sel;
        // delete non_sel;
        // return part_model;
    }

}