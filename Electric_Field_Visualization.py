# Daniel Loo
# 2/3/2015
# This program generates a given number of point charges to represent a rod
# and displays arrows around the charges to represent the electric field 
# at locations of interest to 3D visualize the electric field

from __future__ import division
from visual import *
scene.width = 1024
scene.height = 768
scene.x = scene.y = 0

# constants
k = 9e9 #Coulumb's constant
L = 9 # Length of the rod
Q = 3e-10 # Uniform charge of the rod
N = 20 # Number of charges
scalefactor = .25
dz = L/N # Change in length of rod, depends on the number of charges
dQ = Q/N # Distribution of total charge on each point charge of the rod
R = .5

# list of charges, the loop creates and places them in a linear order to represent a rod
list_of_charges = []
z = -L/2 + dz/2
while z < L/2:
    list_of_charges.append(sphere(pos=(0,0,z), radius=.1, color=color.green))
    z = z+dz
print(len(list_of_charges))  ## print number of items in list

# list of arrows; tail of each arrow is at an observation location
dzz = ((10/8)*L)/10 #change in z axis location
list_of_arrows = []
for z in arange(-5*L/8, 5*L/8+.001, dzz): # Iterate through the length of the rod
    for theta in arange(0,2*pi, pi/4):
        list_of_arrows.append(arrow(pos=(R*cos(theta), R*sin(theta),z),
                                    axis=(0,1,0)))
        
list_of_arrows2 = []
for z in arange(R/2, (10*R)/2, 1/2):
        list_of_arrows.append(arrow(pos=(0, z , 0),
                                    axis=(0,1,0)))

###############################################################
## calculation of field

for thisarrow in (list_of_arrows):  ## take arrows one at a time
    rate(10)
   

    # Sets Enet (the field at tail of thisarrow) to a zero vector
    Enet = vector(0,0,0)
    
    # Loops over list of charges
    for thischarge in list_of_charges:
         
        # Calculate dE, the field due to the current charge, at the observation location (tail of arrow)
        r = thisarrow.pos - thischarge.pos 
        dEtc = (k * dQ )/ (mag(r)**2) * (r / mag(r)) # formula for an electric field at location r from the charge
            
        #  Sums dE to Enet at this observation location
        Enet = Enet + dEtc
            
        # Adds the effect of the electric field on the arrows and redisplays them
        thisarrow.axis = Enet*scalefactor
        thisarrow.color = color.magenta
