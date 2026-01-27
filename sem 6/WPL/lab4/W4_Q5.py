class TwoSum:
    def find_pair(self, numbers, target):
        lookup = {}
        for i, num in enumerate(numbers):
            if target - num in lookup:
                return lookup[target - num], i
            lookup[num] = i


obj = TwoSum()
numbers = [10, 20, 10, 40, 50, 60, 70]
target = 80
print(obj.find_pair(numbers, target))
