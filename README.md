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

The main question of this heuristic is how to assign the distance between the partitions from the nodes
that compose them, which will be further explored.