We need to overflow the value of the variable `[esp+0x3c]` to set it at `0x574f4c46`. It's stored just after our buffer of 40 bytes.

The problem is that we have we have to give an int as argument to the program to calculate to size to read from our input. This int must be less than **9**. To obtain a size superior to **40** we are going to overflow `INT_MIN` to get the size we want once multiply by **4**.
We need **4 bytes** for our address in our payload, so our targeted size will be **44**.

*44 == -2147483637 * 4*
```shell
./bonus1 "-2147483637" $(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')
```
