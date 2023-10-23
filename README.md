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

Moving to the second question, the following two policies are proposed :

- ### Min reconstruction :
        Given a metamodel indicating, for every partition, which partition has to connect to it and which
        partition it has to connect to, the following is done for each partition :
          
          1.  The best entrance node and the best exit node, the node in the partition associated
              with the lower cost arc of the ones starting from the "previous" partition and ending into the 
              current one,
              and the node in the partition associated with lower cost arc of the ones starting from the
              current partition and ending into the "next" one, respectively, are found

          2.  The arcs in the partition that connect to the entrance node and from the exit one are removed
              thus splitting the partition in two sequences

          3.  The entrance node and the node in the previous partition such that the connection
              cost is the lowest are connected, and the exit node and the node in the next partition that respect
              the just aforementioned criterium are connected, too

          4.  The sequence not containing the entrance and exit nodes, let us call it "A", is reattached to the
              other one, let's call it "B" by finding the two nodes in B for which the cost gained from attaching
              them to sequence A's ends minus the cost for removing the arc between them is the most profitable
        
        This reconstruction policy has a problem when the best entrance node and best exit node are the same:
        in that case the best solution may seem to reevaluate the chosen nodes for the partition finding the
        second best entrance and exit nodes and changing one of them with the second best in the most profitable
        way, but that may create domino effects (because it will change the indexes on the other partitions, too)
        that might be cyclical (yet to be proved). The solution in this case is a reevaluation in which the second
        bests are found maintaining the nodes in the nearby partitions unchanged (so they will be the second bests
        with respect to the best exit/entrance node of the previous/next partition)
- ### Saving reconstruction :
        The base idea of this reconstruction policy is to remove from every partition an arc, leaving an entrance
        node and an exit one "open", and then using them to connect to the partition between them.
        Finding the optimal arcs to remove ends up being quite an heavy problem, so the strategy adopted starts
        from a partition and removes the arc for which the lowest cost for the connection of the "exit" node
        to the next partition minus such arc's cost is the most profitable, then the arc in the entering into the
        "entrance" node in the next partition will be removed and the "exit" node created after the removal
        will be connected to the most profitable node in the next partition and so on until the last partition
        is reached: in that case the connection with the first partition is forced to the node left free after
        the first arc's removal. This constraint, on a worst case scenario, will activate the highest cost arc
        between the last and the first partition. This leads to a sub-policy for starting arc selection:
          
        "The selected arc will be the one for which the the "saving" obtained by removing it and connecting its
        nodes to the lowest cost node in the next partition and to the higher cost node in the previous
        is the most profitable"


## Credits

The MIP solver used for testing this program is HiGHS, see :

- Parallelizing the dual revised simplex method Q. Huangfu and J. A. J. Hall Mathematical Programming Computation, 10 (1), 119-142, 2018. DOI: 10.1007/s12532-017-0130-5