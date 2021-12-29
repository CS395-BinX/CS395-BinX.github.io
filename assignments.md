# Homework Assignments

## Sample Assignment
This is an example of what a homework assignment and its solution would look like.

## Assignment 0
Your goal for this week is to get a shell by exploiting the buffer overflow. Remember to turn off ASLR! Submit a PDF writeup that explains how and why your exploit works, and make sure you include a screenshot in your submission.

- Download it from [here](???)

- Get the solution [here](???)

## Assignment 1
For this assignment, you will have to exploit the following binary using a format string vulnerability. Submit a PDF writeup that explains how and why your exploit works, and make sure you include a screenshot in your submission.

- Download it from [here](???)

- Get the solution [here](???)

## Assignment 2
Goal is to get a shell by exploiting a buffer overflow. Open up the binary in Ghidra to find the vulnerability. ASLR can be turned off for this assignment.

- Download it from [here](???)

- Get the solution [here](???)

# Assignment 3
You'll have to submit an exploit that works when ASLR is turned on.

- Download it from [here](???)

- Get the solution [here](???)

# Assignment 4
This problem must be solved with ASLR ON!! Additionally, to make the binary run you must run:

"source ./setup"

This will not survive a reboot, so you'll have to run it again every time you restart your VM.

Your goal is to get a shell by calling the win function with the proper arguments. Without 3 global variables being set correctly, the win function will simply exit the program. It looks like there's some secret functions for setting the global variables, maybe calling those with the proper arguments will allow win() to give you a shell? You can safely ignore libcs395.so, you must download it so "source ./setup" works do not need to interact with it to complete the assignment, it houses the implementation of the win() function.

- Download it from [here](???)

- Get the solution [here](???)
