# Tree Tool

This program will display the directory tree in a formatted similar to the tree tool in Linux.


## Compilation

To compile the program, use the following command:

<div dir='ltr'>

    make stree
</div>



The program accepts an optional command-line argument specifying the directory to traverse.
If no directory is provided, it will traverse the current working directory.


To run the program, use the following command:

<div dir='ltr'>

    ./stree [directory]

</div>



Replace [directory] with the path to the directory you want to traverse. 
If no directory is specified, it will traverse the current working directory.


## Output

The program will display an indented hierarchy of files in the specified directory tree. For each file, it will show the following information:

* Permitions, indicating the file type, using the same letters as ls -l command. 
* The  user
* The group.
* The size of the file.
* The file name or directory name.

Directories are displayed with a trailing slash (/) and files without.


## Cleaning

To clean the generated executable, use the following command:
<div dir='ltr'>

    make clean

</div>