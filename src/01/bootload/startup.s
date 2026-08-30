    .syntax unified
    .cpu cortex-m4
    .thumb

    .section .text
    .global start
    .type   start, %function

start:
    bl      main

1:
    b       1b
