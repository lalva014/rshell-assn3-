# rshell
Assignment 2
The purpose of this assignment is contruct a shell in c++

The Bugs: 
  If too many semicolons are input into the shell, the program putputs an out of range error/crash. the reason is the way we take out input from the command. we couldn't found away to make this work. the exit only works after using it multiple times. if you run the program then exit right away. it will exit but you processed by a command such as ls. the termanl will not exit. you have to enter it multiple times in order for it to work. another thing when we try typing echo &. the terminal did not output the & to the termanl. it outputs and out of range vector. the same thing happen with the || but it doesnt iwth the &&. we also notice that it work for the semi. so if we echo ;  it echos just a space. we also found by inputing into the terminal " ls ls", we got an error. Another thing that strtoke. every time we used it, we couldn't figure it out how to delete the allocated memory. if we put as many && with commands and then echo  hello; the terminal would not complie the last hello; 
