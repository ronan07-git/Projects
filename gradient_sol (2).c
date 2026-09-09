#include "gradient.h"

/*For some reason, my window's machine didn't recognise the srandom and random functions.
  so I had to change them to srand and rand */

path_point find_highest_point(){
    // your solution here

    // Initialization of variables, setting the climbers position to 0,0 because of unknown dimensions
    int posXAxis = 0;
    int posYAxis = 0;

    //Variable which creates our FOV of the nearby cells that are visible amidst the fog
    float fieldOfView[VIEW_SIZE][VIEW_SIZE];

    /* Creation of infinite loop, the loop will run infinitely until the exit condition is met which
       for us is finding the peak of the mountain */
    while (1) {
        // View generation method to get the current view
        generate_view(fieldOfView, posYAxis, posXAxis);

        // These two variables help us measure our current height / the value of our current cell
        int posCenter = VIEW_SIZE / 2;
        float currentFieldOfView = fieldOfView[posCenter][posCenter];

        // Variables for the hillclimbing/comparison loops, holding the values which are leading to higher ground
        int leadingDirectionXAxis = 0;
        int leadingDirectionYAxis = 0;

        float bestDirection = currentFieldOfView;

        // Two For loops which scan the surrounding area/cells until they reach the boundary/fog
        for (int i = 0; i < VIEW_SIZE; i++) {
            for (int j = 0; j < VIEW_SIZE; j++) {

                // Conditional for when we collide with the edges of the matrix
                if (fieldOfView[i][j] == -1) {
                    continue;
                }

                // Find the highest value in the current FOV/the direction where the ascent is coming from.
                if (fieldOfView[i][j] > bestDirection) {
                    bestDirection = fieldOfView[i][j];

                    // For example if the ascent is to our left, we'd represent this by moving (center, center-1)
                    leadingDirectionYAxis = i - posCenter;
                    leadingDirectionXAxis = j - posCenter;
                }
            }
        }

        /* This is the plateau detector, when we reach a area which seems to
         * have no higher values among them we follow two protocols which is to
         * declare the peak to confirm if we have reached it.
         *
         * If the peak was not found and we are on a plateau we will instead
         * jump to a new region of the map and start the ascent up the mountain again.
         *
         * The only reason X is scanned is to keep the method simple while finding new land */
        if (bestDirection == currentFieldOfView) {

            if (declare_peak(posXAxis, posYAxis)) {
                path_point ret;
                ret.x = posXAxis;
                ret.y = posYAxis;

                return ret;
            }

            posXAxis += VIEW_SIZE;
            continue;
        }

        // These two lines are what acts as the movement for this program, always moving to the highest value
        posXAxis += leadingDirectionXAxis;
        posYAxis += leadingDirectionYAxis;

    }
}
