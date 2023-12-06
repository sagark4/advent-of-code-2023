# Advent of Code 2023
My solutions and commentary for Advent of Code 2023 event.

This needs `clang` (or if you have `gcc`, change the appropriate setting in `Makefile`). Then to run place all input files as, e.g., for Day 1 in two-digit format as `~/input/01.txt`, then

```
make all
make run_all
```

## Day 1

My goal was to write a one-pass solution.  For the first part, it was straight-forward to move character-by-character, store the first and the last occurrence of a digit (a single character), compute the "calibration value" after seeing the end-of-line character, and add it to the maintained sum.

After reading Part 2, my first instinct was to find indices of all the possible newly valid digits (like "one", "two", etc.) and actual digits (0, 1, etc.), and find a minimum and maximum index and corresponding digits.  But obviously this went againts the principle of a simple one-pass solution.  I decided to do the hard work and just maintain the history of last four characters seen and do a one-pass solution.  In the process, I managed to also cleanly separate two parts.

## Day 2

I quickly realized this would be a nightmare in C, so I coded-up a quick and dirty Python solution to get stars (same for Day 3), and then worked on my C solution.  My goal was to still write a one-pass solution, and that would need a stream processor, which I wrote in `psed`.  It basically replaces any pattern by substitution as soon as it sees it (in the order given).  Then I also had to use my dynamic-array for maintaining a dynamic list of plays in a dynamic list of games.  Fortunately I had this already implemented for my `clox` [project](https://github.com/sagark4/clox) (which I just started): [see Crafting Interpreters by Robert Nystrom](https://craftinginterpreters.com/contents.html).  This was a massive day, and I might stop doing this advent-of-code stuff in C if there is such heavy string processing in the future days.  It's just too time consuming.

## Day 3

I read and stored the input in a 2-D `char` array.  For Part 1, I created a `bool` 2-D array storing if the cell is next to a non-dot symbol.  Then in the third pass, I parsed the number maintaining an OR of non-dot symbol flags, and adding it to the maintained sum if the flag is true.  For Part 2, I maintained a dynamic array of integers for each `*` cell which was populated while parsing the number.  I used a function called `get_valid_neighbors()` for a given cell.

## Day 4

I have yet to do Day 3 in C, but Day 4 was easy enough to be done directly in C.  It was easy to `scanf` the input into temporary arrays and do two for loops to compute matches (for Part 1).  I am sure there is some Fenwick tree trick to do Part 2 faster, but I'll live with my solution of just keeping an array of copies and then updating the counts one-by-one.

## Day 5

As expected, input parsing in C took longer than coding up the logic.  Part 1 was basically passing the integers through the seven maps.  Part 2 was passing intervals through these maps.  This involved using `qsort()` in `stdlib.h`, because intervals must be sorted to process from left-to-right.  Running time is $O($ max-number-of-intervals $)$.

## Day 6
One can just brute-force it out, but I used the binary search approach to first find a valid solution and then separately to find lower and upper bounds on valid solutions.
