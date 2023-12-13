import numpy as np
import cv2
import pickle

def load_image(file_path):
    image = np.load(file_path)
    return image

def apply_convolution(images, kernel, stride=1, padding=0):
    '''
    Implement 2D Convolution Using Numpy
    =================================================================================================
    Arguments:
        + images: np.array of shape (B, input_H, input_W)
        + kernel: np.array of shape (kernel_H, kernel_W)
        + stride: integer
        + padding: integer
    Outputs:
        + output_images: np.array of shape (B, input_H, input_W)
    '''
    ### TODO: fill in here ###
    images = np.pad(images,((0,0),(padding,padding),(padding,padding)))/255.
    # print(images.shape
    # print(images.shape)
    output_images = []
    # for image in images:
    #     output_images.append(cv2.filter2D(image, -1,kernel ) )#cv2.flip(kernel, -1), borderType=cv2.BORDER_CONSTANT

    kernel_H, kernel_W = kernel.shape
    n,H,W = images.shape
    out_h = (H-kernel_H)//stride +1
    out_w = (W-kernel_W) // stride + 1
    # print(out_h,out_w)
    output_images = np.zeros((n,out_h,out_w))
    kernel = np.array([kernel])
    for i in range(out_h):
        for j in range(out_w):
            # print(i,j)
            output_images[:,i,j] = np.sum(images[:,i*stride:i*stride+kernel_H, j*stride :j*stride+kernel_W]*kernel,axis = (1,2))

    
    # print(output_images.shape)
    return np.array(output_images)


if __name__ == "__main__":

    input_file_path = "input_image.npy"

    input_images = load_image(input_file_path)
    num_images = input_images.shape[0]


    # Sobel filter
    sobel_x = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]])
    sobel_y = np.array([[-1, -2, -1], [0, 0, 0], [1, 2, 1]])

    result_x = apply_convolution(input_images, sobel_x, stride=1, padding=1)
    result_y = apply_convolution(input_images, sobel_y, stride=1, padding=1)

    # Combine the results
    result = np.sqrt(result_x**2 + result_y**2)
    
    '''
    =================================================================================================
    Save and submit a portion of the processed 32 images. 
    You are free to choose any number of images (recommend 4~8)."
    '''
    # print(np.mean(result_x),np.mean(result_y))
    result_x = np.sqrt(result_x**2)
    result_y = np.sqrt(result_y**2)
    
    for i in range(result.shape[0]):
        result[i] = (result[i]/np.max(result[i]) * 255 ).astype(np.uint8)
        result_y[i] = (result_y[i]/np.max(result_y[i]) * 255 ).astype(np.uint8)
        result_x[i] = (result_x[i]/np.max(result_x[i]) * 255 ).astype(np.uint8)
        cv2.imwrite(f"result/{i}.png",result[i])
        cv2.imwrite(f"result_x/{i}.png",result_x[i])
        cv2.imwrite(f"result_y/{i}.png",result_y[i])
    import random
    from matplotlib import pyplot as plt 
  
# create figure 
    fig = plt.figure(figsize=(10, 7)) 
    
    # setting values to rows and column variables 
    rows = 2
    columns = 2
    saved = result[:4]
    # saved = saved.astype(np.uint8)
    fig.add_subplot(rows, columns, 1) 
  
# showing image 
    plt.imshow(saved[0],cmap='gray')
    plt.axis('off')
    plt.title("First") 
    
    # Adds a subplot at the 2nd position 
    fig.add_subplot(rows, columns, 2) 
    
    # showing image 
    plt.imshow(saved[1],cmap='gray') 
    plt.axis('off') 
    plt.title("Second") 
    
    # Adds a subplot at the 3rd position 
    fig.add_subplot(rows, columns, 3) 
    
    # showing image 
    plt.imshow(saved[2],cmap='gray') 
    plt.axis('off') 
    plt.title("Third") 
    
    # Adds a subplot at the 4th position 
    fig.add_subplot(rows, columns, 4) 
    
    # showing image 
    plt.imshow(saved[3],cmap='gray') 
    plt.axis('off') 
    plt.title("Fourth") 
    plt.savefig("result.png")
    # plt.show()



