from math import sqrt, acos, cos, pi, floor
import numpy as np

def ColorRGB2HSI(r, g, b):
  r, g, b = int(r), int(g), int(b)

  epsilon_rgb = 0 if (r+g+b) != 0 else 0.0001
  r_n, g_n, b_n = r/(r+g+b+epsilon_rgb), g/(r+g+b+epsilon_rgb), b/(r+g+b+epsilon_rgb)

  m = min([r_n, g_n, b_n])
  i = (r+g+b)/(3*255)

  denum=(sqrt((r_n-g_n)**2+(r_n-b_n)*(g_n-b_n)))
  epsilon_theta = 0 if denum != 0 else 0.0001
  theta = (0.5*((r_n-g_n)+(r_n-b_n)))/(denum+epsilon_theta)
  h = acos(theta) if b_n <= g_n else 2*pi - acos(theta)

  s = 1 - 3*m
  h, s, i = h*(180/pi), s*100, i*255

  return h, s, i

#calculate alpha beta and gamma (x y z here respectively)S
def calc_xyz(h_n, s_n, i_n):
  x = i_n*(1-s_n)
  y = i_n*(1+((s_n*cos(h_n))/(cos(pi/3-h_n))))
  z = 3*i_n-(x+y)

  return x, y, z

def ColorHSI2RGB(h, s, i):
  h, s, i = float(h), float(s), float(i) #to convert np.uint8 to float
  h_n , s_n , i_n = h*(pi/180), s/100, i/255

  if(h_n < 2*pi/3): 
    x, y, z = calc_xyz(h_n, s_n, i_n)
    r_n, g_n, b_n = y, z, x
  elif(2*pi/3 <= h_n and h_n < 4*pi/3): 
    h_n = h_n - 2*pi/3
    x, y, z = calc_xyz(h_n, s_n, i_n)
    r_n, g_n, b_n = x, y, z
  elif(4*pi/3 <= h_n and h_n < 2*pi):
    h_n = h_n - 4*pi/3
    x, y, z = calc_xyz(h_n, s_n, i_n)
    r_n, g_n, b_n = z, x, y

  r, g, b = round(r_n*255), round(g_n*255), round(b_n*255)
  return r, g, b

def ImageRGB2HSI(img):
  assert (img is not None), "An error occured while reading the image!"

  width, height, _ = img.shape
  new_img = img.astype(np.float64)

  assert (new_img is not None), "An error occured while copying the image!"

  for x in range(width):
    for y in range(height):
      rgb = [None, None, None]

      for k in range(3):
        rgb[k] = img[x][y][k]

      r, g, b = rgb #numpy.uint8
      h, s, i = ColorRGB2HSI(r, g, b)

      hsi = [h, s, i]
      for k in range(3):
        new_img[x][y][k] = hsi[k] #implicitly casted to numpy.uint8

  return new_img

def ImageHSI2RGB(img):
  assert (img is not None), "An error occured while reading the image!"

  width, height, _ = img.shape
  new_img = img.astype(np.uint8) 

  assert (new_img is not None), "An error occured while copying the image!"

  for x in range(width):
    for y in range(height):
      hsi = [None, None, None]

      for k in range(3):
        hsi[k] = img[x][y][k]

      h, s, i = hsi
      r, g, b = ColorHSI2RGB(h, s, i)
      rgb = [r, g, b]

      for k in range(3):
        new_img[x][y][k] = rgb[k]
  
  return new_img    