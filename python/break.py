students = ["Rahul" , "Chidu", "Vishnu", "Mahesh", " Vikram"]
for student in students:
    print(student)
    if student == "Vishnu":
        break   # break the loop


for student in students:
    if student == "Vishnu":
        continue   # break the loop
    print(student)