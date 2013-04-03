chronosync-sqlite: sync library for multiuser applications for NDN (with persistent SQLite storage of the state)
================================================================================================================

1. ChronoSync
-------------
ChronoSync is a library that allows you to synchronize state of a dataset.

The usage of this library is very simple. You just needs to specify the dataset you want to synchronize and what to do when the library tells you new data is added to the dataset.

2. Build and Install
--------------------
To see more options, use `./waf configure --help`.
For default install, use
```bash
./waf configure
./waf
sudo ./waf install
```

### If you're using Mac OS X, Macport's g++ is not recommended. It may cause mysterious memory error with tinyxml. Use clang++ or Apple's g++ instead.

Normally, default install goes to /usr/local.
If you have added /usr/local/lib/pkgconfig to your `PKG_CONFIG_PATH`, then you can compile your code like this:
```bash
g++ code.cpp `pkg-config --cflags --libs libchronoshare-sqlite`
```

3. Examples
-----------
You can find examples in /test directory, which could be a starting point.
There is example of this library in [ChronoShare](https://github.com/named-data/ChronoShare).


