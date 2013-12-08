#!/usr/bin/python

import os, sys, time, datetime

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

if len(sys.argv) < 3:
   print  'Usage : ./read_position.py <start> <end>'
   sys.exit(1)

start = int(sys.argv[1])
end = int(sys.argv[2])

X_MIN = 0
X_MAX = 4000
Y_MIN = 0
Y_MAX = 4000


#Video settings
fps = 7
video_name = "myworld.mp4"
start_frame = str(start) # not supported yet
end_frame = str(end)     # not supported yet
bit_rate = 9000000
######

fin_root = './DATA/'

x_dict = dict()
y_dict = dict()
dim_dict = dict()
x_fp_dict = dict()
y_fp_dict = dict()
nutri_dict = dict()


default_nutrival = 100
food_magnify = 1

for gen in range(start,end + 1):

   print "Getting positions for generation = " , gen
   fgen = open(fin_root + str(gen) + '.txt_b_pos','r')
   f_fp_gen = open(fin_root + str(gen) + '.txt_fp_pos','r')
   line = 'init'
   xlist = []
   ylist = []
   x_fp_list = []
   y_fp_list = []
   dimlist = []
   nutrilist = []

   while line:
      line = fgen.readline()
      if line.find('==') == -1:
         linesp = line.split()
         if len(linesp) == 3 : 
            x = float( linesp[0].strip().rstrip() )
            xlist.append(x)
            y = float( linesp[1].strip().rstrip() )
            ylist.append(y)
            dim = float( linesp[2].strip().rstrip() )
            dimlist.append(dim)
   line = ' '
   while line:
      line = f_fp_gen.readline()
      if line.find('==') == -1:
         linesp = line.split()
         if len(linesp) == 3 :
            x = float( linesp[0].strip().rstrip() )
            x_fp_list.append(x)
            y = float( linesp[1].strip().rstrip() )
            y_fp_list.append(y)
            nutri = float( linesp[2].strip().rstrip() ) / default_nutrival * food_magnify
            if nutri < 1: nutri = 1
            nutrilist.append(nutri)

   fgen.close()
   f_fp_gen.close()
   x_dict[gen] = xlist
   y_dict[gen] = ylist 
   dim_dict[gen] = dimlist
   x_fp_dict[gen] = x_fp_list
   y_fp_dict[gen] = y_fp_list 
   nutri_dict[gen] = nutrilist

#print x_fp_dict, y_fp_dict, nutri_dict
#fout = open (foutx_root + str(gen),'w')
#xstring = ' '
#for x in xlist:
#   xstring = xstring + str(x) + ' '
#fout.write("# name: xpos\n# type: matrix\n# rows: 1\n# columns: " + str(len(xlist)) + '\n')
#fout.write(xstring + '\n')
#fout.close()

#fout = open (fouty_root + str(gen),'w')
#ystring = ' '
#for y in ylist:
#   ystring = ystring + str(y) + ' '
#fout.write("# name: ypos\n# type: matrix\n# rows: 1\n# columns: " + str(len(ylist)) + '\n')
#fout.write(ystring + '\n')
#fout.close()

SAVE = True
PLOT = False

for gen in x_dict.keys():
   print "Creating frame for generation = ", gen
   plt.figure()
   plt.title("AGE = " + str(gen))
   plt.xlim(X_MIN, X_MAX)
   plt.ylim(Y_MIN, Y_MAX)
   #print x_dict[gen], y_dict[gen], dim_dict[gen]
   scat = plt.scatter(x_dict[gen], y_dict[gen], dim_dict[gen], c='b', marker='o')
   scat = plt.scatter(x_fp_dict[gen], y_fp_dict[gen], nutri_dict[gen] , c='r', marker='+')
   if PLOT : plt.show()
   if SAVE:
      plt.savefig(fin_root + str(gen) + '.png')
      plt.clf()

print "Creating the video ..."
cmd = "avconv -y -r " + str(fps) + " -b " + str(bit_rate) + " -i DATA/%d.png " + video_name
print "CMD = ", cmd
status = os.system(cmd)
print "status = ", status
#fig = plt.figure()

#def update_plot(i):
#   scat = plt.scatter(x_dict[i],y_dict[i], s=1, c='b', marker='o')
#   return scat,
  
#def setup_plot():
#   x0 = [0,800]
#   y0 = [0,800]
#   scat = plt.scatter(x0,y0, s=1, c='b', marker='o')
#   return scat,

#ani = animation.FuncAnimation(fig, update_plot, init_func=setup_plot, repeat_delay=2000, frames=273, blit=True, repeat=True)
##ani.save('basic_animation.mp4', fps=30)
#plt.show()
