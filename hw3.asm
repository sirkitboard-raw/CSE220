#Homework #3
#Name : Aditya Balwani
#SBUID : 109353930

.include 

.text
	toRadians:
  		lw $f5, pi
  		li $t0, 180
  		mtc1 $t0, $f5
  		cvt.s.w $f5, $f5
		div.s $f4,$f5,$f6
		mul.s $f0, $f12, $f4
		jr $ra
	
	arcLength:
		jal toRadians
		mul.s $f0, $f12, $f13
		jr $ra