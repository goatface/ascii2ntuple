This is a primitive basis for solving a Sudoku puzzle.

To run it, call `root in.C'

The example puzzle was typed manually into puzzle1.txt from the topmost example https://en.wikipedia.org/wiki/Sudoku

The example puzzle was then converted to a root tree of TNtuple via `.x ascii2ntuple(9,"puzzle1.txt") inside ROOT yielding puzzle1.txt.root

A symlink was made as `ln -s puzzle1.txt.root 0.root` so we don't need to deal with the file name inside of ROOT code.

The primitive solver can be invoked by `root in.C' which must finally be modified near the bottom to actually solve the puzzle.
