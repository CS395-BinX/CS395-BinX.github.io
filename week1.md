# Week 1: Introduction, Integer Overflows, and Basic Buffer Overflows

## Introduction Video
[![Watch here](http://img.youtube.com/vi/e3R97JzPrK4/0.jpg)](https://www.youtube.com/watch?v=e3R97JzPrK4)


Click the image to watch the video

## Note About Hardcoded Addresses
Addresses can change between different computers even if ASLR is disabled. This means that the addresses that we use in our lectures may or may not be the same addresses that you'll use if you follow along with us during the lecture. Please do not just copy/paste the code that we give you in the lectures because the addresses that are hardcoded in the exploit may vary. Make sure that you understand how we found each address and what each line of code does.

For this first lecture, the address that is hardcoded in the example_payload.txt file may or may not be the same address that you'll have to use if you redo the buffer overflow by yourself. If it's not the correct address for your system, then using that payload will not work. You'll have to figure out what the address of get_shell() is on your computer (using the method Sam describes in the lecture) and use that address in your payload instead. This will also be true for payloads given in subsequent lectures.

## LECTURE REVISION:
In this lecture I go over how to write payloads to a file using python, but was still still stuck in python2 mode like a caveman. We'll be using python3 in this class.

So, when you want to write a payload in this class, you'll pretty much always want to prepend it with a "b" so python knows you want to be writing actual bytes instead of ASCII encodings. When you want to write your payload to a file, this is how you should do it:

```
Python 3.9.1 (default, Dec  8 2020, 07:51:42) 
[GCC 10.2.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> f = open("payload","wb") # Notice you should include a "b" when opening a file so you can write bytes to it.
>>> f.write(b'A'*13 + b'\xff\xff\xff\x00\x00\x00\x00\x00') # Notice all strings have a "b" in front of them so python knows we want to write bytes not ASCII
```
Also an important reminder:

There is a security feature enabled on the operating system by default called ASLR that randomizes stack addresses every time the binary is run, which can make it harder for us to exploit buffer overflows. We'll talk more about this and other exploit mitigations in week 6, but for now unless otherwise stated, we want to turn it off. To make this easy we put a script in ~/Desktop/CS395/ called aslr.sh. To disable ASLR simply run "./aslr.sh off". Likewise, to turn it on again run "./aslr.sh on". ASLR is automatically reactivated on reboot, so be sure to remember to disable it if you restart your VM. 

## Week 1 Lecture Video
[![Watch here](http://img.youtube.com/vi/TjKoU5lSroY/0.jpg)](https://www.youtube.com/watch?v=TjKoU5lSroY)


Get the slides [here](https://github.com/CS395-BinX/CS395-BinX.github.io/blob/main/week1/Week%201%20Lecture.pdf)

## Demos
[Code examples](https://github.com/CS395-BinX/CS395-BinX.github.io/tree/main/week1) used in the lecture

## Optional Material
[Integer Representation Review](https://cs.wellesley.edu/~cs240/s17/slides/integers.pdf)
Mostly review from CS367, what we care about most for this lecture is signed vs unsigned integer representation.

[x86 Review](https://www.youtube.com/watch?v=75gBFiFtAb8)
If you've forgotten the basics of programming in assembly, watch the following video to get a refresher on it. Note that this video only covers 32-bit assembly, but we will be using 64-bit assembly in our class. Also, keep in mind that we are using intel syntax in this class, where instructions are written in destination comma source format ("MOV EAX, 0x0" instead of "MOV 0x0, EAX").

[Python Crash Course](https://www.youtube.com/watch?v=I2wURDqiXdM)
You don't have to be an expert at Python for this class, but we will eventually be writing scripts in Python around week five. This video will go over everything you need to know about Python to do well in this class. You can skip watching this video if you already know Python.

