class StringClass:
    def get_String(self):
        self.string = input("Enter a string: ")

    def print_String(self):
        print(self.string.upper())

obj = StringClass()
obj.get_String()
obj.print_String()