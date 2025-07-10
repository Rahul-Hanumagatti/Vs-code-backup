age = int(input("Enter age "))  # type conversion from str to int
if age >= 18 :
    print("You can vote")
elif age<18 and age>10:
    print("You are child")
else:
    print("You are kid")
