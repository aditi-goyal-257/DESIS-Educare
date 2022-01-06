Q1: Baisc operations on linkedlist are done by traversing across the linkedlist. Queue is simulated as a linkedlist with the front of linkedlist being front of queue and back of linkedlist being back of queue. Stack is simulated as a linkedlist with the front of linkedlist being top of stack and back of linkedlist being bottom of stack.

Time complexity:

a. Linkedlist: 
insert_at_start: O(1)
remove_from_start: O(1)
insert_at_end: O(n)
remove_from_end: O(n)
front: O(1)
last: O(n)
traverse: O(n)


b. Stack:
push: O(1)
pop: O(1)
top: O(1)

c. Queue:
push: O(n)
pop: O(1)
front: O(1)

Q3: A dynamic programming question where dp[i][j] represents the number of ways in which the first i elements of the array A can achieve the target j-1000. Now, to calculate dp[i][j], either the A[i-1] had + before it or - befoe it, we need to add dp[i-1][j-A[i-1]] and dp[i-1][j+A[i-1]] to get dp[i][j]. 

Time complexity : O(n*target_range)

Q5: Binary search over answer. See if a particular separation is possible or not and reduce range accordingly. 

Time complexity: O(n log n + nlog(range)) where range is the range of xi's
