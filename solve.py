#!/usr/bin/env python3

def euclid_decomp(a: int, b: int) -> ([int],[int]):
    vals = [a,b]
    coefs = [1]
    while b != 0:
        v = a % b
        c = a // b
        a = b
        b = v
        vals += [v]
        coefs += [c]
    assert vals[-1] == 0
    vals = vals[:-1]
    coefs = coefs[:-1]
    return vals, coefs

def bezout(coefs: [int]) -> (int,int):
    arr = [0] * len(coefs)
    arr[-1] = -coefs[-1]
    arr[-2] = 1
    i = len(arr) - 1
    while i > 1:
        arr[i-2] += arr[i]
        arr[i-1] += arr[i] * -coefs[i-1]
        i -= 1
    return arr[0], arr[1]

a = int(input("enter a: "))
b = int(input("enter b: "))
c = int(input("enter c: "))

vals,coefs = euclid_decomp(a,b)

d = vals[-1]
a_prime = a // d
b_prime = b // d
c_prime = c // d

if c % d != 0:
    print(f"{a}x + {b}y = {c} has no solution")
    exit(1)

u,v = bezout(coefs)

# this problem is in P
assert vals[0]*u + vals[1]*v == vals[-1]

print("S = { " + f"({u*c_prime} + ({b_prime})k, {v*c_prime} - ({a_prime})k) : k em Z" + " }")
