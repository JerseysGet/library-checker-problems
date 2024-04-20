# Library Checker Problems

Forked from [yosupo06/library-checker-problems](https://github.com/yosupo06/library-checker-problems) to stress test my solutions.

## Requirements

- Linux / OS X / Windows(MinGW-w64)
- python3.6+
- g++ / clang++ (Needs --std=c++17 and __int128_t)

## How to Use (Running Tests)

```sh
cd /path/to/library-checker-problems

pip3 install -r requirements.txt
# or pip3 install colorlog

ulimit -s unlimited # for linux (doesn't need for OS X and WSL)

./tester.sh # to test all problems in the script
./tester.sh math/convolution_mod datastructure/staticrmq # to test specific problems 
```

## How to Use (Testing new problems)
Create the directory structure for the problem in `/path/to/library-checker-problems/mine`, and create the file `driver.cpp` in it, with the code for that problem.

Add this problem to `PROBLEMS` in [`tester.sh`](https://github.com/JerseysGet/library-checker-problems/blob/master/tester.sh) along with the other problems, or pass it as a command line arugment to `tester.sh`

Example:
```sh
cd /path/to/library-checker-problems
mkdir -p mine/datastructure/persistent_queue
touch mine/datastructure/persistent_queue/driver.cpp # code for the problem 'persistent_queue'
```
Add the line `PROBLEMS+=( "datastructure/persistent_queue" )` to [`tester.sh`](https://github.com/JerseysGet/library-checker-problems/blob/master/tester.sh) with the other problems OR run `./tester.sh datastructure/persistent_queue`

## Thanks

We use [testlib](https://github.com/MikeMirzayanov/testlib) for verifier(input-checker) and output-checker.
We use [toml](https://github.com/uiri/toml) as toml paser.
