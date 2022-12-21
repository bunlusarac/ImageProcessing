def clamp_pixel_value(value):
  if value < 0:
    return 0
  elif value > 255:
    return 255
  else:
    return value

def LaplacianFilter(img, mask=None):
  assert (img is not None), "The image is not loaded"

  width, height = img.shape
  padded_width = (width//3) * 3
  padded_height = (height//3) * 3
  new_img = img.copy()

  assert (new_img is not None), "Memory not enough to allocate storage for new image"

  laplacian_mask = None

  if mask == "variant":
    laplacian_mask = [[1, 1, 1], [1, -8, 1], [1, 1, 1]]
  elif mask == "sobelx":
    laplacian_mask = [[-1, -2, -1], [0, 0, 0], [1, 2, 1]]
  elif mask == "sobely":
    laplacian_mask = [[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]]
  else:
    laplacian_mask = [[0, 1, 0], [1, -4, 1], [0, 1, 0]]

  for i in range(1, padded_width-1):
    for j in range(1, padded_height-1):
      sum = 0

      for k in range(i-1, i+2):
        for w in range(j-1, j+2):
            sum += img[k][w] * laplacian_mask[k-i][w-j] 

      new_img[i][j] = clamp_pixel_value(sum)
  
  return new_img

def LaplacianEnhance(img, filter):
  assert (img is not None), "The image is not loaded"
  assert (filter is not None), "The filter is not loaded"

  img_width, img_height = img.shape
  filter_width, filter_height = filter.shape

  assert (img_width == filter_width and img_height == filter_height, "Image and filter sizes are not matching")
  
  new_img = img.copy()
  
  for i in range(img_width):
    for j in range(img_height):
      new_img[i][j] = img[i][j] - filter[i][j]

  return new_img