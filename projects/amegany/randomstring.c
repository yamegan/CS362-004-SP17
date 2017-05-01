//Random Tester: testme()
/*
In order to run the program such that the error is eventually found, I did the following. The inputChar() function was 
straight forward in that it simply returns a random character from the string "[({ ax})]" which are characters 
determined to be compatible with the c variable in testme(). The inputString() function first selects a random integer.
If that integer is 0 then the function returns "reset" which trigger the error in testme(). The random integer is set to select
a value between 0-9 to ensure that there is a high probability of triggering the error. If not 0, the function loops through
the random string variable 'randStr' filling it with random characters, and then returns the random string.
*/
