echo "*** tests starting"

for i in TestSuite/*.pas
do
   echo "testing $i";  more $i > $i.out; ./parser < $i >> $i.out
   done

echo "tests finished"
