echo "Rahul Hanumagatti"
echo "I am Rahul"

#!/bin/bash
for i in 1 2 3 4 5
do
  echo "Number: $i"
done

#!/bin/bash
if [ -f myscript.sh ]; then
  echo "File exists"
else
  echo "File does not exist"
fi
