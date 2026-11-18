### 3b
I chose a singly linked list. I didn't go for a circular list, as there wasn't anything the assignment asked for that made a circular list make sense. All the assignments wanted to traverse the list once, so a circular list was not chosen. I chose a singly linked list over doubly linked as there was no real need to be able to traverse in both directions. The assignment doesn't ask for removing or moving of nodes, which is easier in a doubly linked list, so in order to reduce complexity and save memory I chose a singly linked list.

### 12b
The worst-case scenario for the Find() method will always equal the amount of elements in the list, which is n. This demonstrates a complexity of O(n). When an element wasn't found in the list, it had 5001 comparisons, this is the entire list, aka n, which clearly displays the complexity.

The key difference in flexibility between the Every() method and the PrintEveryAccountInDateRange() function is that the Every() method allows for a lot more. It's not limited to searching by DateRange, and since it returns a list it allows a user to manipulate the data further, as well as printing the data.

It does however, increase complexity, making the code harder to read, and the void* cast won't cause issues when compiled, but can break at runtime.
