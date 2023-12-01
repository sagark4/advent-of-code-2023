# advent-of-code-2023
My solutions and commentary for Advent of Code 2023 event

## Day 1

My goal was to write a one-pass solution.  For the first part, it was straight-forward to move character-by-character, store the first and the last occurrence of a digit (a single character), compute the "calibration value" after seeing the end-of-line character, and add it to the maintained sum.

After reading Part 2, my first instinct was to find indices of all the possible newly valid digits (like "one", "two", etc.) and actual digits (0, 1, etc.), and find a minimum and maximum index and corresponding digits.  But obviously this went againts the principle of a simple one-pass solution.  I decided to do the hard work and just maintain the history of last four characters seen and do a one-pass solution.  In the process, I managed to also cleanly separate two parts.
