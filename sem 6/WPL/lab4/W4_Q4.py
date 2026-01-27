class Subsets:
    def get_subsets(self, nums):
        result = [[]]
        for num in nums:
            result += [curr + [num] for curr in result]
        return result


obj = Subsets()
print(obj.get_subsets([4, 5, 6]))
