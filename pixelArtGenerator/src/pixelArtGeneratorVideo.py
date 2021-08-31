import numpy as np
import cv2 as cv
cap = cv.VideoCapture(0)
#cap = cv.VideoCapture('pics/woman.mp4')

if not cap.isOpened():
    print("Cannot open camera")
    exit()
while True:
    # Capture frame-by-frame
    ret, frame = cap.read()
    # if frame is read correctly ret is True
    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        break
    # Our operations on the frame come here
    formatedFrame = cv.cvtColor(frame, cv.CV_8U)

    #Get frame height and width to access pixels
    heightOriginal, widthOriginal, channels = formatedFrame.shape
    originalDim = (widthOriginal,heightOriginal)
    fourcc = cv.VideoWriter_fourcc('M', 'J', 'P', 'G')
    out = cv.VideoWriter('outpy.avi',fourcc, 25, originalDim, True)

    scale_percent = 10# percent of original size
    width = int(formatedFrame.shape[1] * scale_percent / 100)
    height = int(formatedFrame.shape[0] * scale_percent / 100)
    dim = (width, height)
  
    # resize image
    resized = cv.resize(formatedFrame, dim, interpolation = cv.INTER_NEAREST)
    

    #Accessing BGR pixel values    
    for x in range(0, height) :
        for y in range(0, width) :
            pixel = resized[x,y,0] #B Channel Value
            pixel = int(pixel * 0x7 / 0xFF)
            pixel = pixel * 0xFF / 0x07
            resized[x,y,0] = pixel

            pixel = resized[x,y,1] #G Channel Value
            pixel = int(pixel * 0x7 / 0xFF)
            pixel = pixel * 0xFF / 0x07
            resized[x,y,1] = pixel

            pixel = resized[x,y,2] #R Channel Value
            pixel = int(pixel * 0x7 / 0xFF)
            pixel = pixel * 0xFF / 0x07
            resized[x,y,2] = pixel
  
    # resize image
    resized2 = cv.resize(resized, originalDim, interpolation = cv.INTER_NEAREST)

    # Display the resulting frame
    cv.imshow('frame', resized2)
    out.write(resized2)
    if cv.waitKey(1) == ord('q'):
        break
# When everything done, release the capture
out.release()
cap.release()
cv.destroyAllWindows()