import numpy as np
import cv2 as cv
cap = cv.VideoCapture(0)
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
    formateFrame = cv.cvtColor(frame, cv.CV_8U)

    #Get frame height and width to access pixels
    height, width, channels = frame.shape

    #Accessing BGR pixel values    
    for x in range(0, width) :
        for y in range(0, height) :
            print (formateFrame[x,y,0]) #B Channel Value
            print (formateFrame[x,y,1]) #G Channel Value
            print (formateFrame[x,y,2]) #R Channel Value

    # Display the resulting frame
    cv.imshow('frame', formateFrame)
    if cv.waitKey(1) == ord('q'):
        break
# When everything done, release the capture
cap.release()
cv.destroyAllWindows()