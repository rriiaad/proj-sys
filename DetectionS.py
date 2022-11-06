from hashlib import *
import psutil, os, time
from elevate import elevate


#on lance le programme avec les privilèges d'administrateur pour pouvoir parcourir tout les fichiers et dossiers
elevate()

#On recupere le haché du fichier exécutable du programme malveillant "calculé au préalable".
virusHash="900da4b98b8dcf039bb82edc6cbc74114fde1cd0142f7ad07f883399d6b1949c" 


#On démarre la procédure de détection

print("----On commence le scan du programme malveillant----")
start = time.time() 
time.sleep(1.5)

#on commence par les programes en cours d'execution
Virus = False

for process in psutil.process_iter():
    try:
        #on calcule le haché du fichier exécutable du processus
        command="certutil -hashfile \""+process.exe()+"\" SHA256"
        execmd=os.popen(command).read()
        hash=execmd.split("\n")[1] 

        if hash == virusHash:
            Virus = True
            print("\n---------------------------------------------\n")
            print("----L'éxécutable du processus malveillant est détecté !----")
            print("\n---------------------------------------------\n")
            time.sleep(1)
            print("----Interuption du processus malveillant----")
            print("\n---------------------------------------------\n")
            time.sleep(0.5)
            process.kill()
            command='del  "'+process.exe()+'"'
            execmd=os.popen(command).read()
            print("----suppression du fichier exécutable du processus malveillant avec succès----")
            print("\n---------------------------------------------\n")
            print("----Ne télécharger plus des fichiers de sources non sure!----")
            end = time.time() #print current time
            print(f"----Temps d'execution: {end - start}s----")
            print("\n---------------------------------------------\n")
            time.sleep(15)
            break

    except: 
        pass

if Virus == False:
     print("----Le processus malveillant n'est pas actif en ce moment, On doit rechercher dans la liste de tout les Programmes----")
     print("\n---------------------------------------------\n")
     time.sleep(5)

#print(f"you are in: {os.getcwd()}")                                #print current directory
                                                #print current time
suspectFolder = os.environ["appdata"]

for (path,dirs,files) in os.walk(suspectFolder) :                   #we start working from our working directory
    depth = len(path.split('/'))                                    #we are calculating the depth of the path 
    dirs = f"{'-'*(depth*2+4) + '[' +path.split('/')[-1] +']'}"     #print the directories
    

    for file in files :
        fdirs = f"{'-'*(depth*2+6) + ' ' +file}"                    #print the files inside directories
        #print(fdirs)
        fpath = f"{path}\\{file}"                                   #we are creating the full path of the file
        print(fpath)
        
        command = f"certutil -hashfile {fpath} SHA256"              #we are creating the command to get the hash of the file
        execmd = os.popen(command).read()                           #we are executing the command
        hash = execmd.split("\n")[1]                                #we are getting the hash from the output

        if hash == virusHash:                                       #we are checking if the hash is the same as the virus hash
            Virus = True
            print("\n---------------------------------------------\n")
            print("----L'éxécutable du processus malveillant est détecté !-----")
            time.sleep(1)
            print("\n---------------------------------------------\n")
            print(f"-----Le chemin du virus: {fpath}-----")
            time.sleep(1)
            print("\n---------------------------------------------\n")
            command= f'del "{fpath}"'
            execmd=os.popen(command).read()
            print("-----Suppression du fichier source du virus avec succès-----")
            time.sleep(4)
            if Virus == True:
                end = time.time() #print current time
                print("\n---------------------------------------------\n")
                print(f"----Temps mis pour la détection et supression du virus: {end-start}s-----") #print the time taken to execute the program
                print("\n---------------------------------------------\n")
                Virus == False
                time.sleep(10)
                break 
    time.sleep(10)
    break



       


        




