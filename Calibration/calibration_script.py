import cv2

est = []

with open('config_data.txt', 'r') as f:
    
    while(True):        
        line = f.readline().strip()

        if line == '':
            f.readline()
            break
        elif line[0] == '#':
            line = f.readline().strip()        

        aw, ah = [float(x) for x in line.split(sep=',')]
            
    while(True):        
        line = f.readline().strip()
        if(line == ''):
            break
        
        d, w, h = [float(x) for x in line.split(sep=',')] 
        est.append(aw * d / w)        

magic_num = sum(est) / len(est)

with open('calibration.txt', 'w') as f:
    f.write(str(round(magic_num,5)))
