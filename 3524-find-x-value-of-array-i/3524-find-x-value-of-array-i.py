class Solution:
    def resultArray(self, A: List[int], k: int) -> List[int]:
        res = [0] * k
        freq = [0] * k

        for n in A:
            cur = [0] * k
            newX = n % k
            cur[newX] = 1

            for x, c in enumerate(freq):
                cur[x * newX % k] += c

            freq = cur
            for x, c in enumerate(freq):
                res[x] += c

        return res