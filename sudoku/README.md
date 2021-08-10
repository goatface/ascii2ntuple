# What is it?
This is a primitive basis for solving a Sudoku puzzle.  To run it, call `root in.C`

# Where is it from?

The example puzzle was typed manually into puzzle1.txt from [https://en.wikipedia.org/wiki/Sudoku](the top most example on Wikipedia)

# What did we do?

The example puzzle was then converted to a root tree of TNtuple via `.x ascii2ntuple(9,"puzzle1.txt")` inside ROOT yielding puzzle1.txt.root

# How are we viewing it in ROOT?

A symlink was made at the command line as `ln -s puzzle1.txt.root 0.root` so we don't need to deal with the file name inside of ROOT code.

# What's next?

The primitive solver can be invoked by `root in.C` which must finally be modified near the bottom to actually solve the puzzle.
