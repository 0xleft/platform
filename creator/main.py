import os
import playsound
import argparse
import time as t
import threading

import msvcrt

def kbfunc():
    x = msvcrt.kbhit()
    if x:
        ret = msvcrt.getch()
    else:
        ret = False
    return ret

keys = ["a,s,d,f"]

args = argparse.ArgumentParser()
args.add_argument("-f", "--file", help="File to open")

args = args.parse_args()

time = 0
shouldStop = False

def playThread():
    global time, shouldStop
    total = ""
    while not shouldStop:
        t.sleep(0.01)
        time += 10
        x = kbfunc() # will not wait for input
        if x:
            x = str(x)
            total += f"{time};{x},"
    print(total[:-1])

if __name__ == "__main__":
    if args.file:
        if os.path.exists(args.file):
            t1 = threading.Thread(target=playThread)
            t1.start()
            playsound.playsound(args.file, True)
            shouldStop = True
            t1.join()
        else:
            print("File not found")
    else:
        print("No file specified")