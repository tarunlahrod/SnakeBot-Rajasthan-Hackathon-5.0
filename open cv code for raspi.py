import numpy as np
import cv2

face_cascade=cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
fgbg=cv2.createBackgroundSubtractorMOG2()
cap=cv2.VideoCapture(0)

while True:
    ret,frame=cap.read()
    gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    fgmask=fgbg.apply(frame)
    faces = face_cascade.detectMultiScale(gray,1.3,5)
    hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    lower_green=np.array([60,20,90])
    upper_green=np.array([120,250,255])

    mask = cv2.inRange(hsv,lower_green,upper_green)
    for (x,y,w,h) in faces:
        cv2.rectangle(frame,(x,y),(x+w,y+h),(233,99,122),2)
    cv2.imshow('img',frame)
    cv2.imshow('fgmask',fgmask)
    cv2.imshow('mask',mask)
    k=cv2.waitKey(30) & 0xFF
    if k ==27:
        break
cap.release()
cv2.destroyAllWindows()
# this whole code ends on pressing escape
