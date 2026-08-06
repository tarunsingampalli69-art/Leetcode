class Solution:
    def smallestNumber(self, n: int, t: int) -> int:
        x = n
        while True:
            prod = 1
            for d in str(x):
                prod *= int(d)
            if prod % t == 0:
                return x
            x += 1