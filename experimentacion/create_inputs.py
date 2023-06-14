import numpy as np
import random 
np.random.seed(1337)


for power in range(0, 10):
    n = 1000
    #m = int((n**2-n)/2)
    #m = n
    m = int(n/2) + int(power*55444)
    k = n
    f = open("inputs/input_" + str(m), "w")
    f.write(str(1) + " ")
    f.write(str(n) + " ")
    f.write(str(m) + " ")
    f.write(str(k) + " ")
    f.write(str(1) + " ")
    f.write(str(n) + " ")
    

    for i in range(0,m):
        desde = -1
        hasta = -1
        while hasta==desde:
            desde = random.randint(1,n)
            hasta = random.randint(1,n)

        f.write(str(desde) + " ")
        f.write(str(hasta) + " ")
        l = random.randint(1, 1000)
        f.write(str(l) + " ")
    
    
    for i in range(0,k):
        desde = -1
        hasta = -1
        while hasta==desde:
            desde = random.randint(1,n)
            hasta = random.randint(1,n)

        f.write(str(desde) + " ")
        f.write(str(hasta) + " ")
        l = random.randint(1, 1000)
        f.write(str(l) + " ")
    
    f.close()

    
    
