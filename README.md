### Runtime Environment
1. At least 3GB Memory Available.
2. Ubuntu 12.04.4
3. g++ 4.6.3 with -std=c++0x

### Warning
1. In run.sh, use "main.exe" instead of "./main" if using windows.
2. In run_tests.sh, use "diff -w" instead of "diff" to ignore different line endings between windows and linux.

### New feature
It is reasonable to trigger a warning for the sender if the amount of money is greater than a certain value. This message should be like this:
* "unverified: The amount of money you want to send is too large. Are you sure you would like to proceed with this payment?"

In this project, I set the maximum value without triggering this warning is 50.0 because 99th percentile of money in all transactions is around 49.0.

### Format of transaction records
The record of each transaction is comma-delimited and must contain these five parts: time, sender, receiver, money, message. Otherwise, the system will print this incomplete record and throw an error:
* "Error: Data is not clean or incomplete."

### Data Structure
A finite graph is used to record the whole friendship network. Each vertex in this graph is a user. Each edge in this graph represents one transaction between two users.

Use **adjacency list** to represent this graph. One list describes the set of 1st-degree friends of one vertex in this graph. Another list describes the set of 2nd-degree friends of one vertex in this graph. In C++, the unordered map is used to store this adjacency list in the memory.

Hash Map:

                 Key            Value

               User ID  ---> List of 1st-degree friends.

                        ---> List of 2nd-degree friends.

### Algorithm
Update the graph for each new edge between user A and user B as depicted below:

             ________new 2nd friend_____________
            |                    new 1st friend |
    1st-degree list of A  ---  A  -----------   B   ---   1-st degree list of B
                               |______________new 2nd friend_____________|


Implement **Breadth-First Search (BFS) from two directions**: sender and receiver. So two 2nd-degree lists of two users are enough to decide if one is inside of 4th-degree list of another one. Follow the order of the following five conditional statements to decide if this transaction is "trusted" or "unverified".

* 0-degree: A is same as B.

* 1-degree: B is in 1st-degree list of A.

* 2-degree: B is in 2nd-degree list of A.

* 3-degree: 1st-degree list of B intersects with 2nd-degree list of A.

* 4-degree: 2nd-degree list of B intersects with 2nd-degree list of A.


### Scalable Issue
1. It is very easy to extend the above definition of adjacency list to include 3rd-degree friend list.
2. Space Complexity: O(n*m^2), where n is the number of users and m is the average number of 1st-degree friend of one user.  
3. Time Complexity: If user A has sent money to user B before, then a new transaction between them will not update the graph. Thus the size of this graph is predictable.
4. Parallelization: Split transactions into mutiple groups.  

### Execution Time
Around 6 minutes in total. (CPU: Intel Core i5-3210M)
