# Advent of Code 2023
My solutions and commentary for Advent of Code 2023 event

## Day 1

My goal was to write a one-pass solution.  For the first part, it was straight-forward to move character-by-character, store the first and the last occurrence of a digit (a single character), compute the "calibration value" after seeing the end-of-line character, and add it to the maintained sum.

After reading Part 2, my first instinct was to find indices of all the possible newly valid digits (like "one", "two", etc.) and actual digits (0, 1, etc.), and find a minimum and maximum index and corresponding digits.  But obviously this went againts the principle of a simple one-pass solution.  I decided to do the hard work and just maintain the history of last four characters seen and do a one-pass solution.  In the process, I managed to also cleanly separate two parts.

## Day 2

I quickly realized this would be a nightmare in C, so I coded-up a quick and dirty Python solution to get stars (same for Day 3), and then worked on my C solution.  My goal was to still write a one-pass solution, and that would need a stream processor, which I wrote in `psed`.  It basically replaces any pattern by substitution as soon as it sees it (in the order given).  Then I also had to use my dynamic-array for maintaining a dynamic list of plays in a dynamic list of games.  Fortunately I had this already implemented for my `clox` [project](https://github.com/sagark4/clox) (which I just started): [see Crafting Interpreters by Robert Nystrom](https://craftinginterpreters.com/contents.html).  This was a massive day, and I might stop doing this advent-of-code stuff in C if there is such heavy string processing in the future days.  It's just too time consuming.
