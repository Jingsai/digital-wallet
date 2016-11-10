### Runtime Environment
1. At least 4GB Memory.
2. Ubuntu 12.04.4
3. g++ 4.6.3 with -std=c++0x

### Data Structure
Hash Table:

                 Key            Value

               User ID  ---> List of 1st-degree friends.

                        ---> List of 2nd-degree friends.

### Algorithm
Update the network for each new edge between user A and user B.

             _____________new 2nd____________
            |                      new 1st   |
    1st-degree list of A  ---  A   --------   B   ---   1-st degree list of B
                               |______________new 2nd__________________|


* 1-degree: B is in 1st-degree list of A.

* 2-degree: B is in 2nd-degree list of A.

* 3-degree: 1st-degree list of B interects with 2nd-degree list of A.

* 4-degree: 2nd-degree list of B interects with 2nd-degree list of A.

### Execution Time
Around 330-360 seconds. (Intel Core i5-3210M)
