## The Great Sort-Off

### Analysis of Performance Data

| Sorting Type | Time Spent (ms) | Comparisons | Swaps |
|----------|----------|----------|----------|
| **Selection Sort (List)** | 5912.51 | 12497500 | 4984 |
| **Selection Sort (Array)** | 5557.33 | 12497500 | 4984 |
| **Bubble Sort** | 11603.7 | 24585082 | 6268619 |
| **Quick Sort** | 44.8545 | 102968 | 32563 |
| **Merge Sort** | 39.5851 | 50810 | 0 |

NOTE:
The table above consists of results from a randomly generated dataset using the *CompareLastName* callback. Merge sort's 0 swaps is because it builds a new list from scratch instead of swapping elements.

In the table there is a clear difference between the O(n^2) and O(n log n) algorithms. The three first lines are using O(n^2) algorithms. For this data n is ~5000.
With this value for n, we can calculate that n^2 is 25 million, which Bubble Sort's 24.6 million comparisons closely match, while Selection Sort's 12.5 million comparisons is roughly equal to n^2/2.
When calculating n log n we get ~61 000, which Quick Sort's 103 000 comparisons and Merge Sort's 51 000 comparisons are in the same range. Quick Sort's number will be in the higher range, as it treats an equal element the same as a greater element. This makes splits uneven, and increases both comparisons and swaps.
The result of this is clearly shown in the time usage, as the O(n^2) algorithms use seconds, while the O(n log n) algorithms use ~40 ms.

Selection Sort was harder to write for a linked list than for an array because you can't easily go back and forth through a linked list. You also can't directly swap the data in a linked list, you have to go through the nodes, which makes it harder to implement.

### Linear vs Binary Search
| Algorithm | Time Spent (ms) | Comparisons |
| --------- | --------------- | ----------- |
| **Binary Search** | 0.0045 | 8 |
| **Linear Search** | 1.8394 | 2983 |

NOTE: The account searched for was at index 4000 in the sorted array. Both searches match on last name (*CompareLastName*), so they may return different accounts with the same last name. The linear search runs on the unsorted list, while the binary search runs on the sorted array.