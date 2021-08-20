import cv2
import numpy as np
from matplotlib import pyplot as plt
import math
import httplib2

http = httplib2.Http()

cap = cv2.VideoCapture(0);

ret, frame1= cap.read();
ret, frame2= cap.read();

lower_black = np.array([0, 0, 0])
upper_black = np.array([255,255,60])

while (True):

    frame=cv2.GaussianBlur(frame1,(5,5),0)
    hsv=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    mask=cv2.inRange(hsv,lower_black,upper_black)
    edges=cv2.Canny(mask,200,250)
    lines=cv2.HoughLinesP(edges,1,np.pi/180,100,minLineLength= 100,maxLineGap=100)

    diff= cv2.absdiff(frame1,frame2)
    gray = cv2.cvtColor(diff, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (5,5), 0)
    _, thresh = cv2.threshold(blur, 20, 255, cv2.THRESH_BINARY)
    dilated = cv2.dilate(thresh, None, iterations= 3)
    contours,_ = cv2.findContours(dilated, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    if lines is not None:
        for line in lines:
            x1,y1,x2,y2=line[0]

            length=math.sqrt((x1-x2)**2+(y1-y2)**2)
            cv2.line(frame1, (x1, y1),(x2,y2),(0,255,0),2)
   

    for contour in contours:

        M = cv2.moments(contour)
        cX = int(M["m10"] / M["m00"])
        cY = int(M["m01"] / M["m00"])
        (x,y,w,h) = cv2.boundingRect(contour)
        if cv2.contourArea(contour) < 50000:
            continue
        cv2.rectangle(frame1, (x,y), (x+w,y+h), (0,255,0), 2)
        d1 = (x1 - cX) ** 2 + (y1 - cY) ** 2
        d2 = (x2 - cX) ** 2 + (y2 - cY) ** 2

        dis1=math.sqrt(d1)+math.sqrt(d2)
        print("dis1",dis1)

        if length+100<dis1<length+200:
            url = "http://IP1/start"  # Instead of printing the line it will generate an url 
            response, content = http.request(url,"GET")   # As a client it will request for an Url



    cv2.imshow('Frame', frame1)
    

    frame1=frame2
    ret, frame2= cap.read()

    if cv2.waitKey(40)==27:
    	break


cv2.destroyAllWindows()
cap.release()
