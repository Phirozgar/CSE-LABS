class Power:
    def my_pow(self, x, n):
        if n == 0:
            return 1
        if n < 0:
            return 1 / self.my_pow(x, -n)
        return x * self.my_pow(x, n - 1)


obj = Power()
print(obj.my_pow(2, 3))
