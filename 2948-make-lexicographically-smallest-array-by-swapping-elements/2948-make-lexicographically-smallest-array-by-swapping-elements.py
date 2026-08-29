from typing import List

class Solution:
    def lexicographicallySmallestArray(self, nums: List[int], limit: int) -> List[int]:
        n = len(nums)
        
        elements = [(nums[i], i) for i in range(n)]
        
        elements.sort()
        
        answer = [0] * n
        
        start = 0 
        
        while start < n:
            end = start
            
            while (
                end + 1 < n
                and elements[end + 1][0] - elements[end][0] <= limit
            ):
                end += 1
            
            indices = []
            
            for i in range(start, end + 1):
                indices.append(elements[i][1])
            
            indices.sort()
            
            for i, index in enumerate(indices):
                answer[index] = elements[start + i][0]
            
            start = end + 1
        
        return answer