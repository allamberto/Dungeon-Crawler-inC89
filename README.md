James Bonadonna (jbonadon), Ana Lamberto (alamber2), Sean Michalec (smichale)

*NOTE: This code has been adapted from code borrowed, with permission, from Ryan Michalec, the queue.c and queue.h files, as well as the pathfind() function were all written by this group, but the underlying hag interface was created before we added anything.*

Testing
--------

In order to perform testing on this project, first cd into the testing directory, which has its own makefile. In this, make the program, then run ./test in order to get the time it takes to run through Dijkstra's Algorithm. The distance to move is modifiable, and can be changed from a distance of 0-15 (the max sight range of an enemy) by running "./text dx dy", where dx and dy are the distance the enemy is from the player in the x and y directions, respectively. If a number greater than 15 is entered, it will create an uninitialized value error, as this is a case which is never encountered in the actual running of the program. 

There is a README file in the testing folder which has some baseline values for the average running times of linear vs the Dijkstra's Algorithm searching. Due to its speed, there is no time test for the linear search in the testing folder, as it most often takes between 0 and 2 nanoseconds to compute. The README in the testing folder also contains an example of valgrind --leak-check=full being run on the test program. 

Individual Contributions
-------------------------

James Bonadonna (jbonadon): wrote queue.c, queue.h, pathfind(), and test scripts, helped on the README and presentation, performed the walkthrough videos

Ana Lamberto (alamber2): primary debugger for pathfind(), primary writer of the presentation, edited the code walkthrough, helped with README

Sean Michalec (smichale): primary debugger for queue.c, primary writer of the README, helped with the presentation, helped debug test scripts
