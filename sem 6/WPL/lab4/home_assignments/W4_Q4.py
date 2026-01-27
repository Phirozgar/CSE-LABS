class ParenthesesValidator:
    def is_valid(self, s):
        stack = []
        mapping = {')': '(', '}': '{', ']': '['}

        for char in s:
            if char in mapping.values():
                stack.append(char)
            elif char in mapping:
                if not stack or stack.pop() != mapping[char]:
                    return False

        return not stack

validator = ParenthesesValidator()
print(validator.is_valid("()[]{}"))   # True
print(validator.is_valid("({[)]"))    # False
