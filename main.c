

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "histo.h"
#include "leaks.h"

int main(int argc, char *argv[])
{
    // Check if the minimum number of arguments is provided
    if (argc < 4)
    {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <mode> [plant_id]\n", argv[0]);
        fprintf(stderr, "Modes: max, src, real, leaks\n");
        return 1;
    }

    // Assign command line arguments to descriptive variable names
    const char *input_file = argv[1];
    const char *output_file = argv[2];
    const char *mode = argv[3];

    // Check for "histo" modes: max, src, real
    if (strcmp(mode, "max") == 0 || strcmp(mode, "src") == 0 || strcmp(mode, "real") == 0)
    {
        // Call the histo_process function with the input/output files and the mode
        return histo_process(input_file, output_file, mode);
    }
    // Check for "leaks" mode
    else if (strcmp(mode, "leaks") == 0)
    {
        // Check if the mandatory plant identifier argument is provided for 'leaks' mode
        if (argc < 5)
        {
            fprintf(stderr, "Error: leaks mode requires a plant identifier\n");
            return 1;
        }
        // Assign the fifth argument as the plant identifier
        const char *plant_id = argv[4];
        
        // Call the leaks_process function
        return leaks_process(input_file, output_file, plant_id);
    }
    // Handle unknown mode
    else
    {
        fprintf(stderr, "Error: Unknown mode '%s'\n", mode);
        return 1;
    }

    // Note: The return 0 here is unreachable due to the conditional returns above,
    // but is kept for completeness (though the function should terminate in one of the branches).
    return 0; 
}
