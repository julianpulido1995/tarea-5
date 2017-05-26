import numpy as np
import matplotlib.pyplot as plt

#lectura de datos
datos = np.loadtxt('Circuito.txt')
t = datos[:,0]
q = datos[:,1]

#funciones
def likelihood(y_obs, y_m):
    chi_squared = (1.0/2.0)*(sum(((y_obs-y_m)/100)**2)) #evitar que se vaya a cero
    return np.exp(-chi_squared)

def funcion(t,r,c):    
    f = 10.0*c*(1-np.exp((-t)/(r*c)))
    return f

#listas para las iteraciones
rw = np.empty((0)) 
cw = np.empty((0))
lw = np.empty((0))

#valores iniciales
rw = np.append(rw,np.random.random())
cw = np.append(cw,np.random.random())
yo = funcion(t,rw[0],cw[0])
lw = np.append(lw, likelihood(q, yo))

for i in range(20000):
    rprime = np.random.normal(rw[i], 0.1) 
    cprime = np.random.normal(cw[i], 0.1)

    yo = funcion(t, rw[i], cw[i])
    yprime = funcion(t, rprime, cprime)
    
    lprime = likelihood(q, yprime)
    lo = likelihood(q, yo)
    
    alpha = lprime/lo
    
    if(alpha>=1.0):
        rw  = np.append(rw,rprime)
        cw  = np.append(cw,cprime)
        lw = np.append(lw, lprime)
    else:
        beta = np.random.random()
        if(beta<=alpha):
            rw  = np.append(rw,rprime)
            cw  = np.append(cw,cprime)
            lw = np.append(lw, lprime)
            
        else:
            rw = np.append(rw,rw[i])
            cw = np.append(cw,cw[i])
            lw = np.append(lw, lo)
            
#graficas pertinentes
count, bins, ignored =plt.hist(rw, 20, normed=True)
plt.grid()
plt.title('Histograma parametro R')
plt.savefig('histr.png')
plt.close()

count, bins, ignored =plt.hist(cw, 20, normed=True)
plt.grid()
plt.title('Histograma parametro C')
plt.savefig('histc.png')
plt.close()

plt.scatter(rw, -np.log(lw))
plt.xlabel('r')
plt.ylabel('-log(l)')
plt.grid()
plt.title('Likelihood en funcion de r')
plt.savefig('rvsl.png')
plt.close()

plt.figure()
plt.scatter(cw, -np.log(lw))
plt.grid()
plt.xlabel('c')
plt.ylabel('-log(l)')
plt.title('Likelihood en funcion de c')
plt.savefig('cvsl.png')
plt.close()

#parametros optimos y grafica
maxl = np.argmax(lw)
roptimo = rw[maxl]
coptimo = cw[maxl]
mejormodelo = funcion(t,roptimo,coptimo)
plt.figure()
plt.scatter(t,q)
plt.plot(t,mejormodelo,'r', label = 'Ajuste')
plt.grid()
plt.legend(loc = 'upper right', fontsize = 'medium')
plt.xlabel('Tiempo')
plt.ylabel('Carga')
plt.title('Calidad del ajuste, R = 5.9242047589, C = 10.0021147933 ')
plt.savefig('ajuste.png')
plt.close()

