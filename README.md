# mem-utility
Command-line utility for displaying register contents

## How to use
To use this utility, you must enter the start and end addresses of the registers you wish to display. The size of the displayed page must be aligned with the size of the registers being displayed. By default, this size is 32 bits.
``` bash
mem_utility -b 0xA1000000 -e 0xA1000100
Data from regs: A1000000 - A1000100 with reg size: 32
[A1000000] - 0x3041554824
...
[A10000FC] - 0x0000000000
```
If you wish to use a different register display size, use the third argument, -s. The possible values ​​it can take are: 8/16/32/64
``` bash
mem_utility -b 0xA1000000 -e 0xA1000100 -s 64
Data from regs: A1000000 - A1000100 with reg size: 64
[A1000000] - 0x303030303041554824
...
[A10000F8] - 0x000000000000000000
```