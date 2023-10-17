# TSP Partition Heuristic

TSP partition Heuristic is a project trying to create a heuristic for the 
*Travelling Salesperson Problem (TSP)* using iteratively a relaxed version of the 
*Mixed Integer Programming (MIP)* model of the problem in which the *Subtour Elimination Constraints (SEC)*
are added only when properly needed.

This project is part of the "*Algorithms and Models for Discrete Optimization*" 2022/2023 course examination.  
The course is held at University of Rome, Tor Vergata.

## The idea behind the heuristic

The heuristic's basic idea is the following :

        When in the MIP model for the TSP problems Subtour Elimination Constraints are not added,  
        the solvers might return an unconnected optimal solution, which is not a correct TSP solution.
        
        But what if, from an unconnected solution, a new TSP instance is derived, in which the subtours
        are considered as a unique center (thus, in fact, inducing a partition on the nodes) ?

        If we solve this new instance with the complete TSP model, we'll probably find the best way
        to interconnect subtours, and then we'll be able to "reconstruct" a solution for the original problem

        If the new instance is solved without the SEC instead, we'll obtain a "meta-partition", and
        we can iterate this process until the number of nodes makes adding the SEC lighter than the
        original problem, or when the solver naturally finds a connected solution (without being forced to).

The main questions of this heuristic are how to assign the distance (cost) between the partitions from the nodes
that compose them and how to reconstruct a solution for an original instance from a solution of a derived one.

For the first question, the following policies are proposed :

- ### Min distance policy :
        The distance (cost) between two partitions will be the minimum distance (cost) between a node of the  
        first partition and a node of the second one.
- ### Max distance policy :
        The distance (cost) between two partitions will be the maximum distance (cost) between a node of the  
        first partition and a node of the second one.
- ### Average distance policy :
        The distance (cost) between two partitions will be the average of the distances (costs) between the  
        nodes of the first partition the nodes of the second one.

Policies for the reconstruction will be explored later.

## Credits

The MIP solver used for testing this program is HiGHS, see :

- Parallelizing the dual revised simplex method Q. Huangfu and J. A. J. Hall Mathematical Programming Computation, 10 (1), 119-142, 2018. DOI: 10.1007/s12532-017-0130-5