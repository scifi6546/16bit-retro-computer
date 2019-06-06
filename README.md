# nano-com
[![Build Status](https://travis-ci.org/scifi6546/nano-com.svg?branch=master)](https://travis-ci.org/scifi6546/nano-com)
## What is this?
This is a project to build a fictional 16 bit console. It will have a limited amount of memory (lets say 1MB), 
a simple instruction set to make it easy to program, an easy way to share and load games and a screen keyboard and mouse interface.

## Specs of computer
The computer will have 1 MB of addressable ram. An interface for a cartridge and non volatile storage and a cpu with a limited speed.

## Instruction Set
Details still to be determined but I am thinking of having a very simple instruction set. 

## Opcode Format:
A full instruction consists of (except for jmp) two bytes. The first specifies the instruction used and the second byte are 
the arguments of the instruction

## Registers 
There are 4 general purpose registers ra rb rc and rd. These registers can be used for anything. There are two special purpose
registers, sp the stack pointer and of, the offset register.

| Register                 | Opcode             |
| ------------------------ | ------------------ |
| ra (general purpose)     |   000 (0x0)        |
| rb (general purpose)     |   001 (0x1)        |
| rc (general purpose      |   010 (0x2)        |
| rd (general purpose)     |   011 (0x3)        |
| sp (stack pointer)       |   100 (0x4)        |
| of (offset register)     |   101 (0x5)        |
| ip (instruction pointer) |   110 (0x6)        |
| unused                   |   111 (0x7)        |


The width of the opcode is four bits but the opcode shown only takes up three. The first bit specifies whether or not the data at the memory address pointed by the register is used or if the value of the address itself will be used.
for example
```
0000 0011    1000 0001    00000 0000  0000 0000    or in assembly   move  [ra] rb moves the data pointed by ra to rb.
````


## Instruction listing

| Instruction          | Opcode                | Description                      | Arguments                                |
| -------------------- | --------------------- | -------------------------------- | ---------------------------------------- |
| term                 |  0000 0000  (0x00)    | Halts the machine                | None                                     |
| push                 |  0000 0001  (0x01)    | pushs address onto stack         | 1 byte last three bytes contain register |
| pop                  |  0000 0010  (0x02)    | pops address of of stack         | 1 byte last three bytes contain register |`
| move                 |  0000 0011  (0x03)    | moves data                       | 1 byte first 4 bits dest last 4 source   |
| movc                 |  0000 0100  (0x04)    | moves constant into register     | 1st byte register 2 bytes constant       |
| jump                 |  0000 0101  (0x05)    | jumps to memory address          | 2 bytes address to jump too              |
| call                 |  0000 0110  (0x06)    | calls address                    | 2 butes address to jump too              |
| ret                  |  0000 0111  (0x07)    | pops address of of stack into ip | None                                     |
| addu                 |  0000 1000  (0x08)    | adds two registers together      | 1 byte first 4 bits dest last 4 source   |
| adds                 |  0000 1001  (0x09)    | adds signed                      | 1 byte first 4 bits dest last 4 source   |
| sub                  |  0000 1010  (0x0A)    | subtracts to registers           | 1 byte first 4 bits dest last 4 source   |
| je                   |  0000 1011  (0x0B)    | jump if equal                    | 1 byte source and dest registers         |
| jg                   |  0000 1100  (0x0C)    | jump if source is greater        | 1 byte source and dest registers         |
| jl                   |  0000 1101  (0x0D)    | jump if source is less           | 1 byte source and dest registers         |
| int                  |  0000 1110  (0x0E)    | Hardware interrupt               | 2 bytes interrupt number                 |
| intr                 |  0000 1111  (0x0F)    | Hardware interrupt register      | 1 byte register containing interrupt     |

## Offset
Inorder to access the full range of memory sp is used as the first 4 bytes of the regiser.
a typical access operation looks like:
````
sp                        |      register used
0000 0000   00000 MEMORY  | 0110 1101  1110 1111
````
## Instructions Detail

## term
This just terminates the machine.
```
Opcode: 
0000 0000  0000 0000  0000 0000   0000 0000
````

## push
Pushes reg onto stack. sp is incremented by two bytes (by two)
```
opcode:
0000 0001   0000 [reg]  0000 0000   0000 0000
```

## pop
Pops data from stack into register. sp is decremented by two
```
opcode:
0000 0010  0000 [reg] 0000 0000   0000 0000

```

## move
Moves data from one register into another register
```
opcode:
0000 0011 [dest reg][src reg]   0000 0000   0000 0000
```

## movc
Moves constant value into a register
```
opcode:
0000 0100    0000 [dest reg]  [constant value 2 bytes]
```

## jump
jumps to specified address. It sets the ip to the address specified.
```
opcode:
0000 0101 [2 bytes dest address]  0000 0000
```
### Note on jump address
The address used by jump is the index of the first byte of the isntruction jumped to divided by 4. 4 is the width of all opcodes
## call
jumps to a specified address and then pushes next instruction on stack. It pushes the current value of ip+=1
```
opcode:
0000 0110 [2 bytes dest address]   0000 0000
```

## ret
jumps to instruction pushed off of stack. It pushes a value off of the stack into ip and goes to it.
```
opcode:
0000 0111  0000 0000   0000 0000  0000 0000
```
## addu
adds two unsigned registers together. result is stored in dest
```
opcode:
0000 1000 [dest] [src]  0000 0000  0000 0000
```

## adds
adds two signed registers together. result is stored in dest
```
opcode:
0000 1001 [dest] [src]   0000 0000  0000 0000
```
