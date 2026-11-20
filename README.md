# Function Tabulation Program (Variant 14)

Console application in C++ that calculates and tabulates a piecewise function over a range [a, b] with a fixed step.

## Formula

- If x < -4: y = Prod(j=-1..3, (j+2)*x) + 3 * Sum(i=3..n, 12i + 1/x)
- If x >= -4: y = Sum(i=0..n+1, Prod(j=1..n-3, (i + j + i/j)^2))

## Input constraints

- a and b are real numbers, b >= a
- step > 0
- n is an integer, n >= 5

## Features

- Input validation with retry / exit to main menu
- Formatted table of results
- Built-in formula info screen

## Build and run

Open `Lab2Melnyk.slnx` in Visual Studio and press Ctrl+F5.

## Project management

Work is planned with GitHub milestones (iterations), epics and subtasks. Defects are tracked with the `Bug` label and fixed in separate branches via pull requests.
