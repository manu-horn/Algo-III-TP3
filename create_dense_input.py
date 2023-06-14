import numpy as np

#np.random.seed(1337)

for power in range(5, 7):
    n = 2 ** power
    m = int((n**2-n)/2)
    k = m
    f = open("inputs/input_" + str(n), "w")
    f.write(str(1) + " ")
    f.write(str(n) + " ")
    f.write(str(m) + " ")
    f.write(str(k) + " ")
    f.write(str(1) + " ")
    f.write(str(m) + " ")
    
    
    desde = np.random.randint(1,n-1,m)
    #hasta = np.random.sample(range(1,n-1),m)
    hasta = np.random.randint(1,n-1,m)

    for i in range(0,m):
        f.write(str(desde[i]) + " ")
        f.write(str(hasta[i]) + " ")
        f.write(str(np.random.randint(1,1001)))
    
    desde2 = np.random.randint(1,n-1,k)
    #hasta2 = np.random.sample(range(1,n-1),k)
    hasta2 = np.random.randint(1,n-1,k)

    for i in range(0,k):
        f.write(str(desde2[i]) + " ")
        f.write(str(hasta2[i]) + " ")
        f.write(str(np.random.randint(1,1001)))
    
    f.close()

    
    
