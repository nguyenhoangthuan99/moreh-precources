import numpy as np
import cv2
import argparse

def normalize(img):
    new_img = (img - img.min()) / (img.max() - img.min()) * 255.0
    return new_img

def L_transform_vertical(image):
    H,W = image.shape
    new_image = np.zeros((H//2,W))
    for i in range(H//2):
        for j in range(W):
            new_image[i][j] = (image[2*i][j] + image[2*i+1][j])/2**0.5
    return new_image

def L_transform_horizontal(image):
    H,W = image.shape
    new_image = np.zeros((H,W//2))
    for i in range(H):
        for j in range(W//2):
            new_image[i][j] = (image[i][2*j] + image[i][2*j+1])/2**0.5
    return new_image

def H_transfrom_vertical(image):
    H,W = image.shape
    new_image = np.zeros((H//2,W))
    for i in range(H//2):
        for j in range(W):
            new_image[i][j] = (image[2*i][j] - image[2*i+1][j])/2**0.5
    return new_image

def H_transfrom_horizontal(image):
    H,W = image.shape
    new_image = np.zeros((H,W//2))
    for i in range(H):
        for j in range(W//2):
            new_image[i][j] = (image[i][2*j] - image[i][2*j+1])/2**0.5
    return new_image

def normalize(image):
    min_ = np.min(image)
    max_ = np.max(image)
    normalized = (image - min_)/(max_-min_)
    return (normalized*255).astype(np.uint8)

def haar_wavelet_transform(img, depth=1):
    """
    IMPLEMENT THIS FUNCTION
    """
    new_img = np.copy(img)
    result = np.zeros_like(img).astype(np.uint8)
    for i in range (1,depth+1):
        L = L_transform_vertical(new_img)
        H = H_transfrom_vertical(new_img)
        LL = L_transform_horizontal(L)
        LH = H_transfrom_horizontal(L)
        HL = L_transform_horizontal(H)
        HH = H_transfrom_horizontal(H)
        h,w = LL.shape
        result[:h,:w] = normalize(LL)
        result[h:2*h,:w] = normalize(HL) 
        result[:h,w:2*w] = normalize(LH) 
        result[h:2*h,w:2*w] = normalize(HH) 
        new_img = LL


    return result


def main(args):
    image = cv2.imread(args.input, cv2.IMREAD_GRAYSCALE).astype(np.float32)
    transformed_image = haar_wavelet_transform(image, depth=args.depth)
    cv2.imwrite(args.output, transformed_image)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', type=str, required=True, help='input image path')
    parser.add_argument('--output', type=str, required=True, help='output image path')
    parser.add_argument('--depth', type=int, required=True, help='depth of Haar wavelet transform')
    args = parser.parse_args()
    main(args)