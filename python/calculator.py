first = int(input("Enter first "))
second = int(input("Enter second "))
operator = input("Enter operator" )

if operator == '+':
    print(first+second)
elif operator == '-':
    print(first-second)
elif operator == '*':
    print(first*second)
elif operator == '/':
    print(first/second)
else:
    print("Invalid operator")
    
