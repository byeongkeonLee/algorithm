

for i in {4..10}
do
	for((j=1;j<=$i+10;j++))
	do
		echo $i $j > in1.txt
		cat in1.txt
		./a.out < in1.txt >out1.txt
		./2482 < in1.txt >ans1.txt
#		cat in1.txt >> diff.txt
		diff out1.txt ans1.txt >> diff.txt   
	done
done
