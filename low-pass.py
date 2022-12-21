def MinFilter(img, nbhd_size):
  assert (nbhd_size % 2 != 0), "The neighbourhood size must not be even"
  assert (img is not None), "The image is not loaded"

  width, height = img.shape
  padded_width = (width//nbhd_size) * nbhd_size
  padded_height = (height//nbhd_size) * nbhd_size
  new_img = img.copy()

  assert (new_img is not None), "Memory not enough to allocate storage for new image"

  for i in range(((nbhd_size-1)//2), padded_width-((nbhd_size-1)//2)):
    for j in range(((nbhd_size-1)//2), padded_height-((nbhd_size-1)//2)):
      min = 255
      
      for k in range(i-((nbhd_size-1)//2), i+((nbhd_size-1)//2)+1):
        for w in range(j-((nbhd_size-1)//2), j+((nbhd_size-1)//2)+1):
          if img[k][w] < min:
            min = img[k][w]

      new_img[i][j] = min
  
  return new_img

def MaxFilter(img, nbhd_size):
  assert (nbhd_size % 2 != 0), "The neighbourhood size must not be even"
  assert (img is not None), "The image is not loaded"

  width, height = img.shape
  padded_width = (width//nbhd_size) * nbhd_size
  padded_height = (height//nbhd_size) * nbhd_size
  new_img = img.copy()

  assert (new_img is not None), "Memory not enough to allocate storage for new image"

  for i in range(((nbhd_size-1)//2), padded_width-((nbhd_size-1)//2)):
    for j in range(((nbhd_size-1)//2), padded_height-((nbhd_size-1)//2)):
      max = 0
      
      for k in range(i-((nbhd_size-1)//2), i+((nbhd_size-1)//2)+1):
        for w in range(j-((nbhd_size-1)//2), j+((nbhd_size-1)//2)+1):
          if img[k][w] > max:
            max = img[k][w]

      new_img[i][j] = max
  
  return new_img

def MeanFilter(img, nbhd_size):
  assert (nbhd_size % 2 != 0), "The neighbourhood size must not be even"
  assert (img is not None), "The image is not loaded"

  width, height = img.shape
  padded_width = (width//nbhd_size) * nbhd_size
  padded_height = (height//nbhd_size) * nbhd_size
  new_img = img.copy()

  assert (new_img is not None), "Memory not enough to allocate storage for new image"

  for i in range(((nbhd_size-1)//2), padded_width-((nbhd_size-1)//2)):
    for j in range(((nbhd_size-1)//2), padded_height-((nbhd_size-1)//2)):
      sum = 0
      
      for k in range(i-((nbhd_size-1)//2), i+((nbhd_size-1)//2)+1):
        for w in range(j-((nbhd_size-1)//2), j+((nbhd_size-1)//2)+1):
            sum += img[k][w]

      new_img[i][j] = sum/(nbhd_size**2 - 1)
  
  return new_img

def MedianFilter(img, nbhd_size):
  assert (nbhd_size % 2 != 0), "The neighbourhood size must not be even"
  assert (img is not None), "The image is not loaded"

  width, height = img.shape
  padded_width = (width//nbhd_size) * nbhd_size
  padded_height = (height//nbhd_size) * nbhd_size
  new_img = img.copy()

  assert (new_img is not None), "Memory not enough to allocate storage for new image"

  for i in range(((nbhd_size-1)//2), padded_width-((nbhd_size-1)//2)):
    for j in range(((nbhd_size-1)//2), padded_height-((nbhd_size-1)//2)):
      vals = []
      
      for k in range(i-((nbhd_size-1)//2), i+((nbhd_size-1)//2)+1):
        for w in range(j-((nbhd_size-1)//2), j+((nbhd_size-1)//2)+1):
            vals.append(img[k][w])

      new_img[i][j] = vals[len(vals)//2]
  
  return new_img