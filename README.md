# hmwk1-at3103
hmwk1-at3103 created by GitHub Classroom

The written assignment is added as a .txt file and a .pdf file in the hmwk1-at3103 directory. 

The main program is present in shell.c which provides and exectable w4118_sh on make.

A sample test run of shell.c is provided below: {The output has been formatted/indented for better readability}

w4118@w4118:~/hmwk1-at3103$ ./w4118_sh 

$hsitory
error: No such file or directory

$history
0 hsitory

$/bin/ls
a.out		   OS Homework 1.txt  README.md    shell.c	     test.c
makefile	   output.txt	      session.in   shell_modified.c  test_command.txt
OS Homework 1.pdf  README	      session.out  test		     w4118_sh

$ls

error: No such file or directory


$cd

Error: cd takes a single arg

$cd ../

$/bin/pwd
/home/w4118

$cd hmwk1-at3103

$/bin/pwd
/home/w4118/hmwk1-at3103

$/bin/ls -l
total 1312
-rw-r--r-- 1 w4118 w4118     664 Sep 19 17:34 a.out
-rw-r--r-- 1 w4118 w4118     359 Sep 16 01:30 makefile
-rw-r--r-- 1 w4118 w4118   79680 Sep 19 01:27 OS Homework 1.pdf
-rw-r--r-- 1 w4118 w4118   10099 Sep 19 01:27 OS Homework 1.txt
-rw-r--r-- 1 w4118 w4118     199 Sep 19 22:18 output.txt
-rw-r--r-- 1 w4118 w4118       0 Sep 13 23:20 README
-rw-r--r-- 1 w4118 w4118     239 Sep 19 01:27 README.md
-rw-r--r-- 1 w4118 w4118    1079 Sep 19 22:17 session.in
-rw-r--r-- 1 w4118 w4118    1079 Sep 19 22:17 session.in
-rw-r--r-- 1 w4118 w4118 1172953 Sep 19 22:18 session.out
-rw-r--r-- 1 w4118 w4118    6176 Sep 19 22:12 shell.c
-rw-r--r-- 1 w4118 w4118    8768 Sep 18 19:48 shell_modified.c
-rwxr-xr-x 1 w4118 w4118    6840 Sep 18 20:00 test
-rw-r--r-- 1 w4118 w4118     376 Sep 17 22:46 test.c
-rw-r--r-- 1 w4118 w4118     920 Sep 19 19:31 test_command.txt
-rwxr-xr-x 1 w4118 w4118   14984 Sep 19 22:12 w4118_sh

$/bin/ls -l test.c
-rw-r--r-- 1 w4118 w4118 376 Sep 17 22:46 test.c

$bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C

C

$/bin/ls|/bin/ls|/bin/ls|/bin/ls|/bin/ls|/usr/bin/wc|/bin/ls|/bin/ls|/bin/ls|/bin/ls|/bin/ls|/usr/bin/wc 

     15      19     165


$as|as|DFsdassa|sa

error: No such file or directory


$as|as|/bin/ls

a.out		   OS Homework 1.txt  README.md    shell.c	     test.c
makefile	   output.txt	      session.in   shell_modified.c  test_command.txt
OS Homework 1.pdf  README	      session.out  test		     w4118_sh

$history|/usr/bin/wc

      1       6      33


$history

0 hsitory

1 /bin/ls

2 ls

3 cd

4 cd ../

5 /bin/pwd

6 cd hmwk1-at3103

7 /bin/pwd

8 /bin/ls -l

9 /bin/ls -l test.c

10 bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C|/bin/echo A|/bin/echo B|/bin/echo C

11 /bin/ls|/bin/ls|/bin/ls|/bin/ls|/bin/ls|/usr/bin/wc|/bin/ls|/bin/ls|/bin/ls|/bin/ls|/bin/ls|/usr/bin/wc

12 as|as|DFsdassa|sa

13 as|as|/bin/ls

14 history|/bin/grep hello world

15 history|/usr/bin/grep

16 history|/usr/bin/wc

$history 17

Error: Offsetout of range

$history 16

      1       6      33

$history -c

$history

$history 1

Error: Offsetout of range

$exit

w4118@w4118:~/hmwk1-at3103$ 

       


