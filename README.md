# BStree
[![Build Status](https://travis-ci.org/Kirichenkov9/BStree.svg?branch=master)](https://travis-ci.org/Kirichenkov9/BStree)

**This is a project of realization Binary Search tree**

In this project are realized the following opportunities:

* displaying the tree on the screen
* displaying the list of tree nodes (3 orders: pre, in, post)
* adding a node to the tree
* removing the node from the tree
* saving the tree to the file
* loading the tree from the file
* existing of node


## Building of a project:
```ShellSession
$ cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=install
$ cmake --build _build --target install
```

**Run the test:**
```ShellSession
$ cmake -H. -B_build -DBUILD_TESTS=ON
$ cmake --build _build --target install
$ cmake --build _build --target test -- ARGS=--verbose
```

**Run the examples:**
```ShellSession
$ cmake -H. -B_build -DBUILD_EXAMPLES=ON
$ cmake --build _build --target install
$ cd _build
$ ./example<number>
 ```
## Benchmark

The benchmark of each open method is 10, 10 ^ 2, 10 ^ 3, 10 ^ 4, 10 ^ 5, 10 ^ 6, 10 ^ 7, 10 ^ 8 and 10^9 elements.


|Operations|Print|Print pre order|Print in oreder|Print post order|Insert|Remove|Exist|Save in file|Load from file|
|---|---|---|---|---|---|---|---|---|---|
|10|8.7e-05|1e-05| 2e-06|3e-06|2.2e-05|6.3e-05|3e-06|6.7e-05|1.8e-05|
|10^2|0.000267|9e-06|9e-06|1.3e-05|4.8e-05|7.8e-05|2.9e-05|6e-06|1e-05|
|10^3|0.002548|9.3e-05| 9.3e-05|0.000144|0.000767|0.001234|0.000593|0.000787|0.00113|
|10^4|0.01828|0.000945|0.000993|0.001237|0.007021|0.011167| 0.002335|0.00113|0.002797|
|10^5|0.16331|0.01251|0.012897|0.012694|0.052942|0.093658|0.030821|0.029051|0.036695|
|10^6|1.77104|0.171983|0.17855|0.17935| 0.834816| 1.62604|0.80937|0.158951 |0.486303|
|10^7|23.9118| 1.86464|1.96248|2.05967|14.5264|30.3793|15.6677|1.7185|5.55034|
|10^8|283.915|24.4839|24.4839|24.601|244.531|485.906|241.978|21.2049| 68.3128|
|10^9|:x:|:x:|:x:|:x:|:x:|:x:|:x:|:x:|:x:|

*All values in the table are expressed in seconds
