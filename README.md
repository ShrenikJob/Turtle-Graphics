# Turtle Graphics for Terminal
Program that draws out images on the terminal from commands such as: Draw, move, rotate, background colour, etc; which is written on a text (.txt) file.

![DiamondCommand](https://user-images.githubusercontent.com/48969261/196026255-93e14e9b-7d0c-4bac-bcc2-05cefed017c5.PNG)


**I have made it very easy to follow here with simple words and easy steps!**

# 1) Description of Project
This project uses the C programming language to read commands from a text file and then draw an image on the terminal!!

The commands for making the Pokemon character **Charizard** and a **diamond** is provided.

**Image of the Pokemon Charizard:**

![charizard](https://user-images.githubusercontent.com/48969261/196024395-43f34c9f-3e86-43ea-923d-c47f495549a5.jpg)

# 2) Getting Started
To run the code in C, first we need to get the environment.

## NOTE:

- If you are using Linux, just open a terminal and run the following commands. 
- If you using Windows, get the Linux Terminal from Microsoft Store (search up on Google if you don't know how to get around this).

## Follow the steps to get started:

#### i) Git clone the repository:

#### ii) Install the C compiler:

```shell
$ sudo apt update
$ sudo apt install build-essential
```

#### iii) Now to run the code:

- There are two types of files: TurtleGraphics and TurtleGraphicsSimple.
- TurtleGraphics has colour whereas the TurtleGraphicsSimple does not have colour.

**To Run TurtleGraphics:**

```shell
$ make TurtleGraphics
$ ./TurtleGraphics charizard.txt
$ ./TurtleGraphics diamond.txt
```
**To Run TurtleGraphicsSimple:**

```shell
$ make TurtleGraphicsSimple
$ ./TurtleGraphicsSimple charizard.txt
$ ./TurtleGraphicsSimple diamond.txt
```

# We are done!!


