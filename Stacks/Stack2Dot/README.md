# Stack2Dot

``` sh
/*******************************************************************
                Stack2Dot

    1.  struct in C (for describing the data structure of Stack)

    2.  How to Visualize Stack Operations

                                             COMP9024

 *******************************************************************/
``` 
This project is designed to visualize stack operations.

More details will be discussed in [COMP9024/Graphs/Dot2Png](../../Graphs/Dot2Png/README.md).


## 1 How to download this project in [CSE VLAB](https://vlabgateway.cse.unsw.edu.au/)

Open a terminal (Applications -> Terminal Emulator)

```sh

$ git clone https://github.com/sheisc/COMP9024.git

$ cd COMP9024/Stacks/Stack2Dot

Stack2Dot$ 

```


## 2 How to start [Visual Studio Code](https://code.visualstudio.com/) to browse/edit/debug a project.


```sh

Stack2Dot$ code

```

Two configuration files (Stack2Dot/.vscode/[launch.json](https://code.visualstudio.com/docs/cpp/launch-json-reference) and Stack2Dot/.vscode/[tasks.json](https://code.visualstudio.com/docs/editor/tasks)) have been preset.



### 2.1 Open the project in VS Code

In the window of Visual Studio Code, please click "File" and "Open Folder",

select the folder "COMP9024/Stacks/Stack2Dot", then click the "Open" button.


### 2.2 Build the project in VS Code

click **Terminal -> Run Build Task**


### 2.3 Debug the project in VS Code

Open src/Int2Str.c, and click to add a breakpoint (say, line 71).

Then, click **Run -> Start Debugging**



### 2.4 Directory

```sh
├── Makefile             defining set of tasks to be executed (the input file of the 'make' command)
|
├── README.md            introduction to this tutorial
|
├── src                  containing *.c and *.h
|    |
|    ├── Int2Str.c       print an integer as a string (based on a stack)
|    ├── Int2Str.h
|    ├── main.c          main()
|    ├── Stack.c         the implementation of an array-based stack
|    └── Stack.h         the header file of the stack
|
|
└── .vscode              containing configuration files for Visual Studio Code
    |
    ├── launch.json      specifying which program to debug and with which debugger,
    |                    used when you click "Run -> Start Debugging"
    |
    └── tasks.json       specifying which task to run (e.g., 'make' or 'make clean')
                         used when you click "Terminal -> Run Build Task" or "Terminal -> Run Task"
```
Makefile is discussed in [COMP9024/C/HowToMake](../../C/HowToMake/README.md).


## 3 How to visualize stack operations

### 3.1 make && ./main

**In addition to utilizing VS Code, we can also compile and execute programs directly from the command line interface as follows.**

``` sh

Stack2Dot$ make

Stack2Dot$ ./main

```
### 3.2 make view

**Click on the window of 'feh' or use your mouse scroll wheel to view images**.

```sh
Stack2Dot$ make view
```

Here, **feh** is an image viewer available in [CSE VLAB](https://vlabgateway.cse.unsw.edu.au/).


||
|:-------------:|
| <img src="images/Stack_0000.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0001.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0002.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0003.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0004.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0005.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0006.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0007.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0008.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0009.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0010.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0011.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0012.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0013.png" width="80%" height="80%"> |


||
|:-------------:|
| <img src="images/Stack_0014.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0015.png" width="80%" height="80%"> |



||
|:-------------:|
| <img src="images/Stack_0016.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0017.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0018.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0019.png" width="80%" height="80%"> |



||
|:-------------:|
| <img src="images/Stack_0020.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0021.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0022.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0023.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0024.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0025.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0026.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0027.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0028.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0029.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0030.png" width="80%" height="80%"> |

||
|:-------------:|
| <img src="images/Stack_0031.png" width="80%" height="80%"> |






