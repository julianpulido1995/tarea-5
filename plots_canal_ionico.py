import numpy as np
import matplotlib.pyplot as plt

canal = np.loadtxt('Canal_ionico.txt')
canal1 = np.loadtxt('Canal_ionico1.txt')
xcanal = np.loadtxt('xcanal.txt')
ycanal = np.loadtxt('ycanal.txt')
xcanal1 = np.loadtxt('xcanal1.txt')
ycanal1 = np.loadtxt('ycanal1.txt')
r = np.loadtxt('radius.txt')
r1 = np.loadtxt('radius1.txt')

plt.figure()
counts3, bins3,ig3 = plt.hist(xcanal,20, normed = True)
plt.title('Histograma coordenada x, canal_ionico.txt')  
plt.grid()
plt.savefig('histx.png')
plt.close()

plt.figure()
count1, bins1, ignored1 =plt.hist(ycanal,20, normed = True)
plt.title('Histograma coordenada y, canal_ionico.txt')  
plt.grid()
plt.savefig('histy.png')
plt.close()

c1 = plt.Circle((xcanal[np.argmax(r)],ycanal[np.argmax(r)]), np.amax(r), color = 'g', fill = False)
fig, ax = plt.subplots()
plt.grid()
plt.xlabel('x(A)')
plt.ylabel('y(A)')
plt.title(' Parametros: x = 3.149397, y = 5.432353, r = 6.611686 ')
ax.scatter(canal[:,0],canal[:,1])
ax.plot(xcanal[np.argmax(r)],ycanal[np.argmax(r)],'ro')
ax.add_artist(c1)
fig.savefig('canal.png')
plt.close()

plt.figure()
counts3, bins3,ig3 = plt.hist(xcanal1,20, normed = True)
plt.title('Histograma coordenada x, canal_ionico1.txt')  
plt.grid()
plt.savefig('histx1.png')
plt.close()

plt.figure()
count1, bins1, ignored1 =plt.hist(ycanal1,20, normed = True)
plt.title('Histograma coordenada y, canal_ionico.txt')  
plt.grid()
plt.savefig('histy1.png')
plt.close()


c2 = plt.Circle((xcanal1[np.argmax(r1)],ycanal1[np.argmax(r1)]), np.amax(r1), color = 'g', fill = False)
fig, ax = plt.subplots()
plt.grid()
plt.xlabel('x(A)')
plt.ylabel('y(A)')
plt.title('Parametros: x = 7.135665 , y = 5.90313, r = 6.060202')
ax.scatter(canal1[:,0],canal1[:,1])
ax.plot(xcanal1[np.argmax(r1)],ycanal1[np.argmax(r1)],'ro')
ax.add_artist(c2)
fig.savefig('canal1.png')

