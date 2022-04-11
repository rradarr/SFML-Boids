# SFML-Boids
University semester project for Computer Programming sem IV. It's a 2D Boid simulation with interactive control over Boid parameters and Prey/Predator behaviour. Created using C++ and SFML.


![app screen](https://user-images.githubusercontent.com/56255228/162785809-6fa45569-3139-4a48-8dc8-310ab1434110.PNG)

## Boid Simulation
The idea of Boids was proposed by Craig Reynolds in 1986. They create a computer model of coordinated animal motion such as bird flocks and fish schools. It is an example of a complex system where complex, organic and unpredictable behaviour stems from simple rules. 
The three rules that each Boid has to obey are: 
- Separation: steer to avoid crowding local flockmates.
- Alignment: steer towards the average heading of local flockmates.
- Cohesion: steer to move toward the average position of local flockmates.

Local here means that a Boid can only perceive other Boids that are within some distance from it. This addition is crucial to simulating a complex system since a unit element of such system should have limited knowledge of it’s surroundings to achieve balance between chaos and predictability.

## Prey/Predator
Basing on the original three rules one can quite easily introduce new, custom rules. In the application two such rules have been added: Predator and Prey rules. A Boid Group can be a predator group, prey group or neither.

Boids from a prey group will move away, or flee, from Boids from a predator group.

Boids from predator groups will move towards, or chase, Boids from prey groups.

The behaviour can be further customized by changing the weights attributed to the rules. For example the prey rule can have a much higher weight than any other rule since it’s critical to the figurative survival of a Boid.

## Optimization
The application implements a spatially aware bin-lattice spatial subdivision data structure. It speeds up the distance query by dividing the area of the simulation into equal, fixed bins.

The Boids are assigned to bins based on their location each frame. When a Boid wants to find others within some radius from it it can check the Boids that are in nearby bins instead of all Boids present in the simulation. Given that the Boids are somewhat distributed in the simulation area and are not all covered by the nearby bins this data structure significantly improves performance.

The data structure uses a three- dimensional table to represent division of Boids by Group, Bin row and Bin column. At each of these coordinates there is an std::list. This data structure was chosen to allow for fast addition and deletion of elements without invalidating pointers and iterators to the elements. Each frame all Boids register to the BinLattice. Based on their coordinates a pointer to the Boid is placed in an according bin. The Boid updates information about it’s current bin coordinates and an iterator to itself in the list in the BoidLatticeData class. Using this information it will be quick to remove the Boid from the current bin if it moves to an area covered by a different one. When a Boid wants to find nearby Boids it iterates over the Boids pointed to by pointers stored in lists in adjacent bins.

## Control
The user has control over the simulation by the means of a control panel. It can be toggled using Space. There, he can change parameters of a selected Boid Group: weights of movement rules and where a group is a predator, prey or neither. The user can also click in the simulation area to attract or repel Boids relative to the cursor.

Because of the large numbers of Boids in simulations and the real time nature of the application a spatially-aware data structure is used. The bin- lattice spatial subdivision data structure has been chosen to optimize the „local” queries of each Boid.

At the bottom of the control panel there are two squares. These are tools that can be used when clicking in the simulation area. The left one is attraction, it is active by default. It will attract Boids to the cursor. The right one is repulsion.

Left mouse button will use the tool within the selected Boid Group. Right mouse button will use the tool on all Boids.

## More

More information avialable in the [Report PDF](./Computer%20Programming%20Report%20-%20SFML-Boids.pdf) file which was prepared as a final project artifact for the course Computer Programming.
