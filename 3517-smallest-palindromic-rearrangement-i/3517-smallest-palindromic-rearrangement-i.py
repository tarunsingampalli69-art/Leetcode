class Solution:
    def smallestPalindrome(self, s: str) -> str:
        from collections import Counter
        cnt = Counter(s)
        left = []
        middle = ""

        for ch in "abcdefghijklmnopqrstuvwxyz":
            left.append(ch * (cnt[ch] // 2))
            if cnt[ch] % 2 == 1:
                middle = ch

        left = "".join(left)
        return left + middle + left[::-1]