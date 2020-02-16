# totty
Tool for emulating interactive user activity in terminal applications

Not to be confused with: 
totty - girls or women regarded collectively as objects of sexual desire.
"the group on the table next to us were blatantly checking out the totty"

# You probably can use it if you want to:

- create test cases for interactive terminal applications (like htop or shell...)
- automate any other sort of user terminal activity

# Installation
```sh
git clone https://github.com/ag95v2/totty.git
cd totty 
make
```

# Usage

Totty has 2 operating modes: record mode and play mode.
In record mode you can record a "testcase" (sequence of keypresses and pauses) into a file. Command syntax below.
```sh
./totty -r -o file1
```
In play mode you can attach to running process or create new process and redirect a "testcase" to stdin of that process.
Testcase can be taken from file or recorded interactively. If testcase is taken from file, it is possible to speedup execution.

Typical examples that illustrate play mode command syntax:
```sh
# take testcase from file1, speedup 10 times and redirect to stdin of PID
./totty --file file1 --speedup 10 --attach PID
 
# interactively redirect input to stdin of PID
./totty -i  -a PID 

# take testcase from file1, run command with args arg1 and arg2 
# and redirect this testcase to stdin of new process
./totty -f file1  --cmd command arg1 arg2
```
Note that play mode requires root permissions.

# Future plans
- Clever management of stopping condition. Right now just press 'q'
- Child process always runs with root privilegies which is usually not desired
