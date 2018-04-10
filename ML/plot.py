import numpy as np    
import matplotlib.pyplot as plt  
from matplotlib.lines import Line2D  
  
x = [6.2, 9.5, 10.5, 7.7, 8.6, 6.9, 7.3, 2.2, 5.7, 2.,  
        2.5, 4., 5.4, 2.2, 7.2, 12.2, 5.6, 9., 3.6, 5.,  
        11.3, 3.4, 11.9, 10.5, 10.7, 10.8, 4.8]  
y = [29., 44., 36., 37., 53., 18., 31., 14., 11., 11.,  
        22., 16., 27., 9., 29., 46., 23., 39., 15., 32.,  
        34., 17., 46., 42., 43., 34., 19.]  
  
fig = plt.figure()  
ax = fig.add_subplot(111)  
ax.set_title('Linear Regression')  
plt.xlabel('X')  
plt.ylabel('Y')  
ax.scatter(x,y,c = 'r',marker = 'o')  
  
line1 = [(0.0, 6.0506), (40, 137.5202)] # least squares  
line2 = [(0, 1.68624), (40, 154.01864)] # gradient descent  
  
(line1_xs, line1_ys) = zip(*line1)  
(line2_xs, line2_ys) = zip(*line2)  
  
ax.add_line(Line2D(line1_xs, line1_ys, linewidth=2, color='green')) # least squares  
ax.add_line(Line2D(line2_xs, line2_ys, linewidth=2, color='yellow')) # gradient descent  
  
plt.show()  