# Homework Assignments

## Sample Assignment
This is an example of what a homework assignment and its solution would look like.

- Download it from [here](https://github.com/CS395-BinX/CS395-BinX.github.io/tree/main/assignments/asst4/solution)

## Assignment 0
Your goal for this week is to get a shell by exploiting the buffer overflow. Remember to turn off ASLR! Submit a PDF writeup that explains how and why your exploit works, and make sure you include a screenshot in your submission.

- Download it from [here](https://github.com/CS395-BinX/CS395-BinX.github.io/tree/main/assignments/asst0)

- Get the solution [here](https://github.com/CS395-BinX/CS395-BinX.github.io/tree/main/assignments/asst0/solution)

## Assignment 1
For this assignment, you will have to exploit the following binary using a format string vulnerability. Submit a PDF writeup that explains how and why your exploit works, and make sure you include a screenshot in your submission.

- Download it from [here](https://github.com/CS395-BinX/CS395-BinX.github.io/blob/main/assignments/asst1/asst1)

- Get the solution [here](https://github.com/CS395-BinX/CS395-BinX.github.io/blob/main/assignments/asst1/solution/asst1%20solution.pdf)

## Assignment 2
Goal is to get a shell by exploiting a buffer overflow. Open up the binary in Ghidra to find the vulnerability. ASLR can be turned off for this assignment.

- Download it from [here](https://github.com/CS395-BinX/CS395-BinX.github.io/tree/main/assignments/asst2)

- Get the solution [here](https://github.com/CS395-BinX/CS395-BinX.github.io/tree/main/assignments/asst2/solution)

# Assignment 3
You'll have to submit an exploit that works when ASLR is turned on.

- Download it from [here](https://github.com/CS395-BinX/CS395-BinX.github.io/blob/main/assignments/asst3/asst3)

- Get the solution [here](https://github.com/CS395-BinX/CS395-BinX.github.io/tree/main/assignments/asst3/solution)

# Assignment 4
This problem must be solved with ASLR ON!! Additionally, to make the binary run you must run:

"source ./setup"

This will not survive a reboot, so you'll have to run it again every time you restart your VM.

Your goal is to get a shell by calling the win function with the proper arguments. Without 3 global variables being set correctly, the win function will simply exit the program. It looks like there's some secret functions for setting the global variables, maybe calling those with the proper arguments will allow win() to give you a shell? You can safely ignore libcs395.so, you must download it so "source ./setup" works do not need to interact with it to complete the assignment, it houses the implementation of the win() function.

- Download it from [here](https://github.com/CS395-BinX/CS395-BinX.github.io/tree/main/assignments/asst4)

- Get the solution [here](https://github.com/CS395-BinX/CS395-BinX.github.io/tree/main/assignments/asst4/solution)
