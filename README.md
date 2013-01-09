# Advanced C Lecture Notes

This repository contains the example code/notes for Advanced C, taught by David Greenberg at MIT over IAP 2010-2013.

## Typedefs

Here, we the conventions for declaring structs, including struct foo_s, foo_t, and foo_p. We also look at designated initializers for structures, including how they nest. In addition, we see how little protection typedefs give us against coding bugs.

## Special Types

Here, we learn about bitfields, enums, and unions. Bitfields are a way to write structs whose fields have specific numbers of bits. We look at the use of anonymous unions to create discriminated unions. Finally, we look at other union techniques.

## Functions

This file demonstrates inner functions in GCC, which can be used as a limited closure. We also see some quirks of function pointers, and learn about cdecl.

## Jump Table

Combining the knowledge from the previous sections, we make a jump table, which is a function that is able to dynamically dispatch on an arbitrary value. We look at making them with switch statements, arrays of function pointers, and using the GCC-specific feature to goto an address in a variable. We also look at case ranges, which can often replace the need for if-else chains.

## Macros

We look at basic macro usage and common pitfalls, including how to create new symbols/mangle symbols in a macro and how to avoid accidentally evaluating agruments multiple times.

## X-Macros

We apply a cool macro technique for replicating lists to write a more elegant goto-based jump table.

## Attributes (GCC)

In this file, we discuss the following GCC attributes: aligned, packed, always_inline, const, pure, and deprecated.
