import cv2
import numpy as np
import serial
import time
ser = serial.Serial('COM4', 9600) 
cap = cv2.VideoCapture(1)
#11in to 12in
while True:
    ret, frame = cap.read()
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
 # Thresholds for red color
    lower_red = np.array([160, 50, 200]) #highered the saturation values becasue it was reading my lips. Highered the "value" value because it was reading too dark
    upper_red = np.array([180, 255, 255])
    red_mask = cv2.inRange(hsv, lower_red, upper_red)

    # Thresholds for green color
    lower_green = np.array([45, 50, 50])
    upper_green = np.array([75, 255, 255])
    green_mask = cv2.inRange(hsv, lower_green, upper_green)

    # Thresholds for purple color
    lower_pur = np.array([130, 50, 150])
    upper_pur = np.array([155, 255, 255])
    purple_mask = cv2.inRange(hsv, lower_pur, upper_pur)

    # Combine the masks
    combined_mask = cv2.bitwise_or(cv2.bitwise_or(red_mask, green_mask), purple_mask)

    contours, _ = cv2.findContours(combined_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    if len(contours) > 0:
        c = max(contours, key=cv2.contourArea)
        x, y, w, h = cv2.boundingRect(c)
        if w > 50 and h > 50:
            
            if np.sum(red_mask[y:y+h, x:x+w]) > 30000:
                cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 0, 255), 2)
                #if(before = n and count not equal to 1)
                ser.write(b'r')
                time.sleep(15)
            elif np.sum(purple_mask[y:y+h, x:x+w]) > 40000:
                cv2.rectangle(frame, (x, y), (x+w, y+h),  (128, 0, 128), 2)
                ser.write(b'p')
                time.sleep(15)
            elif np.sum(green_mask[y:y+h, x:x+w]) > 0:
                cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
                ser.write(b'g')
                time.sleep(20)

        ser.write(b'n')      
    cv2.imshow('frame', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()
