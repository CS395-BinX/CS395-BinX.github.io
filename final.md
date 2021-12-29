# Final Project
For your final project, you are given multiple binaries that are worth different points. You do not have to exploit every single binary in order to get 100% on this assignment. This assignment will be graded out of 50 points, and your goal is to exploit enough binaries so that you get all 50 points. For example, you could do two 15 point problems and one 20 point problem to get your 50 points. Or you could do two 25 point problems to get your 50 points. You'll pick and choose which binaries you want to exploit, and you'll have to submit a writeup for every binary that you select.

Note that patching a binary is prohibited unless we give you explicit permisison to patch that binary. Some problems require ASLR to be enabled and some do not require ASLR to be enabled. If the problem does not specify whether ASLR must be enabled or not, you can assume that your exploit does not need to work while ASLR is enabled. We may periodically add extra problems as time goes on. You may receive up to 10 points extra credit if you obtain more than 50 points.

# Problems:

## 10 points
- [Patch Me](???)

As the name implies, you are allowed to solve this binary by patching it. This is the only binary you are allowed to solve via patching.

- [Flip Me](???)

Flipping bits is fun!

## 15 points
- [Cha-Cha Slide](???)

Everybody clap your hands!

- [Buyshell](???)

Your goal for your exploit is to obtain enough money to buy a shell

## 20 points
- [Deadbeef](???)

Typical stack buffer overflow. Note that there is a special integer that you must input at the start of your payload.

- [Format's Last Theorem](???)

I bet [Pierre de Fermat](https://www.britannica.com/science/Fermats-last-theorem) didn't know anything about format string vulnerabilities! Your goal here is to disprove Fermat's Last Theorem (not in real life though—just in the binary 🙂). Your exploit should work with ASLR enabled.

## 25 points
- [Guessing Game](???)

For this binary, you'll have to exploit a buffer overflow and a format string vulnerability at the same time. This binary introduces the concept of input validation, which is when a program checks to make sure that the input does not contain any characters that cause the program to behave differently (such as the '%' or '$' characters in format strings). Your goal here is to get the program to say, "you guessed <number>, which is correct!" You'll have to create an exploit that works when ASLR is enabled.

- [Nihaal's Revenge](???)

Have you guys heard of the sweet new game *Nihaal's Revenge*??? I really want to play it, but i don't have enough money to buy a copy of my own! I found the part of the game that checks if you have a valid CD key for owning the game, could you guys find me a key that calls the win() function and lets me play the game? (Recommend using Z3, watch week 9 lecture first)

## 30 points
- [Final Boss](???)

Defeat the final boss and get the victory message to print. ASLR does not need to be enabled. You must use a ROP chain with at least two ROP gadgets to obtain full credit.

- [Calculator](???)

This is a calculator program that is vulnerable to a stack buffer overflow. You'll have to write an exploit that works when ASLR is enabled for this binary.

## Nihaal's Heap Challenge (60 points)
- Challenge [here](???)

This exploit requires you to conduct a heap overflow, which is something that we have never gone over in our lectures. You will have to do some research on your own in order to get your exploit to work. ASLR must be enabled for this challenge. This is an extremely tough binary to exploit, which is why if you are able to submit a writeup for this binary, you will instantly get an A for your final project. Good luck for those who choose to exploit this binary!

