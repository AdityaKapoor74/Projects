import speech_recognition as sr
import vlc
import time
import cv2
import imutils
import numpy as np
from sklearn.metrics import pairwise

#global variables
list_of_songs={"Counting Stars":"CountingStars.mp3","good vibes":"GoodVibes.wav","starboy":"Starboy.wav"}
instance=vlc.Instance()
player=instance.media_player_new()
bg=None             #foreground detection
r=sr.Recognizer()   #recognize audio
mic=sr.Microphone() #input audio

#Gesture
def count(thresholded, segmented): #counting the number of fingers
	# find the convex hull of the segmented hand region
	chull = cv2.convexHull(segmented)

	# find the most extreme points in the convex hull
	extreme_top    = tuple(chull[chull[:, :, 1].argmin()][0])
	extreme_bottom = tuple(chull[chull[:, :, 1].argmax()][0])
	extreme_left   = tuple(chull[chull[:, :, 0].argmin()][0])
	extreme_right  = tuple(chull[chull[:, :, 0].argmax()][0])

	# find the center of the palm
	cX = (extreme_left[0] + extreme_right[0]) // 2
	cY = (extreme_top[1] + extreme_bottom[1]) // 2

	# find the maximum euclidean distance between the center of the palm
	# and the most extreme points of the convex hull
	distance = pairwise.euclidean_distances([(cX, cY)], Y=[extreme_left, extreme_right, extreme_top, extreme_bottom])[0]
	maximum_distance = distance[distance.argmax()]
	
	# calculate the radius of the circle with 80% of the max euclidean distance obtained
	radius = int(0.8 * maximum_distance)
	
	# find the circumference of the circle
	circumference = (2 * np.pi * radius)

	# take out the circular region of interest which has 
	# the palm and the fingers
	circular_roi = np.zeros(thresholded.shape[:2], dtype="uint8")
	
	# draw the circular ROI
	cv2.circle(circular_roi, (cX, cY), radius, 255, 1)
	
	# take bit-wise AND between thresholded hand using the circular ROI as the mask
	# which gives the cuts obtained using mask on the thresholded hand image
	circular_roi = cv2.bitwise_and(thresholded, thresholded, mask=circular_roi)

	# compute the contours in the circular ROI
	(cnts,_) = cv2.findContours(circular_roi.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

	# initalize the finger count
	count = 0

	# loop through the contours found
	for c in cnts:
		# compute the bounding box of the contour
		(x, y, w, h) = cv2.boundingRect(c)

		# increment the count of fingers only if -
		# 1. The contour region is not the wrist (bottom area)
		# 2. The number of points along the contour does not exceed
		#     25% of the circumference of the circular ROI
		if ((cY + (cY * 0.25)) > (y + h)) and ((circumference * 0.25) > c.shape[0]):
			count += 1

	return count


def run_avg(image,aWeight): #detect background
    global bg

    if bg is None:
        bg=image.copy().astype("float")
        return

    cv2.accumulateWeighted(image,bg,aWeight)

def segment(image, threshold=25):
    global bg
    # find the absolute difference between background and current frame
    diff = cv2.absdiff(bg.astype("uint8"), image)

    # threshold the diff image so that we get the foreground
    thresholded = cv2.threshold(diff,
                                threshold,
                                255,
                                cv2.THRESH_BINARY)[1]

    # get the contours in the thresholded image
    (cnts, _) = cv2.findContours(thresholded.copy(),
                                    cv2.RETR_EXTERNAL,
                                    cv2.CHAIN_APPROX_SIMPLE)

    # return None, if no contours detected
    if len(cnts) == 0:
        return
    else:
        # based on contour area, get the maximum contour which is the hand
        segmented = max(cnts, key=cv2.contourArea)
        return (thresholded, segmented)


#VLC media
def playSong(song_name):
    media=instance.media_new(song_name)
    player.set_media(media)
    player.play()
    duration=player.get_length()
    mm,ss=divmod(duration,60)
    print("Current song is:",song_name)
    #print("The length of the song is:")
    #print(mm,"mins",ss,"secs")
    return duration
    
def stopSong():
    player.stop()

def modulate_volume(percentage):
    player.audio_set_volume(percentage)

def get_current_state():
    return player.get_state()
               

if __name__=="__main__":

    print("To start playing wait for a second and say: Hello")
    with mic as source: #asking to play or not
        r.adjust_for_ambient_noise(source)
        audio=r.listen(source)
    
    user_input=r.recognize_google(audio)
    print(user_input)


    while(user_input=="hello" or user_input=="hello"): #loop to play songs
        print("Name a song out of the given list:")
        for name in list_of_songs:
            print(name)

        print("Speak into the microphone, the song you want to play")
        with mic as source: #asking for the name of the song
            r.adjust_for_ambient_noise(source)
            audio=r.listen(source)
        
        user_input=r.recognize_google(audio) #audio to text
        print(user_input)
        
        duration=playSong(list_of_songs[user_input])  #play the song

        #open cv
        aWeight=0.5

        camera=cv2.VideoCapture(0)
        top,right,bottom,left=10,350,225,590

        num_frames=0
        
        #with mic as source:
        #    r.adjust_for_ambient_noise(source)
        #    audio=r.listen(source)

        #user_input=r.recognize_google(audio)
        #print(user_input)
            
        while True:
            current_state=get_current_state()
            if(not current_state):
                break
            (grabbed,frame)=camera.read()

            frame=imutils.resize(frame,width=700)
            frame=cv2.flip(frame,1)

            clone=frame.copy()

            (height,width)=frame.shape[:2]

            roi=frame[top:bottom,right:left]

            gray=cv2.cvtColor(roi,cv2.COLOR_BGR2GRAY)
            gray=cv2.GaussianBlur(gray,(7,7),0)

            if num_frames<30:
                run_avg(gray,aWeight)
            else:
                hand=segment(gray)


                if hand is not None:
                    (thresholded,segmented)=hand

                    cv2.drawContours(clone,[segmented+(right,top)],-1,(0,0,255))

                    count_fingers=count(thresholded,segmented)

                    print(count_fingers)
                    if(count_fingers==5):
                        stopSong()
                        break
                    elif(count_fingers==4):
                        modulate_volume(80)
                    elif(count_fingers==3):
                        modulate_volume(60)
                    elif(count_fingers==2):
                        modulate_volume(40)
                    elif(count_fingers==1):
                        modulate_volume(20)
                    
                    cv2.imshow("Thresholded",thresholded)

                    

            cv2.rectangle(clone,(left,top),(right,bottom),(0,255,0),2)

            num_frames+=1

            cv2.imshow("Video Feed",clone)


            keypress=cv2.waitKey(1) & 0xFF

            if keypress==ord("q"):
                break

        camera.release()
        cv2.destroyAllWindows()




        print("If you want to play another song, say: Hello")
        with mic as source:
            r.adjust_for_ambient_noise(source)
            audio=r.listen(source)

        user_input=recognize_google(audio)
        print(user_input)
